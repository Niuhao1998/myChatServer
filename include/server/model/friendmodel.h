#ifndef CHAT_FRIENDMODEL_H
#define CHAT_FRIENDMODEL_H

#include "user.h"
#include <vector>
using namespace std;

//维护好友信息的操作接口方法
class FriendModel
{
public:
    //添加好友关系
    void insert(int userid,int friendid);

    //返回用户好友列表  friendid
    vector<User> query(int userid);
};

#endif
