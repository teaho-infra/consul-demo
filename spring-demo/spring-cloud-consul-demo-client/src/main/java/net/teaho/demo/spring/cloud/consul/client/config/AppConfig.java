package net.teaho.demo.spring.cloud.consul.client.config;

import lombok.extern.slf4j.Slf4j;
import org.springframework.boot.context.properties.EnableConfigurationProperties;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.util.Map;

/**
 * @author teaho2015@gmail.com
 * @date 2024-11
 */
@Configuration
@EnableConfigurationProperties(AppConfigProp.class)
@Slf4j
public class AppConfig {

    @Bean
    public Map<String, String> configMap(AppConfigProp configProp) {
        log.info("====== consul config:{}", configProp);
        return Map.of("testKey", configProp.getName() + "test");
    }

}
