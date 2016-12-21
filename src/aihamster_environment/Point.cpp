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

#include <cmath>
#include "Point.h"

Point::Point()
{
	this->x=0;
	this->y=0;
}

Point::Point(int x, int y)
{
	this->x=x;
	this->y=y;
}

void Point::SetX(int x)
{
	this->x=x;
}

int Point::GetX()
{
	return this->x;
}

void Point::SetY(int y)
{
	this->y=y;
}

int Point::GetY()
{
	return this->y;
}

int Point::Distance(Point& p)
{
	double pa, pb;
	pa=pow(static_cast<double>(p.GetX()-this->GetX()), 2);
	pb=pow(static_cast<double>(p.GetY()-this->GetY()), 2);
	return static_cast<int>(sqrt(pa+pb));
}

Point operator+(Point& left, Point &right)
{
	Point p;
	p.SetX(left.x+right.x);
	p.SetY(left.y+left.y);
	return p;
}

Point operator-(Point& left, Point &right)
{
	Point p;
	p.SetX(left.x-right.x);
	p.SetY(left.y-left.y);
	return p;
}
