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

#include "BotSocket.h"
#include <winsock.h>

BotSocket::BotSocket(void)
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	serverSocket=INVALID_SOCKET;
	clientSocket=INVALID_SOCKET;
}

BotSocket::~BotSocket(void)
{
	Close();
	WSACleanup();
}

void BotSocket::Open()
{
	serverSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket==INVALID_SOCKET)
		return;

	sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(35000);

    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service))==SOCKET_ERROR) {
		Close();
		return;
	}

	if (listen(serverSocket, 1) == SOCKET_ERROR) {
        Close();
		return;
	}

	u_long argp;
	argp=1;
	if (ioctlsocket(serverSocket, FIONBIO, &argp)!=0) {
		Close();
		return;
	}
}

void BotSocket::Close()
{
	if (clientSocket!=INVALID_SOCKET) {
		closesocket(clientSocket);
		clientSocket=INVALID_SOCKET;
	}
	if (serverSocket!=INVALID_SOCKET) {
		closesocket(serverSocket);
		serverSocket=INVALID_SOCKET;
	}
}

void BotSocket::Restart()
{
	Close();
	Open();
}

void BotSocket::Accept()
{
	if (clientSocket!=INVALID_SOCKET)
		closesocket(clientSocket);
	clientSocket=accept(serverSocket, NULL, NULL);
}

bool BotSocket::IsClientConntected()
{
	if (clientSocket==INVALID_SOCKET)
		return false;

	if (send(clientSocket, NULL, 0, 0)==SOCKET_ERROR && WSAGetLastError()!=WSAEWOULDBLOCK)
		return false;

	if (recv(clientSocket, NULL, 0, 0)==SOCKET_ERROR && WSAGetLastError()!=WSAEWOULDBLOCK)
		return false;

	return true;
}

bool BotSocket::IsListening()
{
	return serverSocket!=INVALID_SOCKET;
}

bool BotSocket::Send(char* src, int len)
{
	if (send(clientSocket, src, len, 0)!=SOCKET_ERROR)
		return true;
	else
		return false;
}

bool BotSocket::Send(BotNetworkWorldState state)
{
	bool ret=false;
	char* buff=new char[sizeof(BotNetworkWorldState)];
	memcpy(buff, &state, sizeof(BotNetworkWorldState));
	ret=Send(buff, sizeof(BotNetworkWorldState));
	delete[] buff;
	return ret;
}

bool BotSocket::Recv(char* dst, int len)
{
	const aitime wait_time=28;
	int st=0;
	int pos=0;
	memset(dst, 0, len);
	char* buff=new char[len];
	while (1) {
		st=recv(clientSocket, buff, len, 0);
		if (st==SOCKET_ERROR && 
			WSAGetLastError()==WSAEWOULDBLOCK &&
			socketTime.diffToCurrent()<=wait_time)
			continue;
		else if (st==SOCKET_ERROR ||
			     st==0 ||
			     socketTime.diffToCurrent()>wait_time) {
			delete[] buff;
			return false;
		}
		else if (st>0) {
			memcpy(dst+pos, buff, st);
			pos=pos+st;
		}

		if (pos==len) {
			delete[] buff;
			return true;
		}
	}

	delete[] buff;
	return false;
}

bool BotSocket::Recv(BotNetworkAction* action)
{
	return Recv(reinterpret_cast<char*>(action), sizeof(BotNetworkAction));
}

bool BotSocket::Send(BotNetworkReaction reaction)
{
	bool ret=false;
	char* buff=new char[sizeof(BotNetworkReaction)];
	memcpy(buff, &reaction, sizeof(BotNetworkReaction));
	ret=Send(buff, sizeof(BotNetworkReaction));
	delete[] buff;
	return ret;
}

bool BotSocket::Recv(BotNetworkHamsterState* state)
{
	return Recv(reinterpret_cast<char*>(state), sizeof(BotNetworkHamsterState));
}
