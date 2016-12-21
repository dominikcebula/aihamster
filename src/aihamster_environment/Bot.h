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

#include "WorldComponents.h"
#include "NetworkProcessor.h"
#include "UI.h"
#include "BotSocket.h"
#include <vector>

using namespace std;

#ifdef _DEBUG
class Bot;
extern Bot* ptrbot;
#endif

class Bot : public WorldComponent, public NetworkProcessorBot, public NetworkProcessorWorld, public NetworkProcessorState
{
	BITMAP* bDead;
	BITMAP* bHole;
	BotSocket* botSocket;
	Time punchTime;
	Time sleepTime;
	Time holeTime;
	bool deadMode;
	bool sleepMode;
	bool holeMode;

	void ProcessActionExtra(WorldComponent* obj);
protected:
	void GetRndPos(Point& rpos);
public:
	Bot();
	~Bot();
	House* hHouse;

	vector<WorldComponent*> objList;
	vector<UI*> uiList;
	void init();
	void Process();
	void ProcessSpecial();
	void ProcessNetwork();
	void Draw();
	BotNetworkReaction ProcessAction(BotNetworkAction botAction);
	BotNetworkWorldState ProduceState();
	void ProcessState(BotNetworkHamsterState state);
	BotNetworkReaction ProduceReaction();
};
