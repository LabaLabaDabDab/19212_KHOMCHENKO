package nsu.khomchenko.hexxagon;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.image.BufferStrategy;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.ArrayList;

/**
 * Ётот класс обеспечивает взаимодействие пользовател€ с игровым полем, отрисовывает его и выполн€ет основную логику игры
 */
public class Board implements DrawableEntity {
	private static final int   BOARD_HEIGHT     = 1024;
	private static final float BOARD_OFFSET_X   = 162;
	private static final float BOARD_OFFSET_Y   = 80;
	private static final float BOARD_GRID_X     = 80;
	private static final float BOARD_GRID_Y     = 100;
	private static final float HLIGHT_OFFSET_X  = -33;
	private static final float HLIGHT_OFFSET_Y  = -31;
	private static final float SELECTION_RADIUS = 30;

	public  volatile      int                  state;
	private final float                scale;
	private final BufferedImage        image;
	private  	  Game                 game;
	public  volatile      Cells                cells;
	private       ArrayList<Chip>      chips;          //фишки
	private       ArrayList<Highlight> hlights;   //дл€ подсветки €чеек
	private final float                boardX;

	private       boolean              isSelected;             //выбрана ли €чейка
	private final int[]                selectedCell;             //координаты выбранной €чейки
	private       Highlight            selectedHlight;
	private       ArrayList<Highlight> moveCells; //в какие €чейки можно делать ход
	private final int[]                nextCell;                 //координаты след €чейки
	public final int                  playerChip;                 //тип фишки игрока

	public int moveMaker = Cells.CELL_RUB;
	public final AIPlayer ai;

	private Button returnButton;

	public Board(Game game, int player) {
		this.game = game;
		this.scale = (float) game.getHeight() / BOARD_HEIGHT;
		this.image = Assets.field;
		this.cells = new Cells();
		this.chips = new ArrayList<>();
		this.hlights = new ArrayList<>();
		this.isSelected = false;
		this.selectedCell = new int[2];
		this.nextCell = new int[2];
		this.playerChip = player;
		this.ai = new AIPlayer(player == Cells.CELL_RUB ? Cells.CELL_PEARL : Cells.CELL_RUB, 1);
		this.state = -1;       //никто еще не выиграл
		this.boardX = game.getWidth() / 2 - (int) (image.getWidth() / 2 * scale);  //позици€ пол€ по х
		this.returnButton = new Button(game, Assets.returnButtonPressed, Assets.returnButtonReleased, Program.WIDTH / 2, Program.HEIGHT / 2 + 50, new ButtonPressHandler() {
			@Override
			public void press() {
				game.returnToMainMenu();
			}
		});
		this.returnButton.setVisible(false);
		updateCells();
		updateHlights();
	}

	/**
	 *отрисовывает элементов статистики и выигрыша
	 */

	@Override
	public void draw(Graphics2D g2d) {
		g2d.drawImage(image, (int) boardX, 0, (int) (image.getWidth() * scale), (int) (image.getHeight() * scale), null);
		drawCells(g2d, chips);
		int[] count = cells.getChipsCount();
		g2d.setFont(new Font("Arial", Font.BOLD, 20));
		g2d.setColor(Color.WHITE);
		g2d.drawString("You are: ", Program.WIDTH - 150, 32);
		g2d.drawImage(playerChip == Cells.CELL_RUB ? Assets.ruby : Assets.pearl, Program.WIDTH - 32, 8, 32, 32, null);
		g2d.drawString("Turn: ", Program.WIDTH - 150, 80);
		g2d.drawImage(moveMaker == Cells.CELL_RUB ? Assets.ruby : Assets.pearl, Program.WIDTH - 32, 56, 32, 32, null);
		g2d.setColor(Color.PINK);
		g2d.drawImage(Assets.ruby, Program.WIDTH - 32, Program.HEIGHT - 56, 32, 32, null);
		g2d.drawString(count[0] + "", Program.WIDTH - 64, Program.HEIGHT - 32);
		g2d.setColor(Color.CYAN);
		g2d.drawImage(Assets.pearl, Program.WIDTH - 32, Program.HEIGHT - 104, 32, 32, null);
		g2d.drawString(count[1] + "", Program.WIDTH - 64, Program.HEIGHT - 80);
		if (state == 0) {
			drawMessage(true, "Ќ»„№я!", g2d);
		}
		else if (state == Cells.CELL_PEARL) {
			if (playerChip == Cells.CELL_PEARL) {
				drawMessage(true, "¬ы выиграли!", g2d);
			}
			else {
				drawMessage(true, "¬ы проиграли!", g2d);
			}
		}
		else if (state == Cells.CELL_RUB) {
			if (playerChip == Cells.CELL_RUB) {
				drawMessage(true, "¬ы выиграли!", g2d);
			}
			else {
				drawMessage(true, "¬ы проиграли!", g2d);
			}
		}
	}

