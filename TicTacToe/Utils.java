import java.awt.image.BufferedImage;

public class Utils {

    public final static int PLAYER_X = 0;
    public final static int PLAYER_O = 1;
    public final static int DRAW = 2;
    public final static int NONE = -1;

    public final static int GAME_NONE = 0;
    public final static int GAME_SINGLE_X = 1;
    public final static int GAME_SINGLE_O = 2;
    public final static int GAME_MULTI = 3;

    private static final int[][] wins = new int[][] { { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 }, { 0, 3, 6 }, { 1, 4, 7 }, { 2, 5, 8 }, { 0, 4, 8 }, { 2, 4, 6 } };

    public static boolean isCellFree(CellButton button) {
        return button.getTeam() == NONE;
    }

    public static String getPlayerName(int player) {
        return player == PLAYER_X ? "X" : "O";
    }

    public static BufferedImage getPlayerImage(int playerTeam, int currentPlayer) {
        if (playerTeam == currentPlayer) return playerTeam == PLAYER_X ? Assets.blueX : Assets.blueO;
        else return currentPlayer == PLAYER_X ? Assets.redX : Assets.redO;
    }

    public static int getOtherPlayer(int player) {
        return player == PLAYER_X ? PLAYER_O : PLAYER_X;
    }

    public static int getBoardState(int currentPlayer, CellButton[][] buttons) {
        for (int i = 0; i < wins.length; i++) {
            int matches = 0;

            for (int j = 0; j < wins[i].length; j++) {
                int row = wins[i][j] / 3;
                int col = wins[i][j] % 3;
                if (buttons[row][col].getTeam() == currentPlayer) {
                    matches++;
                }
            }

            if (matches == wins[i].length) return currentPlayer;
        }

        //проверяем есть ли свободные ячейки
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (buttons[i][j].getTeam() == NONE) {
                    return NONE;
                }
            }
        }

        //нет свободных ячеек - ничья
        return DRAW;
    }

    public static int getMaxConsecutivePositions(int currentPlayer, CellButton[][] buttons) {
        int max = 0;
        for (int i = 0; i < wins.length; i++) {
            int matches = 0;

            for (int j = 0; j < wins[i].length; j++) {
                int row = wins[i][j] / 3;
                int col = wins[i][j] % 3;
                if (buttons[row][col].getTeam() == currentPlayer) {
                    matches++;
                }
                else if (buttons[row][col].getTeam() != Utils.NONE) {
                    matches = 0;
                    break;
                }
            }

            if (matches > max) max = matches;
        }
        return max;
    }

    public static CellButton[][] copyCellButtons(CellButton[][] cellButtons) {
        CellButton[][] buttons = new CellButton[3][3];
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                buttons[i][j] = new CellButton();
                buttons[i][j].setTeam(cellButtons[i][j].getTeam());
            }
        }
        return buttons;
    }
}
