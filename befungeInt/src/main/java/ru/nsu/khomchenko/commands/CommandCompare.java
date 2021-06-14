package ru.nsu.khomchenko.commands;

import ru.nsu.khomchenko.Command;
import ru.nsu.khomchenko.IMachineState;

public class CommandCompare extends Command {
    @Override
    public void execute(IMachineState machineState) {
        int a = machineState.popStack();
        int b = machineState.popStack();

        boolean result = (b > a);

        machineState.pushStack(result ? 1 : 0);
    }
}
