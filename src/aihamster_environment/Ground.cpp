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

#include "Ground.h"
#include "Game.h"
#include "GameException.h"

bool Ground::GroundMap[GroundMapX][GroundMapY];

Ground::Ground()
{
	ground=NULL;

	for (int i=0;i<GroundMapX;i++)
		for (int j=0;j<GroundMapY;j++)
			GroundMap[i][j]=0;
}


Ground::~Ground()
{
	if (ground!=NULL)
		destroy_bitmap(ground);
}

bool Ground::AcceptObject(BoundingBox& box)
{
	int ptlx, ptrx, pblx, pbrx;
	int ptly, ptry, pbly, pbry;
	ptlx=box.pos.GetX()-(box.GetWidth()/2);	ptly=box.pos.GetY()-(box.GetWidth()/2);
	ptrx=box.pos.GetX()+(box.GetWidth()/2);	ptry=box.pos.GetY()-(box.GetWidth()/2);
	pblx=box.pos.GetX()-(box.GetWidth()/2);	pbly=box.pos.GetY()+(box.GetHeight()/2);
	pbrx=box.pos.GetX()+(box.GetWidth()/2);	pbry=box.pos.GetY()+(box.GetHeight()/2);

	if (ptlx<0 || ptlx>=Ground::GroundMapX ||
		ptrx<0 || ptrx>=Ground::GroundMapX ||
		pblx<0 || pblx>=Ground::GroundMapX ||
		pbrx<0 || pbrx>=Ground::GroundMapX ||
		ptly<0 || ptly>=Ground::GroundMapY ||
		ptry<0 || ptry>=Ground::GroundMapY ||
		pbly<0 || pbly>=Ground::GroundMapY ||
		pbry<0 || pbry>=Ground::GroundMapY)
		return false;

	if (!GroundMap[ptlx][ptly] &&
		!GroundMap[ptrx][ptry] &&
		!GroundMap[pblx][pbly] &&
		!GroundMap[pbrx][pbry])
		return true;
	else
		return false;
}

void Ground::init()
{
	ground=load_tga("Data\\ground.tga", default_palette);
	if (ground==NULL)
		throw GameException("Error while loading ground.tga.");
}

void Ground::Draw()
{
	if (ground!=NULL)
		blit(ground, buff, 0, 0, 0, 68, Ground::GroundMapX, Ground::GroundMapY);
}

void Ground::MarkPos(BoundingBox& box, bool flag)
{
	for (int i=box.pos.GetX()-(box.GetWidth()/2);i<box.pos.GetX()+(box.GetWidth()/2);i++) {
		for (int j=box.pos.GetY()-(box.GetHeight()/2);j<box.pos.GetY()+(box.GetHeight()/2);j++) {
			if (i>=0 && i<Ground::GroundMapX &&
				j>=0 && j<Ground::GroundMapY)
				GroundMap[i][j]=flag;
		}
	}
}
