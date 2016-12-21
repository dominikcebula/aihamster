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

#include "Network.h"
#include "Time.h"

class BotSocket
{
	unsigned int __w64 serverSocket;
	unsigned int __w64 clientSocket;
public:
	Time socketTime;

	BotSocket();
	~BotSocket();

	void Open();
	void Close();
	void Restart();
	void Accept();
	bool IsListening();
	bool IsClientConntected();

	bool Send(char* src, int len);
	bool Send(BotNetworkWorldState state);
	bool Recv(char* dst, int len);
	bool Recv(BotNetworkAction* action);
	bool Send(BotNetworkReaction reaction);
	bool Recv(BotNetworkHamsterState* state);
};
