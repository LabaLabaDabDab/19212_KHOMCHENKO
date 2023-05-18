package nsu.khomchenko.hexxagon;

import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.image.BufferedImage;

public class Button {
    private Game game;
    private BufferedImage pressedImg; //нажатая кнопка
    private BufferedImage img; //просто кнопка
    private int centerX;
    private int centerY;
    private ButtonPressHandler buttonPressHandler;
    private boolean isPressed;
    private boolean isVisible;

    public Button(Game game, BufferedImage pressedImg, BufferedImage releasedImg, int centerX, int centerY, ButtonPressHandler buttonPressHandler) {
        this.game = game;
        this.pressedImg = pressedImg;
        this.img = releasedImg;
        this.centerX = centerX;
        this.centerY = centerY;
        this.buttonPressHandler = buttonPressHandler;
        this.isPressed = false;
        this.isVisible = false;
    }

    public void draw(Graphics2D g2d) { //отрисовывает вид кнопки
        if (isVisible) {
            g2d.drawImage(isPressed ?
                    pressedImg :
                    img, centerX - img.getWidth() / 2, centerY - img.getHeight() / 2, img.getWidth(), img.getHeight(), null);
        }
    }

    public boolean canBePressed() { //проверка: находится ли курсор мышки на кнопке
        if (!isVisible) return false;
        Point mp = game.getMousePosition();
        return mp.getX() >= centerX - img.getWidth() / 2 && mp.getX() <= centerX + img.getWidth() / 2 &&
               mp.getY() >= centerY - img.getHeight() / 2 && mp.getY() <= centerY + img.getHeight() / 2;
    }

    public boolean isVisible() {
        return this.isVisible;
    }

    public void setVisible(boolean visible) {
        this.isVisible = visible;
    }

    public void press() {
        if (this.isVisible) {
            buttonPressHandler.press();
        }
    }

    public void setButtonState(boolean isPressed) {
        this.isPressed = isPressed;
    }
}
