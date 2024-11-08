package net.teaho.demo.spring.cloud.consul.client.handler;

import com.ecwid.consul.v1.ConsulClient;
import org.junit.jupiter.api.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.stereotype.Component;
import org.springframework.test.context.junit4.SpringRunner;

import java.util.concurrent.TimeUnit;

/**
 * @author teaho2015@gmail.com
 * @date 2024-11
 */
@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
public class ConsulLockTest {

    private static final Logger log = LoggerFactory.getLogger(ConsulLockTest.class);
    @Autowired
    private ConsulLock consulLock;


    @Test
    public void test() {

        ConsulLock.SessionContext ctx = new ConsulLock.SessionContext();
        ctx.setLockKey("testLock");

        for (int i = 0; i < 20; i++) {
            consulLock.lock(ctx);
            log.info("lock status: {}", ctx);
            try {
                TimeUnit.SECONDS.sleep(2L);
            } catch (InterruptedException e) {
                log.error(e.getMessage());
            }

        }
        consulLock.releaseLock(ctx);
    }

}
