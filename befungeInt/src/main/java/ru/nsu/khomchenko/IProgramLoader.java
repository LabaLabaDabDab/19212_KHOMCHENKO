package ru.nsu.khomchenko;

import java.util.List;

public interface IProgramLoader {
    List<char[]> loadProgram()
            throws ConfigException;
}
