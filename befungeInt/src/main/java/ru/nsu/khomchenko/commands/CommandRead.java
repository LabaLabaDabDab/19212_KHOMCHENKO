package ru.nsu.khomchenko.commands;

import ru.nsu.khomchenko.Command;
import ru.nsu.khomchenko.ConfigException;
import ru.nsu.khomchenko.IMachineState;
import ru.nsu.khomchenko.ProgramException;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandRead extends Command {
    private BufferedReader br;

    @Override
    public void execute(IMachineState machineState)
            throws ProgramException, ConfigException {
        String read;
        try {
            if (br == null) {
                br = new BufferedReader(new InputStreamReader(machineState.getStdin()));
            }
            read = br.readLine();
        } catch (IOException e) {
            throw new ConfigException("Error reading stdin");
        }

        try {
            switch (character) {
                case '&':
                    machineState.pushStack(Integer.parseInt(read));
                    break;
                case '~':
                    machineState.pushStack(read.charAt(0));
                    break;
            }
        } catch (Exception e) {
            throw new ProgramException("Error parsing stdin");
        }
    }
}
