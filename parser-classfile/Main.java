package com.classfile;

import com.classfile.basicinfo.FieldMethodInfo;
import com.classfile.basicinfo.attribute.*;
import com.classfile.constanttype.*;
import com.classfile.type.U2;
import com.classfile.type.U4;

import java.io.FileInputStream;
import java.util.ArrayList;

public class Main {
    /**
     * Модификаторы доступа к классам и свойствам
    */
    private static final int ACC_PUBLIC =	0x0001;
    private static final int ACC_PRIVATE = 0x0002;
    private static final int ACC_PROTECTED = 0x0004;
    private static final int ACC_STATIC	= 0x0008;
    private static final int ACC_FINAL =	0x0010;
    private static final int ACC_INTERFACE = 0x0200;
    private static final int ACC_ABSTRACT = 0x0400;
    private static final int ACC_ENUM	 = 0x4000;

    public static String getAccessModifiers(int access) {
        if ((access & ACC_PUBLIC) != 0) {
            return "public";
        }
        if ((access & ACC_PRIVATE) != 0) {
            return "private";
        }
        if ((access & ACC_PROTECTED) != 0) {
            return "protected";
        }
        return "";
    }

    public static String getOptionalModifiers(int access) {
        String result = "";
        if ((access & ACC_STATIC) != 0) {
            result += "static";
        }
        if ((access & ACC_FINAL) != 0) {
            if (!result.isEmpty()) result += " ";
            result += "final";
        }
        else if ((access & ACC_ABSTRACT) != 0) {
            if (!result.isEmpty()) result += " ";
            result += "abstract";
        }
        return result;
    }

    public static String getClassModifiers(int access) {
        if ((access & ACC_INTERFACE) != 0) {
            return "interface";
        }
        if ((access & ACC_ENUM) != 0) {
            return "enum";
        }
        return "class";
    }

    public static String getParents(ConstantPool cpPool, FileInputStream inputStream, int superIndex, int interfaceCount) {
        StringBuilder result = new StringBuilder();
        ConstantClass superClazz = (ConstantClass) cpPool.cpInfo[superIndex]; //берём супер класс
        ConstantUTF8 superclassName = (ConstantUTF8) cpPool.cpInfo[superClazz.nameIndex]; //берём имя супер класса
        if (!superclassName.value.contains("Object")) { //если наследуется не только от объекта, то смотрим другое
            result.append(" extends ").append(superclassName.value);
        }
        if (interfaceCount > 0) { //чекаем количество интерфейсов
            result.append(" implements "); //добавляем в конец типа
            for (int i = 0; i < interfaceCount; i++) {
                int interfaceIndex = U2.read(inputStream);
                ConstantClass interfaceClazz = (ConstantClass) cpPool.cpInfo[interfaceIndex]; //берём интерфейс
                ConstantUTF8 interfaceName = (ConstantUTF8) cpPool.cpInfo[interfaceClazz.nameIndex]; //берём название
                result.append(interfaceName.value); //добавляем имя интерфейса в тип
                if (i < interfaceCount - 1) { //если не последний интерфейс то ,
                    result.append(", "); //
                }
            }
        }
        return result.toString();
    }

    public static String smartStringConcat(char delimiter, String[] strings) { //конкатенация строк
        StringBuilder str = new StringBuilder();
        for (String string : strings) {
            if (str.length() == 0) str.append(string); //если не записали ничего, то записываем
            else if (!string.isEmpty()) {
                str.append(delimiter).append(string); //если не пустая, добавляем разделитель, затем строку
            }
        }
        return str.toString();
    }

    private static String getMethodArguments(String descriptor) {
        int idx1 = descriptor.indexOf("(");
        int idx2 = descriptor.indexOf(")");
        if (idx1 + 1 == idx2) return "()";
        String args = descriptor.substring(idx1 + 1, idx2); //берём подстраку внутри скобок
        ArrayList<String> types = new ArrayList<>(); //все типы которые есть
        String curType = ""; //текущий тип
        boolean searchForSemicolon = false; //точка с запитой
        for (int i = 0; i < args.length(); i++) { //проходим по всем символам
            char c = args.charAt(i);
            if (searchForSemicolon) { //если ищем ; то добавляем текущий символ
                curType += c;
                if (c == ';') {
                    types.add(curType);
                    curType = "";
                    searchForSemicolon = false;
                }
                continue;
            }
            if (c == '[') { //массив
                if (args.charAt(i + 1) == 'L') { //класс
                    curType = "[";
                    searchForSemicolon = true;
                }
                else { //примитивный тип
                    curType = "";
                    types.add("[" + c);
                }
            }
            else if (c == 'L') { //просто класс
                curType = "L";
                searchForSemicolon = true;
            }
            else { //просто примитивный тип
                curType = "";
                types.add(c + "");
            }
        }
        StringBuilder sb = new StringBuilder();
        sb.append("(");
        for(int i = 0; i < types.size(); i++) {
            sb.append(getNormalTypeName(types.get(i))); //получаем нормальные имена
            if (i < types.size() - 1) {
                sb.append(", ");
            }
        }
        sb.append(")");
        return sb.toString();
    }

    private static String getMethodReturnType(String descriptor) { //возвращаемый тип
        int idx = descriptor.indexOf(")");
        String type = descriptor.substring(idx + 1); //остаётся только после )
        return getNormalTypeName(type);
    }

