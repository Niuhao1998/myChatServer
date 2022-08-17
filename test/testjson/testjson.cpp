//
// Created by Administrator on 2022/8/13.
//
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "json.hpp"

using json=nlohmann::json;
using namespace std;

//json序列化例1
string func1()
{
    json js;
    js["msg_type"]=2;
    js["from"]="zhang san";
    js["to"]="li si";
    js["msg"]="hello, whar are you doing now?";
    string sendBuf=js.dump();
    return sendBuf;
}

//序列化示例2
string func2()
{
    json js;
    js["id"]={1,2,3,4,5};
    js["msg_type"]=2;
    js["from"]="zhang san";
    js["to"]="li si";
    js["msg"]="hello, whar are you doing now?";
    return js.dump();
}

//json序列化示例代码3
string func3()
{
    json js;
// 直接序列化一个vector容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);
    js["list"] = vec;
// 直接序列化一个map容器
    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});
    js["path"] = m;
    string sendBuf=js.dump();   //json的数据对象=》序列化成json字符串
    //cout<<sendBuf<<endl;
    return sendBuf;
}

int main()
{
    string recvBuf=func3();
    //数据的反序列化   json字符串反序列化成数据对象（看作容器，方便放人）
    json jsbuf=json::parse(recvBuf);
  /*  cout<<jsbuf["msg_type"]<<endl;
    cout<<jsbuf["from"]<<endl;
    cout<<jsbuf["to"]<<endl;
    cout<<jsbuf["msg"]<<endl;
*/

  /*
   * cout<<jsbuf["id"]<<endl;
*/

    vector<int> vec=jsbuf["list"];  //js对象里面的数组类型，直接放入vector容器当中
    for(int &v : vec){
        cout<<v<<" ";
    }
    cout<<endl;

    map<int,string> mymap=jsbuf["path"];
    for(auto &p : mymap)
    {
        cout<<p.first<<" "<<p.second<<endl;
    }
    cout<<endl;

    return 0;
}