

#include <iostream>
#include <thread>
#include "ppconsul/consul.h"
#include "workflow/WFTaskFactory.h"
#include "ppconsul/agent.h"
#include "workflow/WFHttpServer.h"

using std::cout;
using std::endl;

auto serviceId = "consul-demo-service";



int main()
{
    //将本服务注册到consul之中
    //找到dc1注册中心
    ppconsul::Consul consul("127.0.0.1:8500",ppconsul::kw::dc = "dc1");
    //创建一个用来访问注册中心的agent
    ppconsul::agent::Agent agent(consul);
//    auto tags = std::set<std::string>();
    agent.registerService(
            ppconsul::agent::kw::name = serviceId,
            ppconsul::agent::kw::address = "127.0.0.1",
            ppconsul::agent::kw::id = serviceId,
            ppconsul::agent::kw::port = 1412,
            ppconsul::agent::kw::tags = {"cpp-consul-demo"},
            ppconsul::agent::kw::meta = {{"meta1", "cpp-consul-demo"}},
            ppconsul::agent::kw::check = ppconsul::agent::TcpCheck{"127.0.0.1:8500", std::chrono::seconds(10)} // 只做模拟操作，用的consul本身的地址
            );

//    std::this_thread::sleep_for(std::chrono::milliseconds(60000));
    getchar();
    agent.deregisterService(serviceId);

    std::cout << "Waited 3 seconds!" << std::endl;

}
