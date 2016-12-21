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
#include "GameComponent.h"
#include "BoundingBox.h"
#include "Time.h"
#include "Network.h"
#include "NetworkProcessor.h"

class WorldComponent : public GameComponent, public BoundingBox, public NetworkProcessorReaction
{
protected:
	BITMAP* bImmatured;
	BITMAP* bMatured;
	BITMAP* bRiot;
	Time objTime;
	aitime ttl;
	float angle;
	bool vflip, hflip;
	bool staticPos;
	bool player;
	bool rotateSupport;

	WorldComponentState nextState(WorldComponentState state);
	aitime getTTL();
protected:
	virtual void GetRndPos(Point& rpos);
public:
	WorldComponentState state;
	WorldComponentID ClsID;
	int ObjID;
	static int GenObjID;
	bool staticState;

	WorldComponent();
	virtual ~WorldComponent();

	virtual void Process();
	virtual void Draw();
};

class Cucumber : public WorldComponent
{
public:
	void init();
	BotNetworkReaction ProduceReaction();
};

class Tomato : public WorldComponent
{
public:
	void init();
	BotNetworkReaction ProduceReaction();
};

class Apple : public WorldComponent
{
public:
	void init();
	BotNetworkReaction ProduceReaction();
};

class Flyagaric : public WorldComponent
{
public:
	void init();
	BotNetworkReaction ProduceReaction();
};

class Water : public WorldComponent
{
public:
	void init();
	BotNetworkReaction ProduceReaction();
};

class Poison : public WorldComponent
{
public:
	void init();
	BotNetworkReaction ProduceReaction();
};

class Hole : public WorldComponent
{
public:
	void init();
	BotNetworkReaction ProduceReaction();
};

class House : public WorldComponent
{
private:
	BITMAP* bSleep;
protected:
	void GetRndPos(Point& rpos);
public:
	bool sleepMode;

	void init();
	void Draw();
	BotNetworkReaction ProduceReaction();
};
