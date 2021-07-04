import javax.swing.*;
import java.awt.*;

public class MainMenuPanel extends JPanel {

    public MainMenuPanel(SwingView swingView){
        super();

        setBackground(Color.WHITE);

        GridLayout gridLayout = new GridLayout(4, 1);
        gridLayout.setVgap(10);

        setLayout(gridLayout);

        JLabel gameLogo = new JLabel(new ImageIcon(Assets.gameLogo));
        JButton singleplayer1 = new JButton("Singleplayer, play as X");
        JButton singleplayer2 = new JButton("Singleplayer, play as O");
        JButton multiplayer = new JButton("Multiplayer");

        singleplayer1.setFont(new Font("Arial", Font.BOLD, 30));
        singleplayer1.setFocusPainted(false);

        singleplayer2.setFont(new Font("Arial", Font.BOLD, 30));
        singleplayer2.setFocusPainted(false);

        multiplayer.setFont(new Font("Arial", Font.BOLD, 30));
        multiplayer.setFocusPainted(false);

        singleplayer1.addActionListener(e -> swingView.setGameState(Utils.GAME_SINGLE_X));
        singleplayer2.addActionListener(e -> swingView.setGameState(Utils.GAME_SINGLE_O));
        multiplayer.addActionListener(e -> {
            int res = swingView.setGameState(Utils.GAME_MULTI);
            if (res == -1) {
                JOptionPane.showMessageDialog(swingView.frame, "Unable to connect to server");
            }
        });

        add(gameLogo);
        add(singleplayer1);
        add(singleplayer2);
        add(multiplayer);
    }
}
