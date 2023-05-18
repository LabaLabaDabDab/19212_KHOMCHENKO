package nsu.khomchenko.hexxagon;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

/**
 * Ётот класс отвечает за отрисовку подсветки €чейки
 */
public class Highlight implements DrawableEntity {

	private int     type; //тип подсветки
	private boolean enable; //включена или выключена подсветка (зелена€/желта€)
	private float   scale; //масштаб
	private float   x, y; //координаты
	private BufferedImage image; //икона вкл или выкл €чейки

	public Highlight(float x, float y, float scale, int type) {
		this.x = x;
		this.y = y;
		this.type = type;
		enable = false;
		this.scale = scale;
		if (type == 0) {
			image = Assets.highlight1;
		}
		else {
			image = Assets.highlight2;
		}
	}

	@Override
	public void draw(Graphics2D g2d) {
		if (enable) g2d.drawImage(image, (int) x, (int) y, (int) (image.getWidth() * scale), (int) (image.getHeight() *
																									scale), null);
	}

	public float[] getCenterPosition() { //¬озвращает позицию центра €чейки в экранных координатах в виде массива
		return new float[] { image.getWidth() * scale / 2 + x, image.getHeight() * scale / 2 + y };
	}

	public void enable(int type) { //¬ключает подсветку, устанавливает указанный тип и обновл€ет изображение
		this.type = type;
		enable = true;
		if (type == 0) {
			image = Assets.highlight1;
		}
		else {
			image = Assets.highlight2;
		}
	}

	public void disable() { //выключает подсветку
		enable = false;
	}

	public boolean isEnable() { //вкл? чи нет?
		return enable;
	}
}
