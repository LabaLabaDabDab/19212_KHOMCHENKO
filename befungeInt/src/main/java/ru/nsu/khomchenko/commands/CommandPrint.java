package ru.nsu.khomchenko.commands;

import ru.nsu.khomchenko.Command;
import ru.nsu.khomchenko.IMachineState;
import org.apache.log4j.Logger;

public class CommandPrint extends Command {
    private static final Logger logger = Logger.getLogger(CommandPrint.class);

    @Override
    public void execute(IMachineState machineState) {
        String result = "";
        switch (character) {
            case ',':
                result = machineState.popStackChar() + "";
                break;
            case '.':
                result = machineState.popStack() + " ";
                break;
        }
        machineState.getStdout().print(result);
        logger.debug("Printed char \"" + result + "\"");
    }
}
