package ru.nsu.khomchenko;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class FileProgramLoader implements IProgramLoader {
    private final String filename;

    public FileProgramLoader(String filename) {
        this.filename = filename;
    }

    @Override
    public List<char[]> loadProgram() throws ConfigException {
        List<char[]> result = new ArrayList<>();

        BufferedReader programReader = null;
        int maxLineLength = 0;

        try {
            programReader = new BufferedReader(new FileReader(filename));
            String line = programReader.readLine();
            while (line != null) {
                result.add(line.toCharArray());
                maxLineLength = Math.max(maxLineLength, line.length());
                line = programReader.readLine();
            }
        } catch (IOException e) {
            throw new ConfigException("Reading program error", e);
        } finally {
            try {
                if (programReader != null) {
                    programReader.close();
                }
            } catch (IOException e) {
                throw new ConfigException("Reading program error", e);
            }
        }

        for (int i = 0; i < result.size(); i++) {
            while (result.get(i).length < maxLineLength) {
                char[] oldArray = result.get(i);
                result.set(i, new char[maxLineLength]);
                System.arraycopy(oldArray, 0, result.get(i), 0, oldArray.length);
            }
        }
        return result;
    }
}
