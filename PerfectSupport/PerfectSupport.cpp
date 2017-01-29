#include "stdafx.h"
#include "PluginSDK.h"
#include "Blitzcrank.h"
#include "Soraka.h"



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