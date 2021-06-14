package ru.nsu.khomchenko;

import java.util.Map;

public interface ITableLoader {
    Map<Character, String> loadTable()
            throws ConfigException;
}
