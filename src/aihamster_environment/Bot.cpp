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

#include "Bot.h"
#include "GameException.h"
#include "Ground.h"
#include "Game.h"
#include <algorithm>

#ifdef _DEBUG
Bot* ptrbot=NULL;
#endif

struct BotNetworkObjCmp {
	bool operator() (BotNetworkObj& a, BotNetworkObj& b)
	{
		if (a.active && !b.active)
			return true;
		else
			return a.distance<b.distance;
	}
} botNetworkObjCmp;


Bot::Bot()
{
#ifdef _DEBUG
	ptrbot=this;
#endif
	botSocket=new BotSocket();
	staticState=true;
	player=true;
	rotateSupport=true;
	
	bDead=NULL;
	hHouse=NULL;
	bHole=NULL;
	deadMode=false;
	sleepMode=false;
	holeMode=false;
}

Bot::~Bot()
{
	objList.clear();
	delete botSocket;

	if (bDead!=NULL)
		destroy_bitmap(bDead);
	if (bHole!=NULL)
		destroy_bitmap(bHole);
}

void Bot::init()
{
	punchTime.saveTime();

	bMatured=load_tga("Data\\hamster.tga", default_palette);
	if (bMatured==NULL)
		throw GameException("Error while loading hamster.tga.");

	bDead=load_tga("Data\\rip.tga", default_palette);
	if (bDead==NULL)
		throw GameException("Error while loading rip.tga.");

	bHole=load_tga("Data\\hamster_hole.tga", default_palette);
	if (bHole==NULL)
		throw GameException("Error while loading hamster_hole.tga.");
}

void Bot::Draw()
{
	if (this->deadMode)
		draw_trans_sprite(buff, bDead, pos.GetX()-(this->width/2), pos.GetY()+68-(this->height/2));
	else if (this->holeMode)
		draw_trans_sprite(buff, bHole, pos.GetX()-(this->width/2), pos.GetY()+68-(this->height/2));
	else if (!this->sleepMode)
		WorldComponent::Draw();

#ifdef _DEBUG
	BotNetworkWorldState state=this->ProduceState();
	for (int i=0;i<64;i++) {
		if (!state.obj[i].active)
			break;

		rect(buff, state.obj[i].x-16, state.obj[i].y-16+68, state.obj[i].x+16, state.obj[i].y+16+68, makecol(255, 255, 255));
	}
#endif
}

void Bot::ProcessNetwork()
{
	if (!botSocket->IsListening())
		botSocket->Restart();

	if (botSocket->IsListening()) {
		if (!botSocket->IsClientConntected())
			botSocket->Accept();

		if (botSocket->IsClientConntected()) {
			botSocket->socketTime.saveTime();

			BotNetworkWorldState worldState=ProduceState();
			if (!botSocket->Send(worldState)) {
				botSocket->Close();
				return;
			}

			BotNetworkAction action;
			if (!botSocket->Recv(&action)) {
				botSocket->Close();
				return;
			}

			BotNetworkReaction reaction=ProcessAction(action);
			if (!botSocket->Send(reaction)) {
				botSocket->Close();
				return;
			}

			BotNetworkHamsterState state;
			if (!botSocket->Recv(&state)) {
				botSocket->Close();
				return;
			}
			ProcessState(state);
		}
	}
}

void Bot::ProcessSpecial()
{
	if (this->sleepMode &&
		this->sleepTime.diffToCurrent()>=2000) {
		hHouse->sleepMode=false;
		this->sleepMode=false;
	}
	else if (this->holeMode &&
		this->holeTime.diffToCurrent()>=4000)
		this->holeMode=false;
}

void Bot::Process()
{
	WorldComponent::Process();
	ProcessSpecial();
	ProcessNetwork();
}

