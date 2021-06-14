package ru.nsu.khomchenko.commands;

import ru.nsu.khomchenko.Command;
import ru.nsu.khomchenko.IMachineState;

public class CommandArithmetic extends Command {
    @Override
    public void execute(IMachineState machineState) {
        int a = machineState.popStack();
        int b = machineState.popStack();
        int result = 0;
        switch (character) {
            case '+':
                result = a + b;
                break;
            case '-':
                result = b - a;
                break;
            case '*':
                result = a * b;
                break;
            case '/':
                result = b / a;
                break;
            case '%':
                result = a % b;
                break;
        }
        machineState.pushStack(result);
    }
}
