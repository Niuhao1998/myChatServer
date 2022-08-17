
/*
 * muduo网络库给永华提供了两个主要的类
 * TcpServer:用于编写服务器程序
 * TcpClient:用于编写客户端程序
 * epoll+线程池
 * 好处：能够把网络I/O的代码和业务代码区分开
 *                          用户的连接和断开    用户的可读写事件
 * */

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <string>
#include <functional>
using namespace std;
using namespace placeholders;
using namespace muduo;
using namespace muduo::net;
//基于muduo网络库开发服务器程序
/*
 * 组合TcpServer对象
 * 创建EventLoop事件循环对象的指针
 * 明确TcpServer构造函数需要什么参数，输出ChatServer的构造哈数
 * 在当前服务器类的构造函数当中，注册处理连接的回调函数和处理读写事件的回调函数
 * 设置合适的服务端线程数量，muduo库会自己划分I/O线程和worker线程
 * */
class ChatServer
{
public:
    ChatServer(EventLoop *loop, //事件循环
                const InetAddress &listenAddr,  //ip+port
                const string &nameArg   //服务器的名字
            ):_server(loop,listenAddr,nameArg),_loop(loop)
            {
                //给服务器注册用户连接的创建和断开回调
                _server.setConnectionCallback(bind(&ChatServer::onConnection,this,_1));
                //给服务器注册用户读写事件回调
                _server.setMessageCallback(bind(&ChatServer::onMessage,this,_1,_2,_3));
                //设置服务器端的线程数量   1个IO线程，3个worker线程
                _server.setThreadNum(4);
            }
    void start()
        {
            _server.start();
        }
private:
    //专门处理用户的创建和断开
    void onConnection(const TcpConnectionPtr &conn)
    {
            if(conn->connected())
            {
                cout<<conn->peerAddress().toIpPort()<<" -> "<<
                    conn->localAddress().toIpPort()<<" state:online"<<endl;
            }
            else
            {
                cout<<conn->peerAddress().toIpPort()<<" -> "<<
                    conn->localAddress().toIpPort()<<" state:offline"<<endl;
                conn->shutdown();   //close(fd)
                //_loop->quit();    //连接断开，回收资源
            }
    }

    void onMessage(
            const TcpConnectionPtr &conn,   //连接
            Buffer *buffer,    //缓冲区
            Timestamp time) //接受到数据的时间信息
    {
        string buf=buffer->retrieveAllAsString();
        cout<<"recv data:"<<buf<<" "<<"time:"<<time.toString()<<endl;
        conn->send(buf);
    }

    TcpServer _server;  //#1
    EventLoop *_loop;   //#2 epoll
};

int main()
{
    EventLoop loop; //epoll
    InetAddress addr("127.0.0.1",6000);
    ChatServer server(&loop,addr,"ChatServer");

    server.start(); //listenfd epoll_ctl=>epoll
    loop.loop();    //epoll_wait 以阻塞方式等待新用户连接，已连接用户的读写事件等操作

    return 0;
}