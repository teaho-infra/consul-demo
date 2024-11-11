

#include <iostream>
#include <thread>
#include "ppconsul/consul.h"
#include "workflow/WFTaskFactory.h"
#include "ppconsul/agent.h"
#include "ppconsul/types.h"
#include "ppconsul/kv.h"
#include "workflow/WFHttpServer.h"

using std::cout;
using std::endl;

auto port = 8110;


int main()
{
    //将本服务注册到consul之中
    //找到dc1注册中心
    ppconsul::Consul consul("127.0.0.1:8500",ppconsul::kw::dc = "dc1");
    // We need the 'kv' endpoint
    ppconsul::kv::Kv kv(consul);

    // Read the value of a key from the storage
    std::string configuration = kv.get("apps/kvMain::dev/configuration", "default-value");


    std::cout << configuration << std::endl;

    // Read the value of a key from the storage with consistency mode specified
    configuration = kv.get("apps/kvMain::dev/configuration", "default-value", ppconsul::kw::consistency = ppconsul::Consistency::Default);

    std::cout << configuration << std::endl;

    // Erase a key from the storage
    kv.erase("apps/kvMain::dev/configuration2");

    // Set the value of a key
    kv.set("apps/kvMain::dev/configuration2", "new-value");


    std::cout << "Ending!" << std::endl;

}
