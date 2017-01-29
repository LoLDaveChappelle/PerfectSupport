#pragma once
#include "PluginSDK.h"


IMenu* MainMenu;
IMenu* QMenu;
IMenu* WMenu;
IMenu* EMenu;
IMenu* RMenu;
IMenu* Misc;
IMenu* Drawings;
IMenuOption* ComboQ;
IMenuOption* AutoQ;
IMenuOption* HarassManaE;
IMenuOption* HarassManaW;
IMenuOption* FarmE;
IMenuOption* FarmEHit;
IMenuOption* HarassManaQ;
IMenuOption* FarmW;
IMenuOption* ComboW;
IMenuOption* QGapCloser;
IMenuOption* AutoE;
IMenuOption* AutoUlt;
IMenuOption* ComboE;
IMenuOption* ComboR;
IMenuOption* UltEnemies;
IMenuOption* DrawReady;
IMenuOption* DrawQ;
IMenuOption* DrawW;
IMenuOption* DrawE;
IMenuOption* DrawR;


ISpell2* Q;
ISpell2* W;
ISpell2* E;
ISpell2* R;

class Blitzcrank
{
public:

	void  Menu()
	{
		MainMenu = GPluginSDK->AddMenu("PerfectBlitzcrank");
		QMenu = MainMenu->AddMenu("Q Settings");
		WMenu = MainMenu->AddMenu("W Settings");
		EMenu = MainMenu->AddMenu("E Settings");
		RMenu = MainMenu->AddMenu("R Settings");
		Drawings = MainMenu->AddMenu("Drawings");

		ComboQ = QMenu->CheckBox("Use Q", true);
		HarassManaQ = QMenu->AddInteger("Mana Manager(%)", 1, 100, 60);

		ComboW = WMenu->CheckBox("Use W", true);

		AutoE = EMenu->CheckBox("Auto E", true);
		ComboE = EMenu->CheckBox("Use E", true);

		AutoUlt = RMenu->CheckBox("Auto R(if 3 enemies in Range", true);
		ComboR = RMenu->CheckBox("R When X Enemies in Range ", true);
		UltEnemies = RMenu->AddInteger("Minimum enemies to hit with R", 1, 5, 2);

		DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);

		DrawQ = Drawings->CheckBox("Draw Q", true);
		DrawW = Drawings->CheckBox("Draw W", true);
		DrawE = Drawings->CheckBox("Draw E", true);
		DrawR = Drawings->CheckBox("Draw R", true);
	}

	void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, static_cast<eCollisionFlags>(kCollidesWithNothing));
		Q->SetOverrideRange(800);
		W->SetOverrideRange(1150);
		E->SetOverrideRange(155);
		R->SetOverrideRange(600);

	}

	int GetEnemiesInRange(float range)
	{
		auto enemies = GEntityList->GetAllHeros(false, true);
		auto enemiesInRange = 0;

		for (auto enemy : enemies)
		{
			if (enemy != nullptr && enemy->GetTeam() != GEntityList->Player()->GetTeam())
			{
				auto flDistance = (enemy->GetPosition() - GEntityList->Player()->GetPosition()).Length();
				if (flDistance < range)
				{
					E->CastOnPlayer();
				}
			}
		}
		return true;
	}

	void Combo()
	{
		if (ComboQ->Enabled())
		{
			if (Q->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
				Q->CastOnTarget(target, kHitChanceHigh);
			}
		}
		if (ComboW->Enabled() && GetEnemiesInRange(850))
		{
			if (W->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, W->Range());
				W->CastOnTarget(target, kHitChanceHigh);
			}
		}
		if (ComboE->Enabled())
		{
			if (E->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, E->Range());
				E->CastOnTarget(target, kHitChanceHigh);
			}
		}
		if (ComboR->Enabled())
		{
			if (R->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, R->Range());
				int enemies = 0;
				Vec3 pos = Vec3();
				R->FindBestCastPosition(false, true, pos, enemies);
				if (enemies >= UltEnemies->GetInteger())
					R->CastOnPosition(pos);

			}
		}
	}

	void Drawing()
	{
		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

			if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

			if (R->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }

		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
		}
	}
};
