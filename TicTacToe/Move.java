import java.io.Serializable;

public class Move implements Serializable {
    private final int i;
    private final int j;

    public Move(int i, int j){
        this.i = i;
        this.j = j;
    }

    public int getI(){
        return i;
    }

    public int getJ(){
        return j;
    }
}
