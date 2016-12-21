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

#include "Time.h"

Time::Time()
{
	savedTime=0;
}


Time::~Time()
{
}

void Time::saveTime()
{
	getTime(&savedTime);
}

void Time::sleepToCurrent()
{
	aitime diff=diffToCurrent();
	if (diff<30) {
		diff=30-diff;
		if (diff>0)
			Sleep(diff);
	}
}

aitime Time::diffToCurrent()
{
	aitime currTime, diff;
	getTime(&currTime);
	diff=currTime-savedTime;
	return diff;
}

void Time::getTime(aitime* dst)
{
	FILETIME tm;
	GetSystemTimeAsFileTime(&tm);
	BYTE* p;
	p=reinterpret_cast<BYTE*>(dst);
	memcpy_s(p, 4, &tm.dwLowDateTime, 4);
	memcpy_s(p+4, 4, &tm.dwHighDateTime, 4);
	*dst/=10000;
}
