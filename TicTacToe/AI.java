public class AI extends Thread {
    private final int team;
    private final BoardPanel boardPanel;

    public AI(int team, BoardPanel boardPanel) {
        this.team = team;
        this.boardPanel = boardPanel;
    }

    @Override
    public void run() {
        synchronized (boardPanel.buttons) {
            while (boardPanel.gameResult.get() == Utils.NONE) {
                while (boardPanel.currentPlayer.get() != team) {
                    try {
                        System.out.println("AI is waiting");
                        boardPanel.buttons.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    if (boardPanel.gameResult.get() != Utils.NONE) {
                        return;
                    }
                }
                System.out.println("AI is making move");
                makeMove();
            }
        }
    }

    private void makeMove() {
        int bestI = -1, bestJ = -1;
        int highestSeenValue = Integer.MIN_VALUE;
        int lowestSeenValue = Integer.MAX_VALUE;
        int currentValue;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (!Utils.isCellFree(boardPanel.buttons[i][j])) continue;

                CellButton[][] copyButtons = Utils.copyCellButtons(boardPanel.buttons);
                copyButtons[i][j].setTeam(boardPanel.currentPlayer.get());

                currentValue = boardPanel.currentPlayer.get() == Utils.PLAYER_X ?
                        min(copyButtons, Utils.getOtherPlayer(boardPanel.currentPlayer.get()),  4) :
                        max(copyButtons, Utils.getOtherPlayer(boardPanel.currentPlayer.get()), 4);

                if (boardPanel.currentPlayer.get() == Utils.PLAYER_X && currentValue >= highestSeenValue) {
                    highestSeenValue = currentValue;
                    bestI = i;
                    bestJ = j;
                }
                else if (boardPanel.currentPlayer.get() == Utils.PLAYER_O && currentValue <= lowestSeenValue) {
                    lowestSeenValue = currentValue;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        boardPanel.makeMove(bestI, bestJ);
    }

    private int min(CellButton[][] buttons, int curPlayer, int depth) {
        if (depth == 0 || Utils.getBoardState(curPlayer, buttons) != Utils.NONE || Utils.getBoardState(Utils.getOtherPlayer(curPlayer), buttons) != Utils.NONE) {
            return evaluate(buttons);
        }

        int lowestSeenValue = Integer.MAX_VALUE;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (!Utils.isCellFree(buttons[i][j])) continue;

                CellButton[][] copyButtons = Utils.copyCellButtons(buttons);
                copyButtons[i][j].setTeam(curPlayer);

                int currentValue = max(copyButtons, Utils.getOtherPlayer(curPlayer), depth - 1);
                if (currentValue <= lowestSeenValue) lowestSeenValue = currentValue;
            }
        }

        return lowestSeenValue;
    }

    private int max(CellButton[][] buttons, Integer curPlayer, int depth) {
        if (depth == 0 || Utils.getBoardState(curPlayer, buttons) != Utils.NONE || Utils.getBoardState(Utils.getOtherPlayer(curPlayer), buttons) != Utils.NONE) {
            return evaluate(buttons);
        }

        int highestSeenValue = Integer.MIN_VALUE;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (!Utils.isCellFree(buttons[i][j])) continue;

                CellButton[][] copyButtons = Utils.copyCellButtons(buttons);
                copyButtons[i][j].setTeam(curPlayer);

                int currentValue = min(copyButtons, Utils.getOtherPlayer(curPlayer), depth - 1);
                if (currentValue >= highestSeenValue) highestSeenValue = currentValue;
            }
        }

        return highestSeenValue;
    }

    private int evaluate(CellButton[][] buttons) {
        return scorePlayer(buttons, Utils.PLAYER_X) - scorePlayer(buttons, Utils.PLAYER_O);
    }

    private int scorePlayer(CellButton[][] buttons, int player) {
        return Utils.getMaxConsecutivePositions(player, buttons);
    }
}