	/**
	 * ќбновл€ет расположение фишек на поле
	 */
	public void updateCells() {
		chips = new ArrayList<>();
		for (int i = 0; i < Cells.WIDTH; i++) {
			for (int j = 0; j < Cells.WIDTH; j++) {
				int cell = cells.getCell(i, j);
				if (cell > 0) {
					chips.add(new Chip(cell, scale,
							boardX + (BOARD_OFFSET_X + BOARD_GRID_X * i) * scale,
							(BOARD_OFFSET_Y + BOARD_GRID_Y * j + i % 2 * BOARD_GRID_Y / 2) * scale));
				}
			}
		}
	}

	/**
	 * ќбновл€ет расположение подсветок €чеек
	 */
	public void updateHlights() {
		hlights = new ArrayList<>();
		for (int i = 0; i < Cells.WIDTH; i++) {
			for (int j = 0; j < Cells.WIDTH; j++) {
				hlights.add(new Highlight(boardX + (BOARD_OFFSET_X + BOARD_GRID_X * i + HLIGHT_OFFSET_X) * scale,
						(BOARD_OFFSET_Y + BOARD_GRID_Y * j + i % 2 * BOARD_GRID_Y / 2 + HLIGHT_OFFSET_Y) * scale, scale, 1));
			}
		}
	}

	/**
	 * ѕодсвечивает €чейки вокруг выбранной клетки
	 */
	public void highlightCells() {
		if (isSelected) {
			moveCells = new ArrayList<>();
			for (int i = 0; i < hlights.size(); i++) {
				float[] cp = hlights.get(i).getCenterPosition();
				float[] cp2 = selectedHlight.getCenterPosition();
				float dist = (float) Math.sqrt(Math.pow(cp2[0] - cp[0], 2) + Math.pow(cp2[1] - cp[1], 2));
				if (dist < BOARD_GRID_X * 2 && dist != 0 &&
					cells.getCell(i / Cells.WIDTH, i % Cells.WIDTH) == Cells.CELL_EMPTY) {
					hlights.get(i).enable((int) (dist / BOARD_GRID_X));
					moveCells.add(hlights.get(i));
				}
			}
		}
		else {
			for (int i = 0; i < hlights.size(); i++) {
				hlights.get(i).disable();
			}
		}
	}

