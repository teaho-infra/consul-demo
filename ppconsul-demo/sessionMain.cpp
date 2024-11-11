

#include <iostream>
#include <thread>
#include <ctime>
#include "ppconsul/consul.h"
#include "workflow/WFTaskFactory.h"
#include "ppconsul/agent.h"
#include "ppconsul/kv.h"
#include "ppconsul/sessions.h"
#include "workflow/WFHttpServer.h"

using std::cout;
using std::endl;
using ppconsul::sessions::kw::name;
using ppconsul::sessions::kw::ttl;

auto port = 8110;


auto checkId = "session-test";
auto lockKey = "test-session";

int main()
{
    //将本服务注册到consul之中
    //找到dc1注册中心
    ppconsul::Consul consul("127.0.0.1:8500",ppconsul::kw::dc = "dc1");

    ppconsul::sessions::Sessions sessions(consul);
    ppconsul::kv::Kv kv(consul);

//    kw::groups::put, kw::name, kw::node, kw::lock_delay, kw::behavior, kw::ttl
    auto sessionId = sessions.create(name = checkId, ttl = std::chrono::seconds(600));
    std::cout << "Session created!" << std::endl;


    for (int i = 0; i < 2; ++i) {
        // 获取当前时间
        time_t now = time(0);
        // 转换为字符串形式
        char* dt = ctime(&now);
        kv.lock(lockKey, sessionId, dt);
    }

    getchar();

    sessions.destroy(sessionId);


    std::cout << "Ending!" << std::endl;

}
