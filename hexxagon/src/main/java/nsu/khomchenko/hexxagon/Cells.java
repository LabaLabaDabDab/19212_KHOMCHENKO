package nsu.khomchenko.hexxagon;

/**
 * Ётот класс хранит состо€ние игрового пол€
 */

public class Cells {
	public static final int   CELL_EMPTY = 0; //пусто
	public static final int   CELL_RUB   = 1; //рубин
	public static final int   CELL_PEARL = 2; //жемчужина
	public static final int   WIDTH      = 9; //высота
	public static final float MIN_RADIUS = 1.3f; //радиус между €чейками

	private final int[] cells;

	public Cells() { //€чейки
		cells = new int[] { -1, -1, -1, 0, 2, 0, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, -1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, -1, -1, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1 };
	}

	/**
	 * —оздает копию €чеек
	 * @param cells исходное состо€ние
	 */
	public Cells(int[] cells) {
		this.cells = cells.clone();
	}

	public Cells getMove(int xfrom, int yfrom, int xto, int yto) { //делает ход и возвращает полученное поле
		if (getCell(xfrom, yfrom) <= 0) {
			System.out.println("\n\nERROR!!!\n\n");
			return this.copy();
		}
		float minRadius = MIN_RADIUS;
		Cells temp = this.copy();
		float[] from = toCoords(xfrom, yfrom);                    //переводим в координаты €чеек размером 1 дл€ удобства рассчетов
		float[] to = toCoords(xto, yto);
		float dist = (float) Math.sqrt(Math.pow(from[0] - to[0], 2) + Math.pow(from[1] - to[1], 2));
		int pl = temp.getCell(xfrom, yfrom);                      //фишка игрока, который делает ход
		if (dist <= minRadius && dist > 0) {
			temp.setCell(xto, yto, temp.getCell(xfrom, yfrom));   //копируем фишку
		}
		else if (dist <= minRadius * 2) {
			temp.setCell(xto, yto, temp.getCell(xfrom, yfrom));   //перемещаем фишку
			temp.setCell(xfrom, yfrom, Cells.CELL_EMPTY);
		}
		else {
			System.out.println("\n\nERROR!!! Too long distance!\n\n");
		}
		for (int i = 0; i < Cells.WIDTH * Cells.WIDTH; i++) {             //захватываем €чейки
			int x = i % Cells.WIDTH;
			int y = i / Cells.WIDTH;
			float[] coords = toCoords(x, y);
			dist = (float) Math.sqrt(Math.pow(to[0] - coords[0], 2) + Math.pow(to[1] - coords[1], 2));
			if (dist <= minRadius && dist > 0) {
				int c = temp.getCell(x, y);
				if (c != pl && c > 0) {
					temp.setCell(x, y, pl);
				}
			}
		}
		return temp;
	}

	public Cells copy() { //копирует поле
		return new Cells(cells);
	}

	/**
	 * ¬озвращает значение €чейки по координатам (значением €вл€етс€ число, определ€ющее кака€ фишка
	 * стоит на данной €чейке или пуста€/не используема€ €чейка)
	 */
	public int getCell(int x, int y) {
		return cells[Cells.WIDTH * y + x];
	}

	public void setCell(int x, int y, int val) { //”станавливает значени€ €чейки по ЄЄ координатам
		cells[Cells.WIDTH * y + x] = val;
	}

	/**
	 * ¬озвращает количество фишек игрока и соперника в виде массива
	 * 0 - рубины
	 * 1 - жемчужины
	 */
	public int[] getChipsCount() {
		int p1 = 0;
		int p2 = 0;
		for (int i = 0; i < cells.length; i++) {
			if (cells[i] == Cells.CELL_RUB) p1++;
			if (cells[i] == Cells.CELL_PEARL) p2++;
		}
		return new int[] { p1, p2 };
	}

	/**
	 * ѕровер€ет, кто из игроков выиграл или сыграл в ничью, и возвращает значение
	 * 0 - ничь€
	 * 1 - победа соперника
	 * 2 - победа игрока
	 */
	public byte getWinPlayer() {

		int[] counts = getChipsCount();
		if (getMovesCount(Cells.CELL_RUB) == 0 || getMovesCount(Cells.CELL_PEARL) == 0) {
			System.out.println("Nothing moves");
		}
		System.out.println("Rubies = " + counts[0]);
		System.out.println("Pearls = " + counts[1]);

		if (getMovesCount(Cells.CELL_PEARL) == 0 && getMovesCount(Cells.CELL_RUB) == 0) {
			if (counts[1] == counts[0]) {
				return 0; //ничь€
			}
			else if (counts[1] > counts[0]) {
				return CELL_PEARL;
			}
			else {
				return CELL_RUB;
			}
		}
		if (getMovesCount(Cells.CELL_PEARL) > 0 && getMovesCount(Cells.CELL_RUB) == 0) {
			for (int i = 0; i < Cells.WIDTH * Cells.WIDTH; i++) {
				if (cells[i] == 0) {
					cells[i] = CELL_PEARL;
				}
			}
			if (counts[1] + getEmptyCount() == counts[0]) {
				return 0; //ничь€
			}
			else if (counts[1] + getEmptyCount() > counts[0]) {
				return CELL_PEARL;
			}
			else {
				return CELL_RUB;
			}
		}
		if (getMovesCount(Cells.CELL_PEARL) == 0 && getMovesCount(Cells.CELL_RUB) > 0) {
			for (int i = 0; i < Cells.WIDTH * Cells.WIDTH; i++) {
				if (cells[i] == 0) {
					cells[i] = CELL_RUB;
				}
			}
			if (counts[1] + getEmptyCount() == counts[0] + getEmptyCount()) {
				return 0; //ничь€
			}
			else if (counts[1] + getEmptyCount() > counts[0] + getEmptyCount()) {
				return CELL_PEARL;
			}
			else {
				return CELL_RUB;
			}
		}
		return -1;
	}

	public int getMovesCount(int pl) { //возвращает число возможных ходов. pl - текущий игрок
		int result = 0;

		for (int i = 0; i < Cells.WIDTH * Cells.WIDTH; i++) { //ищем свою €чейку
			Point from = new Point(i % Cells.WIDTH, i / Cells.WIDTH);
			if (getCell(from.x, from.y) == pl) {
				for (int j = 0; j < Cells.WIDTH * Cells.WIDTH; j++) {
					Point to = new Point(j % Cells.WIDTH, j / Cells.WIDTH);
					if (getCell(to.x, to.y) == Cells.CELL_EMPTY) {
						float dist = from.getRealDist(to);
						if (dist <= Cells.MIN_RADIUS * 2 && dist > 0) result++;
					}
				}
			}
		}
		return result;
	}

	public int getEmptyCount() { //¬озвращает число пустых €чеек
		int result = 0;
		for (int i = 0; i < cells.length; i++) {
			if (cells[i] == Cells.CELL_EMPTY) result++;
		}
		return result;
	}

	/**
	 * переводит координаты €чейки из массива в реальные координаты сот (€чеек, расположенных в сотовом виде)
	 */
	public static float[] toCoords(int x, int y) {
		return new float[] { (float) x, (float) y * 1 + (float) x % 2 * 0.5f };
	}
}