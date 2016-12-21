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

#pragma once

#include <allegro.h>
#include <xstring>
#include "GameComponent.h"
#include "NetworkProcessor.h"
#include "Point.h"

using namespace std;

class UI : public GameComponent, public NetworkProcessorState
{
protected:
	static const int barWidth = 214;
	static const int barHeight = 12;

	Point pos;
	BITMAP* icon;
	string text;
	int progress;
public:
	UI();
	UI(Point& pos);
	~UI();

	void Draw();
	int GetProgress();
	void SetProgress(int progress);
};

class UIHunger : public UI
{
public:
	UIHunger(Point& pos) : UI(pos) { }
	void init();
	void ProcessState(BotNetworkHamsterState state);
};

class UISleep : public UI
{
public:
	UISleep(Point& pos) : UI(pos) { }
	void init();
	void ProcessState(BotNetworkHamsterState state);
};

class UIThirst : public UI
{
public:
	void init();
	UIThirst(Point& pos) : UI(pos) { }
	void ProcessState(BotNetworkHamsterState state);
};

class UISafety : public UI
{
public:
	void init();
	UISafety(Point& pos) : UI(pos) { }
	void ProcessState(BotNetworkHamsterState state);
};

class UIHealth : public UI
{
public:
	void init();
	UIHealth(Point& pos) : UI(pos) { }
	void ProcessState(BotNetworkHamsterState state);
};
