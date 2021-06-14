package ru.nsu.khomchenko;

import org.apache.log4j.Logger;

import java.util.Map;

public class ConfigCommandRepository implements ICommandRepository {
    private final IClassResolver classResolver;
    private Map<Character, String> classNames;

    private static final Logger logger = Logger.getLogger(ConfigCommandRepository.class);

    public ConfigCommandRepository(IClassResolver classResolver) {
        this.classResolver = classResolver;
    }

    public Command getCommandForSymbol(char symbol)
            throws ConfigException, ProgramException {
        String className = classNames.get(symbol);
        if (className == null) {
            throw new ProgramException(String.format("Unknown symbol \"%s\"", symbol + ""));
        }

        Class<?> requiredClass;
        try {
            requiredClass = classResolver.getClassByName(className);
        } catch (ClassNotFoundException e) {
            throw new ConfigException("Class specified in config not found", e);
        }

        try {
            Command command = (Command) requiredClass.getDeclaredConstructor().newInstance();
            command.character = symbol;

            logger.debug("Command \"" + symbol + "\" instantiated");

            return command;
        } catch (Exception e) {
            throw new ConfigException("Error creating class specified in config", e);
        }
    }

    public void loadTable(ITableLoader tableLoader)
            throws ConfigException {
        classNames = tableLoader.loadTable();
    }
}
