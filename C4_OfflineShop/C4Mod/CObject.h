#pragma once

class CObject : public CIOObject
{
	public:

		/* 0x020 */     s32 nClassID;
		/* 0x024 */     s32 nObjectID;
		/* 0x028 */     s32 nObjectType;
		/* 0x02C */     s32 unk02C;

// 		enum VTable
//         {
//                 VMTMemoryObject   = VMT_MemoryObject,
//                 VMTCObject        = VMT_CObject,
//                 VMTCGeneralObject = VMT_CGeneralObject,
//                 VMTCStaticObject  = VMT_CStaticObject,
//                 VMTCVehicle       = VMT_CVehicle,
//                 VMTCCreature      = VMT_CCreature,
//                 VMTCNPC           = VMT_CNPC,
//                 VMTCSummon        = VMT_CSummon,
//                 VMTCPet           = VMT_CPet,
//                 VMTCBoss          = VMT_CBoss,
//                 VMTCZzoldagu      = VMT_CZzoldagu,
//                 VMTUser           = VMT_User,
// 				VMTPledge         = VMT_Pledge,
// 				VMTCMerchant      = VMT_CMerchant
//         };

        bool IsValidObject(u64 vTable)
        {
            if(this)
			{
                __try
				{ 
					if(*(u64*)this == vTable) return true; 
				}
                __except(EXCEPTION_EXECUTE_HANDLER)
				{ 
					/* Invalid pointer */
					/* Preventing Crash ;) */
				}
            }

			return false;
        }
};
