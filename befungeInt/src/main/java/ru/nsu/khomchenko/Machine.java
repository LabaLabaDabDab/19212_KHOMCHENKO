package ru.nsu.khomchenko;

public class Machine {
    public final IMachineState state;
    private final ICommandRepository commandRepository;

    public Machine(ICommandRepository commandRepository, IProgramLoader programLoader)
            throws ConfigException {
        this.commandRepository = commandRepository;
        state = new MachineState(programLoader.loadProgram(), System.out, System.in);
    }

    public void step()
            throws ConfigException, ProgramException {
        char symbol = state.getProgramSymbol(state.getCurrentPosition());

        if (!state.isInStringMode() || symbol == '"') {
            Command command = commandRepository.getCommandForSymbol(symbol);
            command.execute(state);
        } else {
            state.pushStack(symbol);
        }
        moveOneStep();
    }

    public void moveOneStep()
            throws ProgramException {
        Position position = state.getCurrentPosition();
        int speed = 1;
        if (state.isBridgeNextStep()) {
            speed++;
            state.setBridgeNextStep(false);
        }

        switch (state.getMovingDirection()) {
            case Up:
                position.y -= speed;
                break;
            case Right:
                position.x += speed;
                break;
            case Down:
                position.y += speed;
                break;
            case Left:
                position.x -= speed;
                break;
        }

        if (!state.isPositionInsideBounds(position)) {
            throw new ProgramException(String.format("Machine moved out of program, position (%d, %d)", position.x, position.y));
        }
    }
}
