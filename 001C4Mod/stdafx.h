#pragma once

#pragma comment(lib, "ws2_32.lib")

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <WinSock2.h>
#include <vector>
#include <map>
#include <list>
#include <time.h>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <limits>
#include <algorithm>

using namespace std;

#include "..\Shared\Shared.h"

extern u64* pHwID;

#define WIDEN2(x) L##x
#define WIDEN(x) WIDEN2(x)
#define __WFILE__ WIDEN(__FILE__)

#define MAX_PACKET_LEN 0x2000

struct vPosition
{
	d64 x;
	d64 y;
	d64 z;
};

//#define _AMPED64_

#include "Offsets.h"
#include "MemoryTools.h"
#include "Utils.h"
#include "IniFile.h"
#include "CBaseOperateCondition.h"
#include "CBaseSkillEffect.h"
#include "CSkillInfo.h"
#include "CObjectSP.h"
#include "CLog.h"
#include "CSPacket.h"
#include "L2ServerFunctions.h"
#include "MemoryObject.h"
#include "CIOObject.h"
#include "CObject.h"
#include "CItem.h"
#include "CInventory.h"
#include "CSharedData.h"
#include "CCreature.h"
#include "CNPC.h"
#include "CSummon.h"
#include "CPet.h"
#include "User.h"
#include "CSocket.h"
#include "CAlliance.h"
#include "CMerchant.h"
#include "CParty.h"
