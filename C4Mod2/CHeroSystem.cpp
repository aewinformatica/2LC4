#include "stdafx.h"
#include "CHeroSystem.h"

#ifdef DVAMP
	#define CALL_VALIDATE_SKILL1	OCrypt(K0, N0, 0x006BAFCEL)
	#define CALL_VALIDATE_SKILL2	OCrypt(K1, N1, 0x0084E34FL)
	#define CALL_VALIDATE_SKILL3	OCrypt(K2, N2, 0x00853643L)
	#define VALIDATE_NOBLESS_SKILL	OCrypt(K3, N3, 0x006BA630L)
#else
	#define CALL_VALIDATE_SKILL1	OCrypt(K4, N4, 0x006BA41EL)
	#define CALL_VALIDATE_SKILL2	OCrypt(K5, N5, 0x0084D3BFL)
	#define CALL_VALIDATE_SKILL3	OCrypt(K6, N6, 0x008526B3L)
	#define VALIDATE_NOBLESS_SKILL	OCrypt(K7, N7, 0x006B9A80L)
#endif

list<u32> heroSkills;

void CHeroSystem::Install()
{	
	CIniFile ini;

	if(ini.GetIntValue("Enabled", "HeroSkills", "L2Server.ini"))
	{
		u32 nSkillCount = ini.GetIntValue("SkillCount", "HeroSkills", "L2Server.ini");

		for (u32 i = 0; i < nSkillCount; i++)
		{
			char ID[20];
			sprintf_s(ID, sizeof(ID), "SkillID_%d", i);
			heroSkills.push_back(ini.GetIntValue(ID, "HeroSkills", "L2Server.ini"));
		}

		WriteInstruction(CALL_VALIDATE_SKILL1, (s32)CHeroSystem::ValidateHeroSkills, 0, ASM_CALL);
		WriteInstruction(CALL_VALIDATE_SKILL2, (s32)CHeroSystem::ValidateHeroSkills, 0, ASM_CALL);
		WriteInstruction(CALL_VALIDATE_SKILL3, (s32)CHeroSystem::ValidateHeroSkills, 0, ASM_CALL);
	}
}

void CHeroSystem::ValidateHeroSkills( VOID *pNoblessSystem, User *pUser )
{
	// Functions
	typedef void (__fastcall *_VNS) (VOID *, User *);
	_VNS xVNS = (_VNS)VALIDATE_NOBLESS_SKILL;

	// Calling Original Function
	xVNS(pNoblessSystem, pUser);

	// If in a sub class, remove the skills.
	if ( pUser->SD->SubClassID != 0 )
	{
		for ( list<u32>::iterator i = heroSkills.begin() ; i != heroSkills.end() ; i++ )
		{
			if ( pUser->HaveSkill(*i, 1) )
			{
				pUser->SendDeletedSkillToDB(*i);
				pUser->DeleteAcquiredSkill(*i);
			}
		}
		
		pUser->ValidateSkillList();
		return;
	}

	switch (pUser->SD->HeroType)
	{
		case 2: // Is Hero, so add the hero skills.
				for ( list<u32>::iterator i = heroSkills.begin() ; i != heroSkills.end() ; i++ )
				{
					if ( !pUser->HaveSkill(*i, 1) )
					{
						pUser->SendAcquiredSkillToDB(*i, 1, false);
						pUser->AcquireSkill(*i, 1, 0, 0);
					}
				}
			break;

		default: // Not Hero, so remove the hero skills.
				for ( list<u32>::iterator i = heroSkills.begin() ; i != heroSkills.end() ; i++ )
				{
					if ( pUser->HaveSkill(*i, 1) )
					{
						pUser->SendDeletedSkillToDB(*i);
						pUser->DeleteAcquiredSkill(*i);
					}
				}
			break;
	}

	// Performing the Needed Validations
	pUser->ValidateParameters();
	pUser->ValidateSkillList();
}







