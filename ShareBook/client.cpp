#include "client.h"

using json=nlohmann::json;
#define MAX 20
Client* Client::m_instance = nullptr;


Client *Client::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new Client();
    }
    return m_instance;

}

Client::Client()
{
    //这里客户端初始化建立连接
    char ipaddr[MAX] ={"192.168.121.249"};
    m_network.createSocket();
    m_network.connectSocket(ipaddr);
    std::cout<<"Client"<<"客户端建立连接，初始化数据中......"<<std::endl;

}

void Client::send( const char *buf, size_t size)
{
    m_network.sendMessage(buf,size);
}

void Client::sendFile(char *buf,size_t size,std::string filePath)
{
    m_network.sendFile(buf,size,filePath);
}

bool Client::receive(char * buf)
{
    return m_network.receiveMessage(buf);
}

void Client::reconnect()
{
    m_network.closeSocket();

    //这里客户端初始化建立连接
    char ipaddr[MAX] ={"192.168.121.249"};
    m_network.createSocket();
    m_network.connectSocket(ipaddr);
    std::cout<<"Client"<<"客户端重新建立连接，初始化数据中......"<<std::endl;

}

std::string Client::receiveFile()
{
    return m_network.receiveFile();
}

Client::~Client()
{
     m_network.closeSocket();
}
