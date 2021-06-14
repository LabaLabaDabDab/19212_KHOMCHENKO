package ru.nsu.khomchenko;

import java.util.HashMap;
import java.util.Map;

public class ReflectionCachedClassResolver implements IClassResolver {
    private final Map<String, Class<?>> classes;
    public ReflectionCachedClassResolver() {
        this.classes = new HashMap<>();
    }

    @Override
    public Class<?> getClassByName(String name) throws ClassNotFoundException {
        Class<?> requiredClass = classes.get(name);
        if (requiredClass == null) {
            requiredClass = Class.forName(name);
            classes.put(name, requiredClass);
        }
        return requiredClass;
    }
}
