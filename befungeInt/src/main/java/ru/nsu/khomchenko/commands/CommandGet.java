package ru.nsu.khomchenko.commands;

import ru.nsu.khomchenko.Command;
import ru.nsu.khomchenko.IMachineState;
import ru.nsu.khomchenko.Position;

public class CommandGet extends Command {
    @Override
    public void execute(IMachineState machineState) {
        int y = machineState.popStack();
        int x = machineState.popStack();

        char symbol = machineState.getProgramSymbol(new Position(x, y));
        machineState.pushStack(symbol);
    }
}
