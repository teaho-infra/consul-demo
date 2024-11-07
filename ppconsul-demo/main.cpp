

#include <iostream>
#include "ppconsul/consul.h"
#include "workflow/WFTaskFactory.h"
#include "ppconsul/agent.h"
#include <iostream>
using std::cout;
using std::endl;


//维持节点健康
void timerCallback(WFTimerTask* timerTask){
    ppconsul::agent::Agent *pagent = static_cast<ppconsul::agent::Agent*>(timerTask->user_data);
    pagent->servicePass("SignupServicel");
    auto nextTask = WFTaskFactory::create_timer_task(5000000,timerCallback);
    cout << nextTask << endl;
    nextTask->user_data = pagent;
    series_of(timerTask)->push_back(nextTask);
}

int main()
{
    //将本服务注册到consul之中
    //找到dc1注册中心
    ppconsul::Consul consul("127.0.0.1:8500",ppconsul::kw::dc = "dc1");
    //创建一个用来访问注册中心的agent
    ppconsul::agent::Agent agent(consul);

    agent.registerService(
            ppconsul::agent::kw::name = "SignupServicel",
            ppconsul::agent::kw::address = "127.0.0.1",
            ppconsul::agent::kw::id = "SignupServicel",
            ppconsul::agent::kw::port = 1412);
    agent.servicePass("SignupServicel");//设置健康服务(心跳)
    auto timerTask = WFTaskFactory::create_timer_task(1000,timerCallback);
    timerTask->user_data = &agent;
    timerTask->start();
}
