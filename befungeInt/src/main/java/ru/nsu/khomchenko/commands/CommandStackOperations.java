package ru.nsu.khomchenko.commands;

import ru.nsu.khomchenko.Command;
import ru.nsu.khomchenko.IMachineState;

public class CommandStackOperations extends Command {
    @Override
    public void execute(IMachineState machineState) {
        switch (character) {
            case ':':
                int value = machineState.popStack();
                machineState.pushStack(value);
                machineState.pushStack(value);
                break;
            case '\\':
                int value1 = machineState.popStack();
                int value2 = machineState.popStack();
                machineState.pushStack(value1);
                machineState.pushStack(value2);
                break;
            case '$':
                machineState.popStack();
                break;
        }
    }
}
