package net.teaho.demo.spring.cloud.consul.service;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;


@SpringBootApplication
@EnableDiscoveryClient
public class DemoWebBootstrap {

    public static void main(String[] args) {
        SpringApplication.run(DemoWebBootstrap.class,args);
    }

}
