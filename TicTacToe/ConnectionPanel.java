import javax.swing.*;
import java.awt.*;

public class ConnectionPanel extends JPanel {
    public ConnectionPanel(SwingView swingView){
        super();

        GridLayout gridLayout = new GridLayout(2, 1);
        gridLayout.setVgap(20);

        setLayout(gridLayout);

        JLabel wait = new JLabel("Waiting for other player...");
        JButton cancel = new JButton("Cancel");

        wait.setHorizontalAlignment(SwingConstants.CENTER);
        wait.setFont(new Font("Arial", Font.BOLD, 30));

        cancel.addActionListener(e -> swingView.setGameState(Utils.GAME_NONE));
        cancel.setFont(new Font("Arial", Font.BOLD, 30));

        add(wait);
        add(cancel);
    }
}
