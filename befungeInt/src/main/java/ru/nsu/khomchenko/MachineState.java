package ru.nsu.khomchenko;

import java.io.InputStream;
import java.io.PrintStream;
import java.util.ArrayDeque;
import java.util.Deque;
import java.util.List;

public class MachineState implements IMachineState {
    private final Position currentPosition;
    private final Deque<Integer> stack;
    private MovingDirection movingDirection;
    private boolean isInStringMode;
    private boolean bridgeNextStep;
    private boolean isStopped;
    private List<char[]> program;
    private PrintStream stdout;
    private InputStream stdin;
    public MachineState(List<char[]> program, PrintStream stdout, InputStream stdin) {
        currentPosition = new Position(0, 0);
        movingDirection = MovingDirection.Right;
        isInStringMode = false;
        stack = new ArrayDeque<>();
        this.program = program;
        this.stdout = stdout;
        this.stdin = stdin;
    }
    public char getProgramSymbol(Position position) {
        return program.get(position.y)[position.x];
    }
    public void setProgramSymbol(Position position, char symbol) {
        program.get(position.y)[position.x] = symbol;
    }
    @Override
    public boolean isPositionInsideBounds(Position position) {
        return !(position.x < 0 ||
                position.y < 0 ||
                position.x > program.get(position.y).length ||
                position.y > program.size());
    }
    public PrintStream getStdout() {
        return stdout;
    }
    public InputStream getStdin() {
        return stdin;
    }
    public MovingDirection getMovingDirection() {
        return movingDirection;
    }
    public void setMovingDirection(MovingDirection movingDirection) {
        this.movingDirection = movingDirection;
    }
    public boolean isBridgeNextStep() {
        return bridgeNextStep;
    }
    public void setBridgeNextStep(boolean bridgeNextStep) {
        this.bridgeNextStep = bridgeNextStep;
    }
    public boolean isInStringMode() {
        return isInStringMode;
    }
    public void toggleStringMode() {
        isInStringMode = !isInStringMode;
    }
    public int popStack() {
        if (stack.isEmpty()) {
            return 0;
        } else {
            return stack.pop();
        }
    }
    public char popStackChar() {
        if (stack.isEmpty()) {
            return 0;
        } else {
            return (char) stack.pop().intValue();
        }
    }
    public void pushStack(int value) {
        stack.push(value);
    }
    public void pushStack(char value) {
        stack.push((int) value);
    }
    public Position getCurrentPosition() {
        return currentPosition;
    }
    public boolean isStopped() {
        return isStopped;
    }
    public void Stop() {
        isStopped = true;
    }
}
