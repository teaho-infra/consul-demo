

#include <iostream>
#include <thread>
#include "ppconsul/consul.h"
#include "workflow/WFTaskFactory.h"
#include "ppconsul/agent.h"
#include "workflow/WFHttpServer.h"

using std::cout;
using std::endl;

auto serviceId = "consul-demo-service";
auto port = 8110;


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
            ppconsul::agent::kw::port = port,
            ppconsul::agent::kw::tags = {"cpp-consul-demo", "v1"},
            ppconsul::agent::kw::meta = {{"meta1", "cpp-consul-demo"}},
            ppconsul::agent::kw::check = ppconsul::agent::TcpCheck{ "127.0.0.1:" + std::to_string(port), std::chrono::seconds(10)} // 只做模拟操作，用的consul本身的地址
            );

//    getchar();

    // Create an HTTP server
    WFHttpServer server([](WFHttpTask *task) {
        // Define the response for incoming requests
        task->get_resp()->append_output_body("<html>Hello World!</html>");
    });

    // Start the server on port 8888
    if (server.start(port) == 0) {
        std::cout << "Server started on port " << port << std::endl;
        getchar(); // Wait for user input to stop the server
        server.stop(); // Stop the server gracefully
    } else {
        std::cerr << "Failed to start server" << std::endl;
    }


    agent.deregisterService(serviceId);

    std::cout << "Waited 3 seconds!" << std::endl;

}
