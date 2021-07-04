import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;

public class BoardPanel extends JPanel {
    final CellButton[][] buttons;
    AtomicInteger currentPlayer = new AtomicInteger(Utils.PLAYER_X);
    int playerTeam = Utils.PLAYER_X;
    AtomicInteger gameResult = new AtomicInteger(Utils.NONE);
    AtomicBoolean online = new AtomicBoolean(false);

    private final JLabel statusLabel;
    private final JButton exitButton;
    private final JLabel teamLabel;
    private final SwingView swingView;

    public BoardPanel(SwingView swingView){
        super(new GridLayout(4, 3));

        this.swingView = swingView;

        buttons = new CellButton[3][3];
        teamLabel = new JLabel("");
        statusLabel = new JLabel("");
        exitButton = new JButton("Exit");

        statusLabel.setHorizontalAlignment(SwingConstants.CENTER);
        statusLabel.setFont(new Font("Arial", Font.BOLD, 30));

        teamLabel.setHorizontalAlignment(SwingConstants.CENTER);
        teamLabel.setFont(new Font("Arial", Font.BOLD, 30));

        exitButton.setVisible(false);
        exitButton.addActionListener(e -> swingView.setGameState(Utils.GAME_NONE));
        exitButton.setFont(new Font("Arial", Font.BOLD, 30));
    }

    public void initBoard(int playerTeam, boolean online) {
        this.playerTeam = playerTeam;
        this.currentPlayer.set(Utils.PLAYER_X);
        this.gameResult.set(Utils.NONE);
        this.online.set(online);

        this.removeAll();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                buttons[i][j] = new CellButton();
                buttons[i][j].addActionListener(new CellListener(this, i, j));
                add(buttons[i][j]);
            }
        }

        statusLabel.setText("Turn: " + Utils.getPlayerName(currentPlayer.get()));
        teamLabel.setText("You: " + Utils.getPlayerName(playerTeam));
        exitButton.setVisible(false);

        add(teamLabel);
        add(statusLabel);
        add(exitButton);
    }

    public boolean makeMove(int i, int j) {
        CellButton cellButton = buttons[i][j];

        if (!Utils.isCellFree(cellButton)) return false;

        cellButton.setImage(Utils.getPlayerImage(playerTeam, currentPlayer.get()));
        cellButton.setTeam(currentPlayer.get());
        cellButton.updateUI();

        gameResult.set(Utils.getBoardState(currentPlayer.get(), buttons));
        if (gameResult.get() != Utils.NONE) {
            statusLabel.setText(gameResult.get() == Utils.DRAW ? "DRAW" : Utils.getPlayerName(gameResult.get()) + " WON");
            exitButton.setVisible(true);
            return true;
        }

        currentPlayer.set(Utils.getOtherPlayer(currentPlayer.get()));
        statusLabel.setText("Turn: " + Utils.getPlayerName(currentPlayer.get()));
        return true;
    }

    private class CellListener implements ActionListener {
        private final int i, j;
        private final BoardPanel board;

        public CellListener(BoardPanel board, int i, int j) {
            this.board = board;
            this.i = i;
            this.j = j;
        }

        public void sendMove() {
            if (swingView.connectedPlayer == null) return;

            try {
                swingView.connectedPlayer.getObjectOutputStream().writeObject(new Move(i, j));
            } catch (Exception e) {
                e.printStackTrace();
                online.set(false);
                swingView.connectedPlayer.closeSocket();
                new AI(Utils.getOtherPlayer(playerTeam), board).start();
            }
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            synchronized (buttons) {
                if (gameResult.get() != Utils.NONE || currentPlayer.get() != playerTeam) return;

                if (makeMove(i, j)) {
                    if (online.get()) sendMove();
                    else {
                        buttons.notify();
                    }
                    if (gameResult.get() != Utils.NONE && swingView.connectedPlayer != null) {
                        swingView.connectedPlayer.closeSocket();
                    }
                }
            }
        }
    }
}
