package nsu.khomchenko.hexxagon;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

/**
 * Ётот класс загружает все необходимые изображени€ и ресурсы дл€ игры и хранит их.
 */

public class Assets {
	public static BufferedImage field;
	public static BufferedImage ruby;
	public static BufferedImage pearl;
	public static BufferedImage highlight1;
	public static BufferedImage highlight2;
	public static BufferedImage gameLogo;

	public static BufferedImage startGameButtonPressed;
	public static BufferedImage startGameButtonReleased;

	public static BufferedImage returnButtonPressed;
	public static BufferedImage returnButtonReleased;

	public static BufferedImage connectButtonPressed;
	public static BufferedImage connectButtonReleased;

	public static BufferedImage cancelButtonPressed;
	public static BufferedImage cancelButtonReleased;

	/**
	 * ¬ызываетс€ дл€ загрузки изображений и ресурсов
	 */
	public static void init() {
		try {
			field = ImageIO.read(ClassLoader.getSystemResource("images/hexagon_field.png"));
			ruby = ImageIO.read(ClassLoader.getSystemResource("images/rubin.png"));
			pearl = ImageIO.read(ClassLoader.getSystemResource("images/pearl.png"));
			highlight1 = ImageIO.read(ClassLoader.getSystemResource("images/hl1.png"));
			highlight2 = ImageIO.read(ClassLoader.getSystemResource("images/hl2.png"));
			gameLogo = ImageIO.read(ClassLoader.getSystemResource("images/GameLogo.png"));

			startGameButtonPressed = ImageIO.read(ClassLoader.getSystemResource("images/startGameButtonPressed.png"));
			startGameButtonReleased = ImageIO.read(ClassLoader.getSystemResource("images/startGameButtonReleased.png"));

			returnButtonPressed = ImageIO.read(ClassLoader.getSystemResource("images/returnButtonPressed.png"));
			returnButtonReleased = ImageIO.read(ClassLoader.getSystemResource("images/returnButtonReleased.png"));

			connectButtonPressed = ImageIO.read(ClassLoader.getSystemResource("images/connectButtonPressed.png"));
			connectButtonReleased = ImageIO.read(ClassLoader.getSystemResource("images/connectButtonReleased.png"));

			cancelButtonPressed = ImageIO.read(ClassLoader.getSystemResource("images/cancelButtonPressed.png"));
			cancelButtonReleased = ImageIO.read(ClassLoader.getSystemResource("images/cancelButtonReleased.png"));
		}
		catch (IOException e) {
			e.printStackTrace();
		}
	}
}
