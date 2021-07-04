import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

public class CellButton extends JButton {
    private int team;
    private final ImageIcon imageIcon;

    public CellButton() {
        this.team = Utils.NONE;
        this.imageIcon = new ImageIcon(Assets.empty);
        add(new JLabel(this.imageIcon));
        setContentAreaFilled(false);
        setMargin(new Insets(0, 0, 0, 0));
    }

    public int getTeam() {
        return this.team;
    }

    public void setTeam(int team) {
        this.team = team;
    }

    public void setImage(BufferedImage image) {
        this.imageIcon.setImage(image);
    }
}
