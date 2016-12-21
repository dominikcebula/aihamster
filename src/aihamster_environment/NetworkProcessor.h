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

class NetworkProcessorBot {
public:
	virtual BotNetworkReaction ProcessAction(BotNetworkAction botAction) = 0;
};

class NetworkProcessorWorld {
public:
	virtual BotNetworkWorldState ProduceState() = 0;
};

class NetworkProcessorState {
public:
	virtual void ProcessState(BotNetworkHamsterState state) = 0;
};

class NetworkProcessorReaction {
public:
	virtual BotNetworkReaction ProduceReaction() = 0;
};
