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

#include "WorldComponents.h"
#include "Ground.h"
#include "GameException.h"
#include "Game.h"

int WorldComponent::GenObjID=1;

WorldComponent::WorldComponent()
{
	++GenObjID;
	ObjID=GenObjID;

	staticState=false;
	staticPos=false;
	rotateSupport=false;
	player=false;
	angle=0;
	bImmatured=NULL;
	bMatured=NULL;
	bRiot=NULL;
	state=unspawn;
	srand(time(NULL));
	objTime.saveTime();
	ttl=0;
	SetWidth(32);
	SetHeight(32);
}

WorldComponent::~WorldComponent()
{
	if (bImmatured!=NULL)
		destroy_bitmap(bImmatured);
	if (bMatured!=NULL)
		destroy_bitmap(bMatured);
	if (bRiot!=NULL)
		destroy_bitmap(bRiot);
}

void WorldComponent::GetRndPos(Point& rpos)
{
	rpos.SetX(rand()%(Ground::GroundMapX-this->width/2)+this->width/2);
	rpos.SetY(rand()%(Ground::GroundMapY-this->height/2)+this->height/2);
}

void WorldComponent::Process()
{
	if (player && state!=unspawn)
		return;

	if (objTime.diffToCurrent()<ttl)
		return;

	if (state==unspawn) {
		Point oldpos, newpos;
		oldpos=pos;
		bool accepted=false;
		int c=0;

		while (!accepted && c<100) {
			GetRndPos(pos);

			accepted=Ground::AcceptObject(*this);
			c++;
		}

		if (!accepted) {
			pos=oldpos;
			objTime.saveTime();
			return;
		}
		else
			newpos=pos;

		pos=oldpos;
		Ground::MarkPos(*this, 0);
		pos=newpos;
		Ground::MarkPos(*this, 1);
	}
	
	state=nextState(state);
	if (state==unspawn)
		Ground::MarkPos(*this, 0);
	ttl=getTTL();
	objTime.saveTime();
}

void WorldComponent::Draw()
{
	if (state==unspawn)
		return;

	BITMAP* bState=NULL;
	if (state==immatured)
		bState=bImmatured;
	else if (state==matured)
		bState=bMatured;
	else if (state==riot)
		bState=bRiot;

	if (staticState)
		bState=bMatured;
	if (bState!=NULL && !rotateSupport)
		draw_trans_sprite(buff, bState, pos.GetX()-(this->width/2), pos.GetY()+68-(this->height/2));
	else if (bState!=NULL && rotateSupport) {
		BITMAP* bRotated=create_bitmap(32, 32);
		rotate_sprite(bRotated, bState, 0, 0, itofix(angle));
		draw_trans_sprite(buff, bRotated, pos.GetX()-(this->width/2), pos.GetY()+68-(this->height/2));
		destroy_bitmap(bRotated);
	}
}

WorldComponentState WorldComponent::nextState(WorldComponentState state)
{
	if (staticPos)
		return matured;

	if (state==unspawn)
		return immatured;
	else if (state==immatured)
		return matured;
	else if (state==matured)
		return riot;
	else if (state==riot)
		return unspawn;
	else
		return unspawn;
}

aitime WorldComponent::getTTL()
{
	return 15+(rand()%10)*10000;
}

void Cucumber::init()
{
	ClsID=cucumber;

	bImmatured=load_tga("Data\\cucumber_immatured.tga", default_palette);
	if (bImmatured==NULL)
		throw GameException("Error while loading cucumber_immatured.tga.");

	bMatured=load_tga("Data\\cucumber_matured.tga", default_palette);
	if (bMatured==NULL)
		throw GameException("Error while loading cucumber_matured.tga.");

	bRiot=load_tga("Data\\cucumber_riot.tga", default_palette);
	if (bRiot==NULL)
		throw GameException("Error while loading cucumber_riot.tga.");
}

void Tomato::init()
{
	ClsID=tomato;

	bImmatured=load_tga("Data\\tomato_immatured.tga", default_palette);
	if (bImmatured==NULL)
		throw GameException("Error while loading tomato_immatured.tga.");

	bMatured=load_tga("Data\\tomato_matured.tga", default_palette);
	if (bMatured==NULL)
		throw GameException("Error while loading tomato_matured.tga.");

	bRiot=load_tga("Data\\tomato_riot.tga", default_palette);
	if (bRiot==NULL)
		throw GameException("Error while loading tomato_riot.tga.");
}

void Apple::init()
{
	ClsID=apple;

	bImmatured=load_tga("Data\\apple_immatured.tga", default_palette);
	if (bImmatured==NULL)
		throw GameException("Error while loading apple_immatured.tga.");

	bMatured=load_tga("Data\\apple_matured.tga", default_palette);
	if (bMatured==NULL)
		throw GameException("Error while loading apple_matured.tga.");

	bRiot=load_tga("Data\\apple_riot.tga", default_palette);
	if (bRiot==NULL)
		throw GameException("Error while loading apple_riot.tga.");
}

void Flyagaric::init()
{
	ClsID=flyagaric;

	bImmatured=load_tga("Data\\flyagaric_immatured.tga", default_palette);
	if (bImmatured==NULL)
		throw GameException("Error while loading flyagaric_immatured.tga.");

	bMatured=load_tga("Data\\flyagaric_matured.tga", default_palette);
	if (bMatured==NULL)
		throw GameException("Error while loading flyagaric_matured.tga.");

	bRiot=load_tga("Data\\flyagaric_riot.tga", default_palette);
	if (bRiot==NULL)
		throw GameException("Error while loading flyagaric_riot.tga.");
}

