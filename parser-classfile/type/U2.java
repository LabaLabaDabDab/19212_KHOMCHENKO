package com.classfile.type;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.IOException;
import java.io.InputStream;

public class U2 { //двух байтовые

    private static final Logger LOG = LoggerFactory.getLogger(U2.class);

    public static int read(InputStream inputStream) {
        // bytes хранит два байта в виде буферизованного массива
        byte[] bytes = new byte[2];
        try {
            inputStream.read(bytes);
        } catch (IOException e) {
            LOG.debug("read failed:", e);
        }
        // Анализирует два байта в буферизованном массиве на символы
        int num = 0;
        for (int i= 0; i < bytes.length; i++) {
            num <<= 8;
            num |= (bytes[i] & 0xff);
        }
        return num;
    }
}
