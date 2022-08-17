
#ifndef CHAT_USERMODEL_H
#define CHAT_USERMODEL_H

#include "server/model/user.h"

//User表的数据操作类
class UserModel
{
public:
    //User表的增加方法
    bool insert(User &user);

    //根据用户号码查询用户信息
    User query(int id);

    //更新用户的状态信息
    bool updateState(User user);

    //重置用户的状态信息
    void resetState();
};

#endif //CHAT_USERMODEL_H
