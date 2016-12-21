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

enum WorldComponentID {
	cucumber=1,
	tomato=2,
	apple=3,
	flyagaric=4,
	water=5,
	poison=6,
	hole=7,
	house=8
};

enum WorldComponentState {
	unspawn=1,
	immatured=2,
	matured=3,
	riot=4
};

enum Action {
	acMove=1,
	acUse=2
};

// scenario
// 1. BotNetworkWorldState   - env->bot
// 2. BotNetworkAction       - env<-bot
// 3. BotNetworkReaction     - env->bot
// 4. BotNetworkHamsterState - env<-bot

struct BotNetworkObj {
	bool active;
	WorldComponentID clsid;
	int objid;
	WorldComponentState state;
	int x;
	int y;
	int distance;
};

struct BotNetworkWorldState {
	BotNetworkObj obj[64]; 
};

struct BotNetworkAction {
	Action action;
	int vx, vy;
	int objid;
};

struct BotNetworkReaction {
	int x, y;
	int diffHunger;
	int diffSleep;
	int diffThirst;
	int diffSafety;
	int diffHealth;
};

struct BotNetworkHamsterState {
	int hunger;
	int sleep;
	int thirst;
	int safety;
	int health;
};
