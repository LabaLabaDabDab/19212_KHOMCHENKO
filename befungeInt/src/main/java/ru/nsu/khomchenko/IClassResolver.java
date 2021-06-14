package ru.nsu.khomchenko;

public interface IClassResolver {
    Class<?> getClassByName(String name)
            throws ClassNotFoundException;
}
