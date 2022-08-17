#ifndef CHAT_GROUOPMODEL_H
#define CHAT_GROUOPMODEL_H

#include "group.h"
#include <string>
#include <vector>
using namespace std;

class GroupModel
{
public:
    //创建群组
    bool CreateGroup(Group &group);
    //加入群组
    void AddGroup(int userid,int groupid,string role);
    //查询用户所在群组信息
    vector<Group> queryGroups(int userid);
    //根据指定groupid查询群组用户id列表，除userid自己
    static vector<int> queryGroupUsers(int userid,int groupid);
};

#endif