void Bot::ProcessActionExtra(WorldComponent* obj)
{
	if (obj->ClsID==house) {
		House* house=reinterpret_cast<House*>(obj);
		house->sleepMode=true;
		this->sleepMode=true;
		sleepTime.saveTime();
	}
	else if (obj->ClsID==hole) {
		this->holeMode=true;
		holeTime.saveTime();
		Ground::MarkPos(*this, 0);
		this->pos.SetX(obj->pos.GetX());
		this->pos.SetY(obj->pos.GetY());
		Ground::MarkPos(*this, 1);
	}
}

BotNetworkReaction Bot::ProcessAction(BotNetworkAction botAction)
{
	BotNetworkReaction botReaction;
	memset(&botReaction, 0, sizeof(botReaction));
	if (this->deadMode ||
		this->sleepMode ||
		this->holeMode) {
			botReaction.x=pos.GetX();
			botReaction.y=pos.GetY();
			return botReaction;
	}

	if (botAction.action==acMove) {
		Point oldPos;
		oldPos=pos;

		botAction.vx*=5;
		botAction.vy*=5;

		Ground::MarkPos(*this, 0);
		pos.SetX(pos.GetX()+botAction.vx);
		pos.SetY(pos.GetY()+botAction.vy);

		if (!Ground::AcceptObject(*this))
			pos=oldPos;
		else {
			if (botAction.vx!=0)
				angle=-64*(botAction.vx/4);
			else if (botAction.vy!=0)
				angle=(botAction.vy>0 ? 0 : 128);
		}
		Ground::MarkPos(*this, 1);
	}
	else {
		for (size_t i=0;i<objList.size();i++) {
			if (objList[i]->ObjID==botAction.objid) {
				botReaction=objList[i]->ProduceReaction();
				ProcessActionExtra(objList[i]);
				break;
			}
		}
	}

	botReaction.x=pos.GetX();
	botReaction.y=pos.GetY();

	if (punchTime.diffToCurrent()>=5000) {
		botReaction.diffHealth-=5;
		botReaction.diffHunger-=5;
		botReaction.diffSafety-=5;
		botReaction.diffSleep-=5;
		botReaction.diffThirst-=5;

		punchTime.saveTime();
	}

	return botReaction;
}

BotNetworkWorldState Bot::ProduceState()
{
	BotNetworkWorldState state;
	memset(&state, 0, sizeof(BotNetworkWorldState));
	int staten=0;
	int distance;
	Point dpos;
	dpos.SetX(pos.GetX());
	dpos.SetY(pos.GetY());

	for (size_t i=0;i<objList.size();i++) {
		if (objList[i]->state==unspawn)
			continue;
		Point opos;
		opos.SetX(objList[i]->pos.GetX());
		opos.SetY(objList[i]->pos.GetY());
		distance=opos.Distance(dpos);
		if (distance>=0 && distance<=64)
			state.obj[staten].active=true;
		state.obj[staten].distance=distance;
		state.obj[staten].clsid=objList[i]->ClsID;
		state.obj[staten].objid=objList[i]->ObjID;
		if (objList[i]->staticState && objList[i]->state!=unspawn)
			state.obj[staten].state=matured;
		else
			state.obj[staten].state=objList[i]->state;
		state.obj[staten].x=opos.GetX();
		state.obj[staten].y=opos.GetY();
		++staten;
	}
	sort(state.obj, state.obj+staten, botNetworkObjCmp);

	return state;
}

void Bot::ProcessState(BotNetworkHamsterState state)
{
	if (state.health<=0 ||
		state.hunger<=0 ||
		state.safety<=0 ||
		state.sleep<=0	||
		state.thirst<=0)
		this->deadMode=true;

	for (size_t i=0;i<uiList.size();i++)
		uiList[i]->ProcessState(state);
}

BotNetworkReaction Bot::ProduceReaction()
{
	BotNetworkReaction reaction;
	memset(&reaction, 0, sizeof(BotNetworkReaction));
	return reaction;
}

void Bot::GetRndPos(Point& rpos)
{
	if (house==NULL) {
		WorldComponent::GetRndPos(rpos);
		return;
	}

	rpos.SetX(hHouse->pos.GetX());
	rpos.SetY(hHouse->pos.GetY()+32);
}
