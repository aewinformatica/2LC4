#pragma once

struct CAllianceSharedData;

// 60h
class CAlliance : CObject
{
public:
	/* 030 */ u8 _b030[8];
	/* 038 */ CAllianceSharedData* SD;
	/* 040 */ u8 _b040[32];
};