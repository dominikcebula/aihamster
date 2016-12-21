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

#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
	height=0;
	width=0;
}

void BoundingBox::SetWidth(int width)
{
	this->width=width;
}

int BoundingBox::GetWidth()
{
	return this->width;
}

void BoundingBox::SetHeight(int height)
{
	this->height=height;
}

int BoundingBox::GetHeight()
{
	return this->height;
}

bool BoundingBox::CollisionPoint(Point& p)
{
	Point vx, vy;
	Point left, right, up, down;
	vx.SetX(this->width/2);
	vy.SetY(this->height/2);
	up=this->pos-vy;
	down=this->pos+vy;
	left=this->pos-vx;
	right=this->pos+vx;

	if (p.GetX()>=left.GetX() && p.GetY()<=right.GetX() &&
		p.GetY()>=up.GetY() && p.GetY()<=down.GetY())
		return true;
	else
		return false;
}

bool BoundingBox::Collision(BoundingBox& box)
{
	Point vx, vy;
	Point lu, ru, ld, rd;

	vx.SetX(box.width/2);
	vy.SetY(box.height/2);
	lu=box.pos-vx+vy;
	ru=box.pos+vx-vy;
	ld=box.pos-vx+vy;
	rd=box.pos+vx+vy;

	if (this->CollisionPoint(lu) ||
		this->CollisionPoint(ru) ||
		this->CollisionPoint(ld) ||
		this->CollisionPoint(rd))
		return true;
	else
		return false;
}
