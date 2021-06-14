package ru.nsu.khomchenko;

import java.io.InputStream;
import java.io.PrintStream;

public interface IMachineState {
    MovingDirection getMovingDirection();
    void setMovingDirection(MovingDirection movingDirection);
    boolean isBridgeNextStep();
    void setBridgeNextStep(boolean bridgeNextStep);
    boolean isInStringMode();
    void toggleStringMode();
    int popStack();
    char popStackChar();
    void pushStack(int value);
    void pushStack(char value);
    Position getCurrentPosition();
    boolean isStopped();
    void Stop();
    char getProgramSymbol(Position position);
    void setProgramSymbol(Position position, char symbol);
    boolean isPositionInsideBounds(Position position);
    PrintStream getStdout();
    InputStream getStdin();
}
