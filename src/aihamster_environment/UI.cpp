// AIHamster_Environment
// Dominik Cebula
// dominikcebula@gmail.com

// This file is part of AIHamster_Environment. AIHamster_Environment is free software: you can
// redistribute it and/or modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation, version 2.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
// 
// You should have received a copy of the GNU General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 51
// Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
// 
// Copyright Dominik Cebula

#include "UI.h"
#include "GameException.h"
#include "Game.h"
#include "Font.h"

UI::UI()
{
	icon=NULL;
	progress=0;
	text="0%";
}

UI::UI(Point& pos)
{
	icon=NULL;
	progress=0;
	text="0%";
	this->pos=pos;
}

UI::~UI()
{
	if (icon!=NULL)
		destroy_bitmap(icon);
}

void UI::Draw()
{
	Point barP1, barP2, txtPoint;
	
	if (icon!=NULL)
		draw_trans_sprite(buff, icon, pos.GetX(), pos.GetY());

	barP1.SetX(pos.GetX()+18);
	barP1.SetY(pos.GetY()+2);
	barP2.SetX(barP1.GetX()+UI::barWidth);
	barP2.SetY(barP1.GetY()+UI::barHeight);
	rect(buff, barP1.GetX(), barP1.GetY(), barP2.GetX(), barP2.GetY(), makecol(255, 255, 255));

	txtPoint.SetX(barP2.GetX()+5);
	txtPoint.SetY(barP1.GetY()-4);
	Font font=Font::getInstance();
	textprintf(buff, *font, txtPoint.GetX(), txtPoint.GetY(), makecol(255,255,255), "%3d%s", progress, "%");

	if (progress>0) {
		barP1.SetX(barP1.GetX()+2);
		barP1.SetY(barP1.GetY()+2);
		barP2.SetX(barP1.GetX()+((progress*(barWidth-4))/100));
		barP2.SetY(barP2.GetY()-2);
		rectfill(buff, barP1.GetX(), barP1.GetY(), barP2.GetX(), barP2.GetY(), makecol(255, 255, 255));
	}
}

int UI::GetProgress()
{
	return this->progress;
}

void UI::SetProgress(int progress)
{
	this->progress=progress;
}

void UIHunger::init()
{
	icon=load_tga("Data\\icon_hunger.tga", default_palette);
	if (icon==NULL)
		throw GameException("Error while loading icon_hunger.tga.");
}

void UISleep::init()
{
	icon=load_tga("Data\\icon_sleep.tga", default_palette);
	if (icon==NULL)
		throw GameException("Error while loading icon_sleep.tga.");
}

void UIThirst::init()
{
	icon=load_tga("Data\\icon_thirst.tga", default_palette);
	if (icon==NULL)
		throw GameException("Error while loading icon_thirst.tga.");
}

void UISafety::init()
{
	icon=load_tga("Data\\icon_safety.tga", default_palette);
	if (icon==NULL)
		throw GameException("Error while loading icon_safety.tga.");
}

void UIHealth::init()
{
	icon=load_tga("Data\\icon_health.tga", default_palette);
	if (icon==NULL)
		throw GameException("Error while loading icon_health.tga.");
}

void UIHunger::ProcessState(BotNetworkHamsterState state)
{
	this->SetProgress(state.hunger);
}

void UISleep::ProcessState(BotNetworkHamsterState state)
{
	this->SetProgress(state.sleep);
}

void UIThirst::ProcessState(BotNetworkHamsterState state)
{
	this->SetProgress(state.thirst);
}

void UISafety::ProcessState(BotNetworkHamsterState state)
{
	this->SetProgress(state.safety);
}

void UIHealth::ProcessState(BotNetworkHamsterState state)
{
	this->SetProgress(state.health);
}
