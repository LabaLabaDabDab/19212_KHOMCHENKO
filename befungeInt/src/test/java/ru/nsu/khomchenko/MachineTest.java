package ru.nsu.khomchenko;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import ru.nsu.khomchenko.commands.CommandNoOp;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.List;

public class MachineTest {
    private Machine machine;
    private MockCommandRepository commandRepository;

    @Test
    public void testGetSetProgramSymbol() throws Exception {
        assertEquals('<', machine.state.getProgramSymbol(new Position(3, 2)));
        machine.state.setProgramSymbol(new Position(3, 2), '@');
        assertEquals('@', machine.state.getProgramSymbol(new Position(3, 2)));
    }

    @Test
    public void testMoveOneStep() throws Exception {
        machine.moveOneStep();
        assertEquals(new Position(1, 0), machine.state.getCurrentPosition());
        machine.state.setMovingDirection(MovingDirection.Down);
        machine.moveOneStep();
        assertEquals(new Position(1, 1), machine.state.getCurrentPosition());
    }

    @BeforeEach
    public void setUp() throws Exception {
        this.commandRepository = new MockCommandRepository();
        this.machine = new Machine(commandRepository, new MockProgramLoader());
    }

    @Test
    public void testStep() throws Exception {
        commandRepository.commandToReturn = new CommandNoOp();
        machine.step();
        assertEquals(new Position(1, 0), machine.state.getCurrentPosition());
        assertEquals('>', commandRepository.lastSymbolCalled);
        assertEquals(1, commandRepository.getCommandCalledTimes);
        machine.step();
        assertEquals(new Position(2, 0), machine.state.getCurrentPosition());
        assertEquals(' ', commandRepository.lastSymbolCalled);
        assertEquals(2, commandRepository.getCommandCalledTimes);
    }
}

class MockCommandRepository implements ICommandRepository {
    Command commandToReturn;
    int getCommandCalledTimes = 0;
    char lastSymbolCalled;

    @Override
    public Command getCommandForSymbol(char symbol){
        lastSymbolCalled = symbol;
        getCommandCalledTimes++;
        return commandToReturn;
    }
}

class MockProgramLoader implements IProgramLoader {
    @Override
    public List<char[]> loadProgram(){
        List<char[]> result = new ArrayList<>();
        result.add(">  v".toCharArray());
        result.add("    ".toCharArray());
        result.add("^  <".toCharArray());
        return result;
    }
}