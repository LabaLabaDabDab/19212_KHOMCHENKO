package com.classfile.basicinfo.attribute;

import com.classfile.ConstantPool;
import com.classfile.constant.Constant;
import com.classfile.type.U1;
import com.classfile.type.U2;
import com.classfile.type.U4;
import com.classfile.basicinfo.BasicInfo;
import com.classfile.constanttype.ConstantUTF8;

import java.io.InputStream;

public class AttributeInfo extends BasicInfo {

    public int nameIndex;

    protected int length;

    public short[] info;



    public AttributeInfo(ConstantPool cp, int nameIndex) {
        super(cp);
        this.nameIndex = nameIndex;
    }

    @Override
    public void read(InputStream inputStream) {
        length = (int) U4.read(inputStream);
        // информация представляет конкретное содержимое таблицы свойств,
        // здесь на самом деле содержимое других типов свойств хранится для предотвращения смещения чтения
        info = new short[length];
        for (int i = 0; i < length; i++) {
            info[i] = U1.read(inputStream);
        }
    }

    public static AttributeInfo getAttribute(ConstantPool cp, InputStream inputStream) {
        int nameIndex = U2.read(inputStream);
        String name = ((ConstantUTF8)cp.cpInfo[nameIndex]).value;

        // Поддерживаемые в настоящее время типы таблиц атрибутов
        switch(name) {
            case Constant.CODE:
                return new CodeAttribute(cp, nameIndex);
            case Constant.EXCEPTIONS:
                return new ExceptionAttribute(cp, nameIndex);
            case Constant.LINE_NUMBER_TABLE:
                return new LineNumberTableAttribute(cp ,nameIndex);
            case Constant.LOCAL_VARIABLE_TABLE:
                return new LocalVariableTableAttribute(cp, nameIndex);
        }
        // Неподдерживаемые типы, сначала сохраненные в общей таблице атрибутов
        return new AttributeInfo(cp, nameIndex);

    }
}
