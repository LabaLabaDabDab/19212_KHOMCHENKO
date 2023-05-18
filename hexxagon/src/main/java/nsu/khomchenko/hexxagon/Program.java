package nsu.khomchenko.hexxagon;

import java.awt.Dimension;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JFrame;

/**
 * Основной класс программы. Инициализирует окна, графику и вызывает основной игровой поток
 */

public class Program {
	private static       Game   game;
	private static final String TITLE = "Hexxagon";
	public static final  int    WIDTH = 1280;
	public static final  int    HEIGHT = 720;

	public static String ip;
	public static int port;

	public static void main(String[] args) {
		try {
			ip = args[0];
			port = Integer.parseInt(args[1]);
		}
		catch (Exception ignored) {
			ip = "localhost";
			port = 5555;
		}

		JFrame frame = new JFrame(TITLE);
		frame.setBounds(10, 10, WIDTH, HEIGHT);
		frame.setLocationRelativeTo(null);
		frame.setResizable(false);

		game = new Game();
		game.setPreferredSize(new Dimension(WIDTH, HEIGHT));

		frame.add(game);
		frame.pack();
		frame.setVisible(true);
		frame.addWindowListener(new GameWindowAdapter());

		game.addMouseListener(new GameMouseListener());
		game.start();
	}

	private static class GameMouseListener implements MouseListener {
		@Override
		public void mouseReleased(MouseEvent e) {
			game.handleMouseReleased();
		}

		@Override
		public void mousePressed(MouseEvent e) {
			game.handleMousePressed();
		}

		@Override
		public void mouseExited(MouseEvent e) {

		}

		@Override
		public void mouseEntered(MouseEvent e) {

		}

		@Override
		public void mouseClicked(MouseEvent e) {

		}
	}

	private static class GameWindowAdapter extends WindowAdapter {
		@Override
		public void windowClosing(WindowEvent e) {
			try {
				game.connectedPlayer.getSocket().close();
			}
			catch (Exception ignored) {

			}
			game.stop();
			ThreadPool.INSTANCE.shutdown();
			System.exit(0);
		}
	}
}
