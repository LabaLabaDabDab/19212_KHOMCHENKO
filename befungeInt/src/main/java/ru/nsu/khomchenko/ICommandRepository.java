package ru.nsu.khomchenko;

public interface ICommandRepository {
    Command getCommandForSymbol(char symbol)
            throws ConfigException, ProgramException;
}
