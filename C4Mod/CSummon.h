#pragma once

class CSummon : public CNPC
{
	public:

	/* 1A58 */ s32 _dw1A58[18];

	User* GetMaster()
	{
		typedef User* (__thiscall *_GETM) (CSummon *Myself);
		_GETM xGetM = (_GETM)CSummon__GetMaster;
		return (xGetM(this));
	}
};