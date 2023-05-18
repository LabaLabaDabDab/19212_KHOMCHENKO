package nsu.khomchenko.hexxagon;

import java.util.ArrayList;

 /**
 * Этот класс отвечает за поиск наилучшего хода компьютера
 */

public class AIPlayer {
	 private final int BIGVALUE = 100000;

	 /**
	  * Максимальная глубина прохождения дерева игры
	  */
	 private final int   MAX_DEPTH = 2;
	 private       int   player;
	 private       int   startPlayer;
	 private       Cells bestCells;
	 private       Move  bestMove;

	 /**
	  * Конструктор
	  *
	  * @param chip За какую фишку ходит компьютер
	  * @param diff Уровень сложности (пока не используется)
	  */

	 public AIPlayer(int chip, int diff) {
		 player = chip;
		 startPlayer = player;
		 bestCells = null;
	 }

	 /**
	  * Делает ход компьютера
	  *
	  * @param cells Исходное игровое поле, на котором делать ход
	  * @return Возвращает состояние после хода
	  */

	 public Move move(Cells cells) {
		 bestCells = null;
		 bestMove = null;
		 getBestMove(startPlayer, 0, cells);
		 return bestMove;
	 }

	 /**
	  * Возвращает список всех возможных ходов из данного состояния для данного игрока
	  *
	  * @param cls Исходное состояние
	  * @param pl  Номер игрока
	  * @return
	  */

	 private ArrayList<Move> getAllMoves(Cells cls, int pl) {
		 ArrayList<Move> moves = new ArrayList<Move>();

		 for (int i = 0; i < Cells.WIDTH * Cells.WIDTH; i++) { //ищем свою ячейку
			 Point from = new Point(i % Cells.WIDTH, i / Cells.WIDTH);
			 if (cls.getCell(from.x, from.y) == pl) {
				 for (int j = 0; j < Cells.WIDTH * Cells.WIDTH; j++) {
					 Point to = new Point(j % Cells.WIDTH, j / Cells.WIDTH);
					 if (cls.getCell(to.x, to.y) == Cells.CELL_EMPTY) {
						 float dist = from.getRealDist(to);
						 if (dist <= Cells.MIN_RADIUS * 2 && dist > 0) moves.add(new Move(from.x, from.y, to.x, to.y, pl));
					 }
				 }
			 }
		 }
		 return moves;
	 }

	 /**
	  * Реализует алгоритм NegaMax поиска лучшего хода.
	  *
	  * @param pl    Текущий игрок
	  * @param depth Текущая глубина
	  * @param cls   Текущее состояние игрового поля
	  * @return Возвращает оценку состояния для алгоритма
	  */

	 private int getBestMove(int pl, int depth, Cells cls) {
		 if (depth >= MAX_DEPTH - 1) return evaluate(pl, cls);
		 ArrayList<Move> bestMoves = new ArrayList<Move>();
		 int max = - BIGVALUE;
		 ArrayList<Move> moves = getAllMoves(cls, pl);
		 int nextpl = (pl == 1) ? 2 : 1;
		 int val = 0;
		 for (Move m : moves) {
			 val = -getBestMove(nextpl, depth + 1, cls.copy().getMove(m.getFrom().x, m.getFrom().y, m.getTo().x, m.getTo().y));
			 if (val > max) {  //ищем макс/мин значение
				 max = val;
				 bestMoves = new ArrayList<Move>();      //обнуляем список, если нашли лучший ход
				 bestMoves.add(new Move(m.getFrom().x, m.getFrom().y, m.getTo().x, m.getTo().y, pl));
			 }
			 else if (val == max) {
				 bestMoves.add(new Move(m.getFrom().x, m.getFrom().y, m.getTo().x, m.getTo().y, pl));  //не обнуляем, если нашли равноценный ход
			 }
		 }

		 if (depth == 0) {
			 Move best = bestMoves.get((int) (Math.random() * bestMoves.size()));
			 bestMove = best;
			 System.out.println(
					 "AI: MoveTo " + best.getFrom().x + ";" + best.getFrom().y + "  " + best.getTo().x + ";" + best.getTo().y);
			 bestCells = cls.getMove(best.getFrom().x, best.getFrom().y, best.getTo().x, best.getTo().y);
		 }
		 return val;
	 }

	 /**
	  * Производит оценку состояния
	  *
	  * @param pl  Текущий игрок
	  * @param cls Текущее состояние
	  * @return Оценка состояния
	  */

	 private int evaluate(int pl, Cells cls) {
		 int foe = (pl == 1) ? 2 : 1;
		 int value = 0;
		 int[] ccount = cls.getChipsCount();
		 value += ccount[pl - 1] - ccount[foe - 1];
		 return value;
	 }
 }
