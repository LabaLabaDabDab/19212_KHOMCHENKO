package ru.nsu.khomchenko;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import ru.nsu.khomchenko.commands.CommandNoOp;

import static org.junit.jupiter.api.Assertions.*;

import java.util.HashMap;
import java.util.Map;

public class ConfigCommandRepositoryTest {
    private ConfigCommandRepository commandRepository;
    private MockClassResolver classResolver;

    @BeforeEach
    public void setUp() throws Exception {
        this.classResolver = new MockClassResolver();
        this.commandRepository = new ConfigCommandRepository(classResolver);
        commandRepository.loadTable(new MockTableLoader());
    }

    @Test
    public void getCommandForSymbol() throws Exception {
        classResolver.classToReturn = CommandNoOp.class;

        Command actual = commandRepository.getCommandForSymbol('@');

        assertTrue(actual instanceof CommandNoOp);
        assertEquals(1, classResolver.getClassCalledTimes);
        assertEquals("stop", classResolver.lastNameCalled);
    }
}

class MockClassResolver implements IClassResolver{
    Class<?> classToReturn;
    String lastNameCalled;
    int getClassCalledTimes = 0;

    @Override
    public Class<?> getClassByName(String name){
        lastNameCalled = name;
        getClassCalledTimes++;
        return classToReturn;
    }
}

class MockTableLoader implements ITableLoader {
    @Override
    public Map<Character, String> loadTable(){
        Map<Character, String> result = new HashMap<>();
        result.put('@', "stop");
        result.put('v', "arrowDown");
        result.put('p', "p");
        return result;
    }
}