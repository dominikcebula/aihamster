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

#include "Game.h"
#include "GameException.h"
#include "Counter.h"
#include "Keyboard.h"
#include "Ground.h"
#include "Logo.h"
#include "UI.h"
#include "WorldComponents.h"
#include "Bot.h"

bool Game::end=false;
BITMAP* buff;

Game::Game()
{
	buff=NULL;
	Bot* bot=new Bot;

	componentList.push_back(new Keyboard);
	componentList.push_back(new Logo(Point(640, 8)));

	componentList.push_back(new UIHealth(Point(10, 5)));	bot->uiList.push_back(reinterpret_cast<UI*>(componentList.back()));
	componentList.push_back(new UISafety(Point(10, 25)));	bot->uiList.push_back(reinterpret_cast<UI*>(componentList.back()));
	componentList.push_back(new UISleep(Point(10, 45)));	bot->uiList.push_back(reinterpret_cast<UI*>(componentList.back()));
	componentList.push_back(new UIHunger(Point(300, 5)));	bot->uiList.push_back(reinterpret_cast<UI*>(componentList.back()));
	componentList.push_back(new UIThirst(Point(300, 25)));	bot->uiList.push_back(reinterpret_cast<UI*>(componentList.back()));
	
	componentList.push_back(new House);	bot->objList.push_back(reinterpret_cast<WorldComponent*>(componentList.back()));
	bot->hHouse=reinterpret_cast<House*>(componentList.back());
	componentList.push_back(bot);

	for (int i=0;i<3;i++) {
		componentList.push_back(new Apple);		bot->objList.push_back(reinterpret_cast<WorldComponent*>(componentList.back()));
		componentList.push_back(new Cucumber);	bot->objList.push_back(reinterpret_cast<WorldComponent*>(componentList.back()));
		componentList.push_back(new Tomato);	bot->objList.push_back(reinterpret_cast<WorldComponent*>(componentList.back()));
		componentList.push_back(new Flyagaric); bot->objList.push_back(reinterpret_cast<WorldComponent*>(componentList.back()));
		componentList.push_back(new Water);		bot->objList.push_back(reinterpret_cast<WorldComponent*>(componentList.back()));
		componentList.push_back(new Poison);	bot->objList.push_back(reinterpret_cast<WorldComponent*>(componentList.back()));
		componentList.push_back(new Hole);		bot->objList.push_back(reinterpret_cast<WorldComponent*>(componentList.back()));
	}
	
	componentList.push_back(new Ground);
}

Game::~Game()
{
	ComponentList::iterator it;
	while (componentList.size()>0) {
		it=componentList.begin();
		delete *it;
		componentList.pop_front();
	}

	if (buff!=NULL)
		destroy_bitmap(buff);
}

void Game::init()
{
	if (allegro_init()!=0)
		throw GameException("Error while allegro_init.");

	if (install_keyboard()!=0)
		throw GameException("Error while install_keyboard.");

	set_color_depth(32);
	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, resolution_width, resolution_height, 0, 0)!=0)
		throw GameException("Error while set_gfx_mode.");
	set_alpha_blender();

	buff=create_bitmap(SCREEN_W, SCREEN_H);

	ComponentList::iterator it;
	it=componentList.begin();
	while (it!=componentList.end()) {
		(*it)->init();
		it++;
	}
}

void Game::run()
{
	Time gtime;
	ComponentList::reverse_iterator it;

	while (!end) {
		gtime.saveTime();
		clear(buff);

		it=componentList.rbegin();
		while (it!=componentList.rend()) {
			(*it)->Process();
			it++;
		}

		it=componentList.rbegin();
		while (it!=componentList.rend()) {
			(*it)->Draw();
			it++;
		}

		blit(buff, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		gtime.sleepToCurrent();
	}
}
