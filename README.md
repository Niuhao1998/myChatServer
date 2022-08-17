# myChatServer
工作在nginx tcp负载均衡环境中的集群聊天服务器和客户端代码源码  基于muduo库实现 redis  mysql

编译方式
cd build
rm -rf *
cmake ..
make

#Mysql表设计
User表
|字段名称|字段类型|字段说明|约束|
|:-----|:----------:|------------:|----------:|
|id|INT|用户id|PRIMARY KEY、AUTO_INCREMENT|
|name|VATCHAR(50)|用户名|NOT NULL,UNIQUE|
|password|VARCHAR(50)|用户密码|NOT NULL|
|state|ENUM('online','offline')|当前登录状态|DEFAULT 'offline'|

Friend表
|字段名称|字段类型|字段说明|约束|
|:-----|:----------:|------------:|----------:|
|userid|INT|用户id|NOT NULL、联合主键|
|friend|INT|好友id|NOT NULL、联合主键|

AllGroup表
|字段名称|字段类型|字段说明|约束|
|:-----|:----------:|------------:|----------:|
|id|INT|组id|PRIMARY KEY、AUTO_INCREMENT|
|groupname|VARCHAR(50)|组名称|NOT NULL|
|groupdesc|VARCHAR(200)|组功能描述|DEFAULT ''|

GroupUser表
|字段名称|字段类型|字段说明|约束|
|:-----|:----------:|------------:|----------:|
|groupid|INT|组id|NOT NULL、联合主键|
|userid|INT|组员id|NOT NULL、联合主键|
|groupid|ENUM('creator','normal')|组内角色|DEFAULT 'normal'|

OfflineMessage表
|字段名称|字段类型|字段说明|约束|
|:-----|:----------:|------------:|----------:|
|userid|INT|用户id|NOT NULL|
|message|VARCHAR(50)|离线消息|NOT NULL|


#需要nginx的负载均衡配置,nginx.conf中进行设置。
'''
stream{
   upstream MyServer {
                server ip地址:端口 weight=1 max_fails=3 fail_timeout=30s;
                server ip地址:端口 weight=1 max_fails=3 fail_timeout=30s;
        }

    server{
                proxy_connect_timeout 1s;
                listen 8000;
                proxy_pass MyServer;
                tcp_nodelay on;
           }
}
'''
