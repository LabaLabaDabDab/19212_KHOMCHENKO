package nsu.khomchenko.hexxagon;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

/**
 * Этот класс служит для отрисовки фишек. Содержит ссылки на изображения и координаты фишки.
 */
public class Chip implements DrawableEntity {

	private int           type; //тип фишки: рубин/жемчужина
	private float         scale; //масштаб
	private BufferedImage image1, image2;
	float x, y; //координаты

	public Chip(int type, float scale, float x, float y) {
		this.type = type;
		this.x = x;
		this.y = y;
		this.scale = scale;
		image1 = Assets.ruby;
		image2 = Assets.pearl;
	}

	@Override
	public void draw(Graphics2D g2d) {
		BufferedImage img;
		if (type == Cells.CELL_PEARL) img = image2;
		else if (type == Cells.CELL_RUB) img = image1;
		else return;
		g2d.drawImage(img, (int) x, (int) y, (int) (img.getWidth() * scale), (int) (img.getHeight() * scale), null);
	}
}