	/**
	 * ¬ыдел€ет выбранную €чейку (вызываетс€ в обработчике событий мыши) и делает ход
	 */
	public void selectCell() {
		if (moveMaker != playerChip) return;
		Point mp = game.getMousePosition();
		for (int i = 0; i < hlights.size(); i++) {
			Highlight h = hlights.get(i);
			float[] cp = h.getCenterPosition();
			float dist = (float) Math.sqrt(
					(mp.getX() - cp[0]) * (mp.getX() - cp[0]) + (mp.getY() - cp[1]) * (mp.getY() - cp[1]));
			if (dist <= SELECTION_RADIUS) {  //прев€рем, на какую €чейку мы нажали
				int x = i / Cells.WIDTH;
				int y = i % Cells.WIDTH;
				if (h.isEnable() && h == selectedHlight) {
					h.disable();
					selectedHlight = null;
					isSelected = false;
				}
				else if (cells.getCell(x, y) == playerChip && !isSelected) {
					h.enable(1);
					selectedCell[1] = y; //y
					selectedCell[0] = x; //x
					selectedHlight = h;
					isSelected = true;
				}
				highlightCells();
			}
		}
		if (isSelected) {
			for (int i = 0; i < moveCells.size(); i++) {
				Highlight h = moveCells.get(i);
				int j = hlights.indexOf(h);
				float[] cp = h.getCenterPosition();
				float dist = (float) Math.sqrt(
						(mp.getX() - cp[0]) * (mp.getX() - cp[0]) + (mp.getY() - cp[1]) * (mp.getY() - cp[1]));
				if (dist <= SELECTION_RADIUS) {  //прев€рем, на какую €чейку мы нажали
					int x = j / Cells.WIDTH;
					int y = j % Cells.WIDTH;
					nextCell[0] = x;
					nextCell[1] = y;
					if (state < 0) {
						Move move = new Move(selectedCell[0], selectedCell[1], x, y, playerChip);
						try {
							game.connectedPlayer.getObjectOutputStream().writeObject(move);
						}
						catch (Exception e) {
							game.online = false;
							try {
								game.connectedPlayer.getSocket().close();
							} catch (IOException ioException) {
								ioException.printStackTrace();
							}
						}
						makeMove(move);
					}
					state = cells.getWinPlayer();
					isSelected = false;
					highlightCells();
					updateCells();
					if (!game.online) {
						if (state < 0) {
							makeMove(ai.move(cells.copy()));
						}
						state = cells.getWinPlayer();
						updateCells();
					}
				}
			}
		}
	}

