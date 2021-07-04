import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;
import java.net.Socket;

public class SwingView {
    private static final String TITLE = "TicTacToe";
    private static final int WIDTH = 520;
    private static final int HEIGHT = 720;

    private final MainMenuPanel mainMenu;
    private final ConnectionPanel connectionMenu;
    private final BoardPanel board;

    public JFrame frame;

    public ConnectedPlayer connectedPlayer;

    public SwingView() {
        this.frame = new JFrame(TITLE);

        this.mainMenu = new MainMenuPanel(this);
        this.connectionMenu = new ConnectionPanel(this);
        this.board = new BoardPanel(this);

        this.mainMenu.setVisible(true);
        this.connectionMenu.setVisible(false);
        this.board.setVisible(false);

        this.connectedPlayer = null;

        JPanel panel = new JPanel();
        LayoutManager overlay = new OverlayLayout(panel);
        panel.setLayout(overlay);

        panel.add(this.mainMenu);
        panel.add(this.connectionMenu);
        panel.add(this.board);

        this.frame.add(panel);
        this.frame.addWindowListener(new GameWindowAdapter());
        this.frame.setSize(WIDTH, HEIGHT);
        this.frame.setLocationRelativeTo(null);
        this.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.frame.setResizable(false);
        this.frame.setVisible(true);
    }

    public int setGameState(int gameState) {
        switch (gameState) {
            case Utils.GAME_NONE -> {
                if (connectedPlayer != null) {
                    connectedPlayer.closeSocket();
                    connectedPlayer = null;
                }
                board.gameResult.set(Utils.NONE);
                mainMenu.setVisible(true);
                board.setVisible(false);
                connectionMenu.setVisible(false);
            }
            case Utils.GAME_SINGLE_X -> {
                board.initBoard(Utils.PLAYER_X, false);
                new AI(Utils.PLAYER_O, board).start();
                mainMenu.setVisible(false);
                board.setVisible(true);
                connectionMenu.setVisible(false);
            }
            case Utils.GAME_SINGLE_O -> {
                board.initBoard(Utils.PLAYER_O, false);
                new AI(Utils.PLAYER_X, board).start();
                mainMenu.setVisible(false);
                board.setVisible(true);
                connectionMenu.setVisible(false);
            }
            case Utils.GAME_MULTI -> {
                try {
                    Socket socket = new Socket(Program.ip, Program.port);
                    connectedPlayer = new ConnectedPlayer(socket);
                    connectedPlayer.start();
                    mainMenu.setVisible(false);
                    board.setVisible(false);
                    connectionMenu.setVisible(true);
                } catch (IOException e) {
                    System.out.println("Unable to connect to server: " + e.getLocalizedMessage());
                    return -1;
                }
            }
        }
        return 0;
    }

    public class ConnectedPlayer extends PlayerThread {
        public boolean working;

        public ConnectedPlayer(Socket socket) throws IOException {
            super(socket);
            this.working = true;
        }

        @Override
        public void run() {
            while (working) {
                try {
                    Object obj = getObjectInputStream().readObject();
                    if (obj instanceof Move) {
                        Move move = (Move) obj;
                        board.makeMove(move.getI(), move.getJ());
                        if (board.gameResult.get() != Utils.NONE) {
                            working = false;
                        }
                    } else if (obj instanceof Integer) {
                        board.initBoard((int) obj, true);
                        mainMenu.setVisible(false);
                        board.setVisible(true);
                        connectionMenu.setVisible(false);
                    }
                } catch (Exception e) {
                    working = false;
                }
            }

            closeSocket();
            connectedPlayer = null;
            synchronized (board.buttons) {
                board.online.set(false);
                if (board.gameResult.get() == Utils.NONE && board.isVisible()) {
                    System.out.println("Lost connection with server. Turning on AI");
                    new AI(Utils.getOtherPlayer(board.playerTeam), board).start();
                }
            }
        }
    }

    private class GameWindowAdapter extends WindowAdapter {
        @Override
        public void windowClosing(WindowEvent e) {
            if (connectedPlayer != null) {
                connectedPlayer.closeSocket();
            }
        }
    }
}
