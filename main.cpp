#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <map>
#include <conio.h>
using namespace std;

int main()
{
    //sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::UdpSocket socket;
    std::string connectionType ="";
    std::string serverCheck ="server";
    std::string serverCheckShort ="s";
    std::string clientCheckShort ="c";
    std::string clientCheck ="client";
    char buffer[2000];

    std::size_t received;
    std::map<unsigned short, sf::IpAddress> computerID;
    std::string text = "Connected to: ";

    std::cout <<"Enter (server) for server, Enter (client) for client: \n";
    std::cin >> connectionType;


    unsigned short port;

    std::cout << "set port number: ";
    std::cin >> port;

    socket.bind(port);

    if(connectionType==serverCheckShort || connectionType==serverCheck)
    {
            std::cout<<"Please type (ready) if everyone is ready: \n";
            std::string answer="a";
            while(answer != "r" && answer !="ready")
            {
                sf::IpAddress rIp;
                unsigned short port;
                socket.receive(buffer,sizeof(buffer), received, rIp, port);
                if(received >0)
                {
                    std::cout<<"connected \n";
                    computerID[port] = rIp;
                }
                std::cin >> answer;
            }
    }
    if(connectionType==clientCheckShort || connectionType==clientCheck)
    {
        std::string sIP;
        std::cout << "Enter server ip: ";
        std::cin>> sIP;
        sf::IpAddress sendIP(sIP);
        socket.send(text.c_str(), text.length() +1, sendIP, 2000);
    }

    bool done=false;
    while(done==false)
    {
        if(connectionType==serverCheckShort || connectionType==serverCheck)
        {
            std::getline(cin, text);
            std::map<unsigned short, sf::IpAddress>::iterator tempIterator;
            for(tempIterator = computerID.begin(); tempIterator != computerID.end(); ++tempIterator)
            {
                socket.send(text.c_str(), text.length() +1, tempIterator->second, tempIterator->first);
            }
        }
        if(connectionType==clientCheckShort || connectionType==clientCheck)
        {
            sf::IpAddress tempIp;
            unsigned short tempPort;
            socket.receive(buffer, sizeof(buffer), received, tempIp, tempPort);
            if(received>0)
            {
                std::cout << "Received: " <<buffer << "\n";
            }
        }
    }
    return 0;
}
