package com.classfile.basicinfo;

import com.classfile.ConstantPool;
import com.classfile.type.U2;
import com.classfile.basicinfo.attribute.AttributeInfo;

import java.io.InputStream;

public class FieldMethodInfo extends BasicInfo {

    public int accessFlag; //флаг доступа

    public int nameIndex; //индекс в пуле констант для имени

    public int descriptorIndex; //индекс в пуле констант для дескриптора
    public int attributesCount;

    public AttributeInfo[] attributes;

    public FieldMethodInfo(ConstantPool cp) {
        super(cp);
    }


    public void read(InputStream inputStream) {

        accessFlag = U2.read(inputStream);
        nameIndex = U2.read(inputStream);
        descriptorIndex = U2.read(inputStream);
        attributesCount = U2.read(inputStream);
        attributes = new AttributeInfo[attributesCount];

        for (int i = 0; i < attributesCount; i++) {
            AttributeInfo attributeInfo = AttributeInfo.getAttribute(cp, inputStream);
            attributeInfo.read(inputStream);
            attributes[i] = attributeInfo;
        }

    }
}
