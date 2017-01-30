#include "stdafx.h"
#include "PluginSDK.h"
#include "Blitzcrank.h"
#include "Soraka.h"
#include "Nami.h"
#include "Sona.h"
#include "Brand.h"
#include "Leona.h"


PluginSetup("Name");

#pragma region Events
PLUGIN_EVENT(void) OnOrbwalkBeforeAttack(IUnit* Target)
{
}

PLUGIN_EVENT(void) OnOrbwalkAttack(IUnit* Source, IUnit* Target)
{

}
#pragma endregion

class IChampion
{
public:
	virtual void OnGameUpdate() = 0;
	virtual void OnRender() = 0;
	virtual void OnLoad() = 0;
	virtual void unLoad() = 0;
};

class Blitz : public IChampion
{
public:
	virtual void OnLoad() override
	{
		PrintBlitzLoadMessage();
		Blitzcrank().Menu();
		Blitzcrank().LoadSpells();
	}
	virtual void OnRender() override
	{
		Blitzcrank().Drawing();
	}

	virtual void OnGameUpdate() override
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Blitzcrank().Combo();
		}
	}
	virtual void unLoad() override
	{
		Blitzcrank().Menu();
		Blitzcrank().LoadSpells();
	}
private:
	void PrintBlitzLoadMessage()
	{
		GGame->PrintChat("Blitzcrank detected...Loading script");
	}
};

class Raka : public IChampion
{
public:
	virtual void OnLoad() override
	{
		SorakaLoadMessage();
		Soraka().Menu();
		Soraka().LoadSorakaSpells();
	}
	virtual void OnRender() override
	{
		Soraka().Drawing();
	}

	virtual void OnGameUpdate() override
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Soraka().Combo();
		}
	}
	virtual void unLoad() override
	{
		Soraka().Menu();
		Soraka().LoadSorakaSpells();
	}
private:
	void SorakaLoadMessage()
	{
		GGame->PrintChat("Soraka detected...Loading script");
	}
};

class Son : public IChampion
{
public:
	virtual void OnLoad() override
	{
		SonaLoadMessage();
		Sona().Menu();
		Sona().LoadSorakaSpells();
	}
	virtual void OnRender() override
	{
		Sona().Drawing();
	}

	virtual void OnGameUpdate() override
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Sona().Combo();
		}
	}
	virtual void unLoad() override
	{
		Sona().Menu();
		Sona().LoadSorakaSpells();
	}
private:
	void SonaLoadMessage()
	{
		GGame->PrintChat("Sona detected...Loading script");
	}
};

class Jan : public IChampion
{
public:
	virtual void OnLoad() override
	{
		SorakaLoadMessage();
		Soraka().Menu();
		Soraka().LoadSorakaSpells();
	}
	virtual void OnRender() override
	{
		Soraka().Drawing();
	}

	virtual void OnGameUpdate() override
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Soraka().Combo();
		}
	}
	virtual void unLoad() override
	{
		Soraka().Menu();
		Soraka().LoadSorakaSpells();
	}
private:
	void SorakaLoadMessage()
	{
		GGame->PrintChat("Janna detected...Loading script");
	}
};

class Zyr : public IChampion
{
public:
	virtual void OnLoad() override
	{
		SorakaLoadMessage();
		Soraka().Menu();
		Soraka().LoadSorakaSpells();
	}
	virtual void OnRender() override
	{
		Soraka().Drawing();
	}

	virtual void OnGameUpdate() override
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Soraka().Combo();
		}
	}
	virtual void unLoad() override
	{
		Soraka().Menu();
		Soraka().LoadSorakaSpells();
	}
private:
	void SorakaLoadMessage()
	{
		GGame->PrintChat("Zyra detected...Loading script");
	}
};

class Bran : public IChampion
{
public:
	virtual void OnLoad() override
	{
		SorakaLoadMessage();
		Brand().Menu();
		Brand().LoadSorakaSpells();
	}
	virtual void OnRender() override
	{
		Brand().Drawing();
	}

	virtual void OnGameUpdate() override
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Brand().Combo();
		}
	}
	virtual void unLoad() override
	{
		Brand().Menu();
		Brand().LoadSorakaSpells();
	}
private:
	void SorakaLoadMessage()
	{
		GGame->PrintChat("Brand detected...Loading script");
	}
};

class Nam : public IChampion
{
public:
	virtual void OnLoad() override
	{
		NamiLoadMessage();
		Nami().Menu();
		Nami().LoadSorakaSpells();
	}
	virtual void OnRender() override
	{
		Nami().Drawing();
	}

	virtual void OnGameUpdate() override
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Nami().Combo();
		}
	}
	virtual void unLoad() override
	{
		Nami().Menu();
		Nami().LoadSorakaSpells();
	}
private:
	void NamiLoadMessage()
	{
		GGame->PrintChat("Nami detected...Loading script");
	}
};


class Leon : public IChampion
{
public:
	virtual void OnLoad() override
	{
		LeonaLoadMessage();
		Leona().Menu();
		Leona().LoadSorakaSpells();
	}
	virtual void OnRender() override
	{
		Leona().Drawing();
	}

	virtual void OnGameUpdate() override
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Leona().Combo();
		}
	}
	virtual void unLoad() override
	{
		Leona().Menu();
		Leona().LoadSorakaSpells();
	}
private:
	void LeonaLoadMessage()
	{
		GGame->PrintChat("Leona detected...Loading script");
	}
};

class Lu : public IChampion
{
public:
	virtual void OnLoad() override
	{
		SorakaLoadMessage();
		Soraka().Menu();
		Soraka().LoadSorakaSpells();
	}
	virtual void OnRender() override
	{
		Soraka().Drawing();
	}

	virtual void OnGameUpdate() override
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Soraka().Combo();
		}
	}
	virtual void unLoad() override
	{
		Soraka().Menu();
		Soraka().LoadSorakaSpells();
	}
private:
	void SorakaLoadMessage()
	{
		GGame->PrintChat("LuLu detected...Loading script");
	}
};


IChampion* pChampion = nullptr;

PLUGIN_EVENT(void) OnRender()
{
	pChampion->OnRender();
}

PLUGIN_EVENT(void) OnGameUpdate()
{
	pChampion->OnGameUpdate();
}

void LoadChampion()
{
	std::string szChampion = GEntityList->Player()->ChampionName();

	if (szChampion == "Blitzcrank")
		pChampion = new Blitz;
	else if (szChampion == "Soraka")
		pChampion = new Raka;
	else if (szChampion == "Sona")
		pChampion = new Son;
	else if (szChampion == "Janna")
		pChampion = new Jan;
	else if (szChampion == "Zyra")
		pChampion = new Zyr;
	else if (szChampion == "Nami")
		pChampion = new Nam;
	else if (szChampion == "Leona")
		pChampion = new Leon;
	else if (szChampion == "LuLu")
		pChampion = new Lu;
	else if (szChampion == "Brand")
		pChampion = new Bran;
	else
	{
		GGame->PrintChat("Champion not supported!");
	}

	if (pChampion != nullptr)
	{
		GEventManager->AddEventHandler(kEventOnRender, OnRender);
		GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
		// add other events here
	}
}

// Called when plugin is first loaded
PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	// Initializes global interfaces for core access
	PluginSDKSetup(PluginSDK);

	LoadChampion();
	pChampion->OnLoad();
}

// Called when plugin is unloaded
PLUGIN_API void OnUnload()
{

	if (pChampion != nullptr)
	{
		GEventManager->RemoveEventHandler(kEventOnRender, OnLoad);
		GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
		GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
		pChampion->unLoad();
	}
}