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
#include <list>
#include "GameComponent.h"

typedef std::list<GameComponent*> ComponentList;

extern BITMAP* buff;

class Game
{
	ComponentList componentList;
public:
	static const int resolution_width = 1024;
	static const int resolution_height = 768;
	static bool end;

	Game();
	~Game();

	void init();
	void run();
};
