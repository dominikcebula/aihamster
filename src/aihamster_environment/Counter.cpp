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

#include <cstdio>
#include "Counter.h"
#include "Font.h"
#include "Game.h"

Counter::Counter()
{
	frames=0;
	fps=0;
	ctime.saveTime();
}


Counter::~Counter()
{
}

void Counter::Process()
{
	frames++;

	aitime diff=ctime.diffToCurrent();
	diff/=1000;
	if (diff>2) {
		fps=frames/diff;
		frames=0;
		ctime.saveTime();
	}
}

void Counter::Draw()
{
	Font font=Font::getInstance();
	textprintf(buff, *font, 0, 0, makecol(255,255,0), "%d", fps);
}
