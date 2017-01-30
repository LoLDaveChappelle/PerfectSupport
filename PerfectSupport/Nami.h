#pragma once
#include "PluginSDK.h"
#include "Blitzcrank.h"


class Nami
{
public:

	void  Menu()
	{
		MainMenu = GPluginSDK->AddMenu("PerfectNami");
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
	}

	void LoadSorakaSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, static_cast<eCollisionFlags>(kCollidesWithNothing));

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

	int GetTeamMatesInRange(float range)
	{
		auto friendly = GEntityList->GetAllHeros(true, false);
		auto enemiesInRange = 0;

		for (auto friendly : friendly)
		{
			if (friendly != nullptr && friendly->GetTeam() != GEntityList->Player()->GetTeam())
			{
				auto flDistance = (friendly->GetPosition() - GEntityList->Player()->GetPosition()).Length();
				if (flDistance < range)
				{
					W->CastOnPlayer();
				}
			}
		}
		return true;
	}

	void WLogic()
	{
		for (auto ally : GEntityList->GetAllHeros(true, false))
		{
			if (GEntityList->Player()->IsValidTarget(ally, W->Range()) && W->IsReady() && ally->HealthPercent() <= 55)
			{
				W->CastOnTarget(ally);
				
			}
			if (GEntityList->Player()->IsValidTarget(ally, W->Range()) && W->IsReady() && ally->HealthPercent() <= 55)
			{
				E->CastOnTarget(ally);
			}
		}
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
		if (ComboW->Enabled())
		{
			WLogic();
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

	void TestPing()
	{
		GGame->SendPing(kPingOnMyWay, Vec3(255, 255, 255));
	}



	void Drawing()
	{
		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled())
			{
				GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range());
			}

			if (E->IsReady() && DrawE->Enabled())
			{
				GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range());
			}

			if (W->IsReady() && DrawW->Enabled())
			{
				GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range());
			}

		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }
		}
	}
};