    private static String getNormalTypeName(String type) {
        boolean isArray = false;
        if (type.startsWith("[")) { //проверка на массив
            isArray = true;
            type = type.substring(1); //если да убираем скобку
        }
        if (type.length() == 1) { //примитимный тип
            String name = "";
            switch (type.charAt(0)) {
                case 'B': name = "byte"; break;
                case 'C': name = "char"; break;
                case 'D': name = "double"; break;
                case 'F': name = "float"; break;
                case 'I': name = "int"; break;
                case 'J': name = "long"; break;
                case 'S': name = "short"; break;
                case 'Z': name = "boolean"; break;
                case 'V': name = "void"; break;
            }
            if (!name.isEmpty()) {
                return name + (isArray ? "[]" : "");
            }
        }
        type = type.substring(1); //класс, убираем первую букву L
        if (type.endsWith(";")) type = type.substring(0, type.length() - 1);
        return type + (isArray ? "[]" : "");
    }

    public static void main(String[] args) throws Exception {
        FileInputStream inputStream = new FileInputStream(args[0]);
        U4.read(inputStream); //magic
        U2.read(inputStream); //minor version
        U2.read(inputStream); //major version
        int cpCount = U2.read(inputStream);

        ConstantPool cpPool = new ConstantPool(cpCount);
        cpPool.read(inputStream);

        int accessFlag = U2.read(inputStream); //флаг доступа для класса
        int classIndex = U2.read(inputStream); //индекс класса в пуле констант
        ConstantClass clazz = (ConstantClass) cpPool.cpInfo[classIndex]; //берём сам класс
        ConstantUTF8 className = (ConstantUTF8) cpPool.cpInfo[clazz.nameIndex];

        int superIndex = U2.read(inputStream); //берём индекс супер классов в пуле констант
        int interfaceCount = U2.read(inputStream); //количетсов интерфейсов

        System.out.print(smartStringConcat(' ', new String[] {
                        getAccessModifiers(accessFlag),
                        getOptionalModifiers(accessFlag),
                        getClassModifiers(accessFlag),
                        className.value,
                        getParents(cpPool, inputStream, superIndex, interfaceCount),
                        "{"
        }));
        System.out.println();

        //fields

        int fieldCount = U2.read(inputStream); //количество полей
        for (int i = 0; i < fieldCount; i++) {
            FieldMethodInfo fieldInfo = new FieldMethodInfo(cpPool); //заводим класс под инфу для поля
            fieldInfo.read(inputStream); //берём инфу о поле
            String descriptor = ((ConstantUTF8) cpPool.cpInfo[fieldInfo.descriptorIndex]).value; //тип поля
            System.out.println("\t" + smartStringConcat(' ', new String[] {
                    getAccessModifiers(fieldInfo.accessFlag),
                    getOptionalModifiers(fieldInfo.accessFlag),
                    getMethodReturnType(descriptor),
                    ((ConstantUTF8) cpPool.cpInfo[fieldInfo.nameIndex]).value
            }) + ";");
        }
        System.out.print("\n");

        //methods
        int methodCount = U2.read(inputStream); //считываем количество методов
        for (int i = 0; i < methodCount; i++) {
            FieldMethodInfo methodInfo = new FieldMethodInfo(cpPool);
            methodInfo.read(inputStream);
            String name = ((ConstantUTF8) cpPool.cpInfo[methodInfo.nameIndex]).value; //имя метода
            String descriptor = ((ConstantUTF8) cpPool.cpInfo[methodInfo.descriptorIndex]).value; //аргументы и возвращаемый тип
            if (name.contains("<init>")) { //если метод является конструктором
                System.out.print("\t" + smartStringConcat(' ', new String[] {
                        getAccessModifiers(methodInfo.accessFlag),
                        getOptionalModifiers(methodInfo.accessFlag),
                        className.value + getMethodArguments(descriptor)
                }));
            }
            else if (name.contains("<clinit>")) { //статический блок инициализации
                System.out.print("\t" + smartStringConcat(' ', new String[] {
                        getOptionalModifiers(methodInfo.accessFlag),
                        "{}"
                }));
            }
            else {
                System.out.print("\t" + smartStringConcat(' ', new String[]{ //всё остальное
                        getAccessModifiers(methodInfo.accessFlag),
                        getOptionalModifiers(methodInfo.accessFlag),
                        getMethodReturnType(descriptor),
                        ((ConstantUTF8) cpPool.cpInfo[methodInfo.nameIndex]).value + getMethodArguments(descriptor)
                }));
            }
            for (int j = 0; j < methodInfo.attributesCount; j++) { //какие исключения метод пробрасывает
                if (methodInfo.attributes[j] instanceof ExceptionAttribute) {
                    ExceptionAttribute exceptionAttribute = (ExceptionAttribute) methodInfo.attributes[j]; //берём эти аттрибуты
                    if (exceptionAttribute.numberOfExceptions > 0) System.out.print(" throws ");
                    for (int m = 0; m < exceptionAttribute.numberOfExceptions; m++) {
                        int nameIndex = ((ConstantClass) cpPool.cpInfo[exceptionAttribute.indexTable[m]]).nameIndex;
                        System.out.print(((ConstantUTF8) cpPool.cpInfo[nameIndex]).value);
                        if (j < methodInfo.attributesCount - 1) {
                            System.out.print(", ");
                        }
                    }
                }
            }
            System.out.println(";");
        }
        System.out.println("}");
        inputStream.close();
    }
}
