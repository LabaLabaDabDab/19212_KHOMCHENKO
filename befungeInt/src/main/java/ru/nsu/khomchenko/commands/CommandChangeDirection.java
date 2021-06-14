package ru.nsu.khomchenko.commands;

import ru.nsu.khomchenko.Command;
import ru.nsu.khomchenko.IMachineState;
import ru.nsu.khomchenko.MovingDirection;

import java.util.Random;

public class CommandChangeDirection extends Command {
    private static final Random random = new Random();

    @Override
    public void execute(IMachineState machineState) {
        switch (character) {
            case '^':
                machineState.setMovingDirection(MovingDirection.Up);
                break;
            case '>':
                machineState.setMovingDirection(MovingDirection.Right);
                break;
            case 'v':
                machineState.setMovingDirection(MovingDirection.Down);
                break;
            case '<':
                machineState.setMovingDirection(MovingDirection.Left);
                break;
            case '?':
                machineState.setMovingDirection(getRandomDirection());
                break;
        }
    }

    private MovingDirection getRandomDirection() {
        switch (random.nextInt(4)) {
            case 0:
                return MovingDirection.Up;
            case 1:
                return MovingDirection.Right;
            case 2:
                return MovingDirection.Down;
            default:
                return MovingDirection.Left;
        }
    }
}
