package ru.nsu.khomchenko.commands;

import ru.nsu.khomchenko.Command;
import ru.nsu.khomchenko.IMachineState;
import ru.nsu.khomchenko.MovingDirection;

public class CommandCondition extends Command {
    @Override
    public void execute(IMachineState machineState) {
        boolean value = (machineState.popStack() != 0);

        switch (character) {
            case '|':
                if (value) {
                    machineState.setMovingDirection(MovingDirection.Up);
                } else {
                    machineState.setMovingDirection(MovingDirection.Down);
                }
                break;
            case '_':
                if (value) {
                    machineState.setMovingDirection(MovingDirection.Left);
                } else {
                    machineState.setMovingDirection(MovingDirection.Right);
                }
                break;
        }
    }
}
