package ru.nsu.khomchenko.commands;

import ru.nsu.khomchenko.Command;
import ru.nsu.khomchenko.IMachineState;

public class CommandBridge extends Command {
    @Override
    public void execute(IMachineState machineState) {
        machineState.setBridgeNextStep(true);
    }
}
