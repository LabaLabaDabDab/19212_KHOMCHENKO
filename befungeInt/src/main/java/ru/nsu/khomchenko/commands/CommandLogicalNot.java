package ru.nsu.khomchenko.commands;

import ru.nsu.khomchenko.Command;
import ru.nsu.khomchenko.IMachineState;

public class CommandLogicalNot extends Command {
    @Override
    public void execute(IMachineState machineState) {
        boolean a = (machineState.popStack() != 0);
        a = !a;
        machineState.pushStack(a ? 1 : 0);
    }
}
