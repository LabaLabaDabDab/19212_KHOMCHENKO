import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;

public class Assets {
    public static BufferedImage empty;
    public static BufferedImage gameLogo;

    public static BufferedImage blueO;
    public static BufferedImage blueX;

    public static BufferedImage redO;
    public static BufferedImage redX;

    static {
        try {
            empty = ImageIO.read(ClassLoader.getSystemResource("empty.png"));
            gameLogo = ImageIO.read(ClassLoader.getSystemResource("gameLogo.png"));
            redX = ImageIO.read(ClassLoader.getSystemResource("redX.png"));
            redO = ImageIO.read(ClassLoader.getSystemResource("redO.png"));
            blueX = ImageIO.read(ClassLoader.getSystemResource("blueX.png"));
            blueO = ImageIO.read(ClassLoader.getSystemResource("blueO.png"));
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}
