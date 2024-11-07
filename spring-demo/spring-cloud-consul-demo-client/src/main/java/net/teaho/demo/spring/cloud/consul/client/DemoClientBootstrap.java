package net.teaho.demo.spring.cloud.consul.client;

import lombok.extern.slf4j.Slf4j;
import net.teaho.demo.spring.cloud.discovery.api.UserFeign;
import net.teaho.demo.spring.cloud.discovery.api.config.UserFeignFallback;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;
import org.springframework.cloud.openfeign.EnableFeignClients;
import org.springframework.context.ConfigurableApplicationContext;

@SpringBootApplication
@EnableDiscoveryClient
@Slf4j
public class DemoClientBootstrap {

    public static void main(String[] args) {
        ConfigurableApplicationContext ctx = SpringApplication.run(DemoClientBootstrap.class, args);
        UserFeign userFeign = ctx.getBean(UserFeign.class);
        log.info("======result:{}", userFeign.getUserById(1L));



    }

}
