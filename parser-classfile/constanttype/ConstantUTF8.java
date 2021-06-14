package com.classfile.constanttype;

import com.classfile.ConstantBase;
import com.classfile.type.U2;

import java.io.InputStream;
import java.io.UTFDataFormatException;

public class ConstantUTF8 extends ConstantBase {

    public String value;

    public short tag;

    public ConstantUTF8(short tag) {
        this.tag = tag;
    }

    public void read(InputStream inputStream) {
        int length = U2.read(inputStream);
        byte[] bytes = new byte[length];
        try {
            inputStream.read(bytes);
        } catch(Exception e) {

        }

        try {
            value = readUtf8(bytes).replace('/', '.');
        } catch(Exception e) {

        }
    }

    // Декодировать поток байтов в кодировке utf-8 в строку, записанную в двоичном формате
    public String readUtf8(byte[] byteArr) throws Exception {
        int c, char2, char3;
        int count = 0;
        int charArrCount = 0;
        char[] charArr = new char[byteArr.length];

        while (count < byteArr.length) {
            c = (int) byteArr[count] & 0b1111_1111;
            if (c > 127) break;
            count++;
            charArr[charArrCount++] = (char) c;
        }

        while (count < byteArr.length) {
            c = (int) byteArr[count] & 0b1111_1111;
            // смотрим по последним 4 цифрам
            switch (c >> 4) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                    // Битовые характеристики одного байта
                    /* 0xxx_xxxx*/
                    count += 1;
                    charArr[charArrCount++] = (char) c;
                    break;
                case 12:
                case 13:
                    // Двухбайтовые битовые характеристики
                    /* 110x_xxxx 10xx_xxxx*/
                    count += 2;
                    if (count > byteArr.length) {
                        throw new UTFDataFormatException("malformed input: partial character at end");
                    }

                    char2 = (int) byteArr[count - 1]; //чары которые занимают 2 байта
                    if ((char2 & 0b1100_0000) != 0b1000_0000) {
                        throw new UTFDataFormatException("malformed input around byte " + count);
                    }
                    // Первая высокая позиция, следующая позиция
                    // High занимает только последние 5 бит,low только последние 6 бит
                    charArr[charArrCount++] = (char) (((c & 0b0001_1111) << 6) |
                            (char2 & 0b0011_1111));
                    break;
                case 14:
                    // Трехбайтовые битовые характеристики
                    /* 1110_xxxx 10xx_xxxx 10xx_xxxx */
                    count += 3;
                    if (count > byteArr.length) {
                        throw new UTFDataFormatException("malformed input: partial character at end");
                    }

                    char2 = (int) byteArr[count - 2];
                    char3 = (int) byteArr[count - 1];
                    // Проверяем последние два бита
                    if (((char2 & 0b1100_0000) != 0b10_00_0000) || ((char3 & 0b110_0000) != 0b1000_0000)) {
                        throw new UTFDataFormatException("malformed input around byte " + (count - 1));
                    }

                    // Самый высокий значащий бит 4, второй по величине значащий бит 6,самый низкий значащий бит 6
                    charArr[charArrCount++] = (char) (((c & 0b0000_1111) << 12) |
                            ((char2 & 0b0011_1111) << 6) |
                            ((char3 & 0b0011_1111) << 0));
                    break;
                default:
                    /* 10xx xxxx, 1111 xxxx */
                    throw new UTFDataFormatException("malformed input around byte " + count);
            }
        }
        // Используем допустимую длину декодированного массива символов
        return new String(charArr, 0, charArrCount);
    }
}
