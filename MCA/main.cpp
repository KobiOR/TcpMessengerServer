
#include <iostream>
#include "TcpCLientMessenger.h"
#include "../SocketUtils/TCPMessengerProtocol.h"

using namespace std;
using  namespace npl;

void instructions(){
	cout<<" To connect: c <ip>" <<endl;
	cout<<" To login: login <username> <password>" <<endl;
	cout<<" To register type: register <username> <password>" <<endl;
	cout<<" To open private chat type:op <username>" <<endl;
	cout<<" To open new room: or <chatroomname>" <<endl;
	cout<<" To login to specific room: o <chatroomname>" <<endl;
	cout<<" To send a message: s <message>" <<endl<<endl;
	cout<<" To get the user list from the server type:: lu" <<endl;
	cout<<" To get the connected users type: lcu" <<endl;
	cout<<" print all rooms: lr" <<endl;
	cout<<" print all users in this room: lru <roomname>" <<endl;
	cout<<" print the current status of the client: l" <<endl;
	cout<<" disconnect the open session / exit from a room: cs" <<endl;
	cout<<" disconnect from server: d" <<endl;
	cout<<" close the app: x" <<endl;
	cout<<" Close room: cr <chatroomname>" <<endl;


}
int main() {
	cout<<" Welcome to the client chat "<<endl;

	instructions();
	TcpCLientMessenger clientManager;
	bool running = true;

	while(running)
	{
		string command, parameter1, parameter2,answer;
		cin >> command;

		if(command == "c")
		{
			cin >> parameter1;
			if(clientManager.connectToServer(parameter1,MSNGR_PORT))
				cout << "connected to: " << parameter1 << endl;
			else
				cout<<"connection failed"<<endl;
		}
		else if(command=="login")
		{
			cin >> parameter1;
			cin >> parameter2;
			clientManager.log(parameter1,parameter2,LOGIN_REQUEST);
		}
		else if(command=="register")
		{
			cin >> parameter1;
			cin >> parameter2;
			if (clientManager.isLogin()==true){
				cout<<"You allready connected!"<<endl;
			}
			else{
			clientManager.sign(parameter1,parameter2,SIGNUP_REQUEST);
			cout<<"Please login with your new name& password"<<endl;
			}
		}
		else if(command == "op")
		{
			cin >> parameter1;
			clientManager.openSession(parameter1);
		}
		else if(command == "l")
		{
			clientManager.printCurrentInfo();
		}
		else if(command == "s")
		{
			cin >> parameter1;
			if(!clientManager.sendMsg(parameter1))
			cout<<"you need to create a session or login to a room first"<<endl;
		}
		else if(command == "or")
		{
			cin >> parameter1;
			if (!clientManager.createChatRoom(parameter1))
				cout<<"You cannot create room in current status, check if you are connected"<<endl;
			else
				clientManager.loginToChatRoom(parameter1);
		}
		else if(command == "o")
		{
			cin >> parameter1;
			if (!clientManager.loginToChatRoom(parameter1))
				cout<<"Cannot connect to the room, check if you already logged in."<<endl;
		}
		else if(command == "lu")
		{
			clientManager.listUsers();
		}
		else if(command == "lcu")
		{
			clientManager.prinCtonnectedUsers();
		}
		else if(command == "lr")
		{
			clientManager.RoomsList();
		}
		else if(command == "lru")
		{

			cin >> parameter1;
            if (parameter1.empty())
                cout<<"Please insert room name!\n";
            else
			clientManager.listConnectedUsersInRoom(parameter1);
		}
		else if(command == "cs")
		{
			if(!clientManager.exitRoomOrCloseSession())
				cout<<"There is not session or room to exit from him."<<endl;
		}
		else if(command == "cr")
		{
			cin >> parameter1;
			if (!clientManager.deleteChatRoom(parameter1))
				cout<<"You cannot delete the room"<<endl;
		}
		else if(command == "d")
		{
			clientManager.exitAll();
			cout<<"You logged out from server"<<endl;
		}
		else if(command == "x")
		{
			clientManager.exitAll();
			cout<<"shutting down..."<<endl;
			running=false;
		}
		else
		{
			cout<<"invalid command"<<endl;
		}
	}
}


