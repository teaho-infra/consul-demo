package net.teaho.demo.spring.cloud.consul.service.controller;

import net.teaho.demo.spring.cloud.discovery.api.UserFeign;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

/**
 * @author teaho2015@gmail.com
 * @date 2024-11
 */
@RestController
public class UserController implements UserFeign {

    @Override
    public Object getUserById(Long id) {
        return Map.of("key", "hello " + id);
    }

    @Override
    public Object getUserDetail() {
        return null;
    }

    @Override
    public Boolean processVendorSpu(Long id, Byte result, Long languageId, Long categoryId, String categoryName, Long subCategoryId, String subCategoryName, Long itemId, String itemName, String description, String[] descImgs, String[] bannerImgs, String indexImage, String jsonSKU, String rejectMsg,
        String parameters, Long templateId) {
        return null;
    }
}
