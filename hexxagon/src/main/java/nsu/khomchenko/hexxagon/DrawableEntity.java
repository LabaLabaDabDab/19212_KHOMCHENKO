package nsu.khomchenko.hexxagon;

import java.awt.Graphics2D;

/**
 * Интерфейс для любого объекта, который может быть отрисован на экране и должен обновляться каждый кадр
 */
public interface DrawableEntity {
	void draw(Graphics2D g2d); //Вызывает перерисовку объекта каждый кадр
}
