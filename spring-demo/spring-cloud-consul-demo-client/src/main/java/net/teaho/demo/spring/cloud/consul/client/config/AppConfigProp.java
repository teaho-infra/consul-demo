package net.teaho.demo.spring.cloud.consul.client.config;

import lombok.Data;
import org.springframework.boot.context.properties.ConfigurationProperties;

/**
 * @author teaho2015@gmail.com
 * @date 2024-11
 */
@Data
@ConfigurationProperties(prefix = "my.config")
public class AppConfigProp {

    private String name;
}
