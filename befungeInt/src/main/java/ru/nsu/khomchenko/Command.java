package ru.nsu.khomchenko;

public abstract class Command {
    public char character;
    public abstract void execute(IMachineState machineState) throws ProgramException, ConfigException;
}
