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

#include "Logo.h"
#include "Game.h"
#include "GameException.h"


Logo::Logo()
{
	logo=NULL;
}

Logo::Logo(Point& pos)
{
	logo=NULL;
	this->pos=pos;
}

Logo::~Logo()
{
	if (logo!=NULL)
		destroy_bitmap(logo);
}

void Logo::Draw()
{
	if (logo!=NULL)
		blit(logo, buff, 0, 0, pos.GetX(), pos.GetY(), 355, 51);
}

void Logo::init()
{
	logo=load_tga("Data\\logo.tga", default_palette);
	if (logo==NULL)
		throw GameException("Error while loading logo.tga.");
}