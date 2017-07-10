#pragma once

class CHeroSystem
{
public:
	/* STATIC METHODS */
	static void Install();

private:
	static void ValidateHeroSkills(VOID *pNoblessSystem, User *pUser);
};