	public void makeMove(Move move) {
		playAnimation(move);
		state = cells.getWinPlayer();
		if (state >= 0) {
			if (game.online) {
				try {
					game.connectedPlayer.getObjectOutputStream().writeObject(true);
					game.connectedPlayer.getSocket().close();
					game.online = false;
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}
		moveMaker = moveMaker == Cells.CELL_RUB ? Cells.CELL_PEARL : Cells.CELL_RUB;
		updateCells();
	}

	private void playAnimation(Move move) {
		float[] move_from = Cells.toCoords(move.getFrom().x, move.getFrom().y);                    //переводим в координаты €чеек размером 1 дл€ удобства рассчетов
		float[] move_to = Cells.toCoords(move.getTo().x, move.getTo().y);
		float move_dist = (float) Math.sqrt(Math.pow(move_from[0] - move_to[0], 2) + Math.pow(move_from[1] - move_to[1], 2));

		chips = new ArrayList<>();
		int movedChipType = move.getTeam();
		for (int i = 0; i < Cells.WIDTH; i++) {
			for (int j = 0; j < Cells.WIDTH; j++) {
				int cell = cells.getCell(i, j);
				if (cell > 0) {
					Chip chip = new Chip(cell, scale,
							boardX + (BOARD_OFFSET_X + BOARD_GRID_X * i) * scale,
							(BOARD_OFFSET_Y + BOARD_GRID_Y * j + i % 2 * BOARD_GRID_Y / 2) * scale);
					if (i == move.getFrom().x && j == move.getFrom().y) {
						if (move_dist <= Cells.MIN_RADIUS && move_dist > 0) {
							chips.add(chip);
						}
					}
					else {
						chips.add(chip);
					}
				}
			}
		}

		BufferStrategy bs = game.bs;
		Graphics2D g2d = (Graphics2D) bs.getDrawGraphics();
		for (int i = 0; i < hlights.size(); i++) {
			hlights.get(i).disable();
		}
		draw(g2d);

		double transitionTime = move_dist / 3;

		var image1 = Assets.ruby;
		var image2 = Assets.pearl;
		var img = movedChipType == Cells.CELL_PEARL ?
				image2 :
				image1;

		double startX = boardX + (BOARD_OFFSET_X + BOARD_GRID_X * move.getFrom().x) * scale;
		double startY =
				(BOARD_OFFSET_Y + BOARD_GRID_Y * move.getFrom().y + move.getFrom().x % 2 * BOARD_GRID_Y / 2) * scale;

		double endX = boardX + (BOARD_OFFSET_X + BOARD_GRID_X * move.getTo().x) * scale;
		double endY = (BOARD_OFFSET_Y + BOARD_GRID_Y * move.getTo().y + move.getTo().x % 2 * BOARD_GRID_Y / 2) * scale;

		double diffX = endX - startX;
		double diffY = endY - startY;

		double timeStart = System.nanoTime();
		while ((System.nanoTime() - timeStart) / 1e9f < transitionTime) {
			double coeff = ((System.nanoTime() - timeStart) / 1e9f) / transitionTime;
			double posX = startX + diffX * coeff;
			double posY = startY + diffY * coeff;
			g2d.drawImage(img, (int) posX, (int) posY, (int) (img.getWidth() * scale), (int) (img.getHeight() * scale), null);
		}

		Cells oldCells = cells.copy();
		cells = cells.getMove(move.getFrom().x, move.getFrom().y, move.getTo().x, move.getTo().y);
		updateCells();
		drawCells(g2d, chips);

		transitionTime = 0.75;
		timeStart = System.nanoTime();
		g2d.setColor(Color.MAGENTA);
		g2d.setStroke(new BasicStroke(2));
		while ((System.nanoTime() - timeStart) / 1e9f < transitionTime) {
			boolean foundAny = false;
			for (int i = 0; i < Cells.WIDTH * Cells.WIDTH; i++) {
				int x = i % Cells.WIDTH;
				int y = i / Cells.WIDTH;
				float[] to = Cells.toCoords(move.getTo().x, move.getTo().y);
				float[] coords = Cells.toCoords(x, y);
				int cell = oldCells.getCell(x, y);
				if (cell > 0) {
					float dist = (float) Math.sqrt(Math.pow(to[0] - coords[0], 2) + Math.pow(to[1] - coords[1], 2));
					if (cell != move.getTeam() && dist <= Cells.MIN_RADIUS && dist > 0) {
						startX = boardX + (BOARD_OFFSET_X + BOARD_GRID_X * move.getTo().x + 32) * scale;
						startY = (BOARD_OFFSET_Y + BOARD_GRID_Y * move.getTo().y + move.getTo().x % 2 * BOARD_GRID_Y / 2 + 32) * scale;
						endX = boardX + (BOARD_OFFSET_X + BOARD_GRID_X * x + 32) * scale;
						endY = (BOARD_OFFSET_Y + BOARD_GRID_Y * y + x % 2 * BOARD_GRID_Y / 2 + 32) * scale;

						double displs = 8;

						double startXAdd = (Math.random() - 0.5) * displs;
						double startYAdd = (Math.random() - 0.5) * displs;
						double endXAdd = (Math.random() - 0.5) * displs;
						double endYAdd = (Math.random() - 0.5) * displs;

						g2d.drawLine((int) (startX + startXAdd), (int) (startY + startYAdd), (int) (endX + endXAdd), (int) (endY + endYAdd));
						foundAny = true;
					}
				}
			}
			if (!foundAny) break;
		}
	}

	public void handleMouseReleased() {
		returnButton.setButtonState(false);
		if (returnButton.canBePressed()) {
			returnButton.press();
			returnButton.setVisible(false);
		}
		else {
			selectCell();
		}
	}

	public void handleMousePressed() {
		if (returnButton.canBePressed()) {
			returnButton.setButtonState(true);
		}
	}

	/**
	 * ¬ыводит сообщение по окончании игры
	 *
	 * @param draw ќтображать сообщение
	 * @param text “екст сообщени€
	 * @param g2d  Ётот объект рисует графику
	 */
	private void drawMessage(boolean draw, String text, Graphics2D g2d) {
		int width = 600;
		int height = 100;
		g2d.setColor(new Color(0.7f, 0.1f, 0.9f, 0.5f));
		g2d.fillRect(game.getWidth() / 2 - width / 2, game.getHeight() / 2 - height / 2, width, height);
		g2d.setColor(Color.WHITE);
		g2d.drawString(text, game.getWidth() / 2 - 50, game.getHeight() / 2 - 5);
		g2d.setColor(Color.BLACK);
		returnButton.setVisible(true);
		returnButton.draw(g2d);
	}

	/**
	 * ќтрисовывает все фишки и подсветки
	 * @param g2d
	 */
	private void drawCells(Graphics2D g2d, ArrayList<Chip> chips) {
		for (Highlight h : hlights) {
			h.draw(g2d);
		}
		for (int i = 0; i < chips.size(); i++) {
			Chip c = chips.get(i);
			c.draw(g2d);
		}
	}
}
