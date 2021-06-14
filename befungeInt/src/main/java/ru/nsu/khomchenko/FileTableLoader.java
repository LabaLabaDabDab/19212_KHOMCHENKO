package ru.nsu.khomchenko;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

public class FileTableLoader implements ITableLoader {
    private final String filepath;
    public FileTableLoader(String filepath) {
        this.filepath = filepath;
    }

    @Override
    public Map<Character, String> loadTable() throws ConfigException {
        Map<Character, String> result = new HashMap<>();

        InputStream stream = ClassLoader.getSystemResourceAsStream(filepath);
        Properties properties = new Properties();

        try {
            properties.load(stream);
            for (Map.Entry<Object, Object> entry : properties.entrySet()) {
                result.put(entry.getKey().toString().charAt(0), entry.getValue().toString());
            }
        } catch (IOException e) {
            throw new ConfigException("Reading config error", e);
        } finally {
            try {
                stream.close();
            } catch (IOException e) {
                throw new ConfigException("Reading config error", e);
            }
        }
        return result;
    }
}
