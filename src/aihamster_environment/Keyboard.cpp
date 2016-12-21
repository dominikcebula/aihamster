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

#include <allegro.h>
#include "Keyboard.h"
#include "Game.h"
#include "Network.h"

#ifdef _DEBUG
#include "Bot.h"
#endif

#ifdef _DEBUG
#define STATE_CHCK(OBJ, ITM) if (OBJ.ITM<0) OBJ.ITM=0; if (OBJ.ITM>100) OBJ.ITM=100;
#endif

void Keyboard::Process()
{
	if (key[KEY_ESC])
		Game::end=true;

#ifdef _DEBUG
	static BotNetworkHamsterState hstate;
	static bool stateInit=false;
	if (!stateInit) {
		hstate.health=50;
		hstate.hunger=50;
		hstate.safety=50;
		hstate.sleep=50;
		hstate.thirst=50;

		stateInit=true;
	}
	STATE_CHCK(hstate, health);
	STATE_CHCK(hstate, hunger);
	STATE_CHCK(hstate, safety);
	STATE_CHCK(hstate, sleep);
	STATE_CHCK(hstate, thirst);
	ptrbot->ProcessState(hstate);

	if (ptrbot==NULL)
		return;

	BotNetworkAction act;
	memset(&act, 0, sizeof(BotNetworkAction));
	act.action=acMove;
	if (key[KEY_LEFT])
		act.vx=-1;
	else if (key[KEY_RIGHT])
		act.vx=1;
	else if (key[KEY_UP])
		act.vy=-1;
	else if (key[KEY_DOWN])
		act.vy=1;
	else if (key[KEY_SPACE]) {
		BotNetworkWorldState state=ptrbot->ProduceState();
		if (state.obj[0].active) {
			act.action=acUse;
			act.objid=state.obj[0].objid;
		}
	}
	BotNetworkReaction reaction=ptrbot->ProcessAction(act);

	hstate.health+=reaction.diffHealth;
	hstate.hunger+=reaction.diffHunger;
	hstate.safety+=reaction.diffSafety;
	hstate.sleep+=reaction.diffSleep;
	hstate.thirst+=reaction.diffThirst;
#endif
}
