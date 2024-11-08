package net.teaho.demo.spring.cloud.consul.client.handler;

import com.ecwid.consul.v1.ConsulClient;
import com.ecwid.consul.v1.QueryParams;
import com.ecwid.consul.v1.Response;
import com.ecwid.consul.v1.agent.model.NewCheck;
import com.ecwid.consul.v1.kv.model.PutParams;
import com.ecwid.consul.v1.session.model.NewSession;
import com.ecwid.consul.v1.session.model.Session;
import lombok.Data;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

/**
 * @author teaho2015@gmail.com
 * @date 2024-11
 */
@Component
public class ConsulLock {

    @Autowired
    private ConsulClient consulClient;


    public SessionContext lock(SessionContext sessionContext) {
        if (sessionContext.getSessionId() == null) {
            String sessionKey = createSession(sessionContext.getLockKey(), 10);
            sessionContext.setSessionId(sessionKey);
        }
        sessionContext.lockStatus = lock(sessionContext.getLockKey(), sessionContext.getSessionId());
        return sessionContext;
    }

    private String createSession(String lockKey, int ttlSeconds) {
        NewCheck check = new NewCheck();
        check.setId("check "+lockKey);
        check.setName(check.getId());
        check.setTtl(ttlSeconds+"s"); //该值和session ttl共同决定决定锁定时长
        check.setTimeout("10s");
        consulClient.agentCheckRegister(check);
        consulClient.agentCheckPass(check.getId());

        NewSession session = new NewSession();
        session.setBehavior(Session.Behavior.RELEASE);
        session.setName("session "+lockKey);
        session.setLockDelay(1);
        session.setTtl(ttlSeconds + "s"); //和check ttl共同决定锁时长
        List<String> checks = new ArrayList<>();
        checks.add(check.getId());
        session.setChecks(checks);

        return consulClient.sessionCreate(session,null).getValue();
    }

    private boolean lock(String key, String sessionId){
        PutParams putParams = new PutParams();
        putParams.setAcquireSession(sessionId);
        return consulClient.setKVValue(key, "lock:"+ LocalDateTime.now(),putParams).getValue();
    }

    public void releaseLock(SessionContext sessionContext) {
        consulClient.sessionDestroy(sessionContext.getSessionId(), null);
    }

    @Data
    public static class SessionContext {
        private String lockKey;
        private String sessionId;
        private boolean lockStatus;


    }
}