void Water::init()
{
	ClsID=water;
	staticState=true;

	bMatured=load_tga("Data\\water.tga", default_palette);
	if (bMatured==NULL)
		throw GameException("Error while loading water.tga.");
}

void Poison::init()
{
	ClsID=poison;
	staticState=true;

	bMatured=load_tga("Data\\poison.tga", default_palette);
	if (bMatured==NULL)
		throw GameException("Error while loading poison.tga.");
}

void Hole::init()
{
	ClsID=hole;
	staticState=true;

	bMatured=load_tga("Data\\hole.tga", default_palette);
	if (bMatured==NULL)
		throw GameException("Error while loading hole.tga.");
}

void House::init()
{
	ClsID=house;
	staticState=true;
	staticPos=true;
	sleepMode=false;

	bMatured=load_tga("Data\\house.tga", default_palette);
	if (bMatured==NULL)
		throw GameException("Error while loading house.tga.");

	bSleep=load_tga("Data\\house_sleep.tga", default_palette);
	if (bSleep==NULL)
		throw GameException("Error while loading house_sleep.tga.");
}

BotNetworkReaction Cucumber::ProduceReaction()
{
	BotNetworkReaction reaction;
	memset(&reaction, 0, sizeof(BotNetworkReaction));

	if (state==immatured) {
		reaction.diffHunger=2;
		reaction.diffThirst=0;
		reaction.diffHealth=-2;
	}
	else if (state==matured) {
		reaction.diffHunger=10;
		reaction.diffThirst=1;
		reaction.diffHealth=10;
	}
	else if (state==riot) {
		reaction.diffHunger=0;
		reaction.diffThirst=-2;
		reaction.diffHealth=-2;
	}

	state=unspawn;
	Ground::MarkPos(*this, 0);

	return reaction;
}

BotNetworkReaction Tomato::ProduceReaction()
{
	BotNetworkReaction reaction;
	memset(&reaction, 0, sizeof(BotNetworkReaction));

	if (state==immatured) {
		reaction.diffHunger=5;
		reaction.diffThirst=1;
		reaction.diffHealth=-1;
	}
	else if (state==matured) {
		reaction.diffHunger=15;
		reaction.diffThirst=3;
		reaction.diffHealth=10;
	}
	else if (state==riot) {
		reaction.diffHunger=0;
		reaction.diffThirst=0;
		reaction.diffHealth=-2;
	}

	state=unspawn;
	Ground::MarkPos(*this, 0);

	return reaction;
}

BotNetworkReaction Apple::ProduceReaction()
{
	BotNetworkReaction reaction;
	memset(&reaction, 0, sizeof(BotNetworkReaction));

	if (state==immatured) {
		reaction.diffHunger=5;
		reaction.diffThirst=4;
		reaction.diffHealth=-5;
	}
	else if (state==matured) {
		reaction.diffHunger=10;
		reaction.diffThirst=1;
		reaction.diffHealth=10;
	}
	else if (state==riot) {
		reaction.diffHunger=0;
		reaction.diffThirst=1;
		reaction.diffHealth=-1;
	}

	state=unspawn;
	Ground::MarkPos(*this, 0);

	return reaction;
}

BotNetworkReaction Flyagaric::ProduceReaction()
{
	BotNetworkReaction reaction;
	memset(&reaction, 0, sizeof(BotNetworkReaction));

	if (state==immatured) {
		reaction.diffHunger=6;
		reaction.diffHealth=-10;
	}
	else if (state==matured) {
		reaction.diffHunger=10;
		reaction.diffHealth=-20;
	}
	else if (state==riot) {
		reaction.diffHunger=4;
		reaction.diffHealth=-8;
	}

	state=unspawn;
	Ground::MarkPos(*this, 0);

	return reaction;
}

BotNetworkReaction Water::ProduceReaction()
{
	BotNetworkReaction reaction;
	memset(&reaction, 0, sizeof(BotNetworkReaction));

	reaction.diffThirst=10;
	reaction.diffHealth=10;

	state=unspawn;
	Ground::MarkPos(*this, 0);

	return reaction;
}

BotNetworkReaction Poison::ProduceReaction()
{
	BotNetworkReaction reaction;
	memset(&reaction, 0, sizeof(BotNetworkReaction));

	reaction.diffThirst=10;
	reaction.diffHealth=-10;

	state=unspawn;
	Ground::MarkPos(*this, 0);

	return reaction;
}

BotNetworkReaction Hole::ProduceReaction()
{
	BotNetworkReaction reaction;
	memset(&reaction, 0, sizeof(BotNetworkReaction));

	reaction.diffSleep=-30;
	reaction.diffSafety=-20;
	reaction.diffHealth=-20;

	state=unspawn;
	Ground::MarkPos(*this, 0);

	return reaction;
}

BotNetworkReaction House::ProduceReaction()
{
	BotNetworkReaction reaction;
	memset(&reaction, 0, sizeof(BotNetworkReaction));

	reaction.diffSleep=100;
	reaction.diffSafety=60;
	reaction.diffHealth=40;

	return reaction;
}

void House::GetRndPos(Point& rpos)
{
	rpos.SetX(rand()%(Ground::GroundMapX-this->width/2)+this->width/2);
	rpos.SetY(rand()%(Ground::GroundMapY-(this->height*2)));
}

void House::Draw()
{
	if (sleepMode)
		draw_trans_sprite(buff, bSleep, pos.GetX()-(this->width/2), pos.GetY()+68-(this->height/2));
	else
		WorldComponent::Draw();
}
