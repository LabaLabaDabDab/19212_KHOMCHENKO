package nsu.khomchenko.hexxagon;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.image.BufferStrategy;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

/**
 * Основной поток приложения, в котором происходит обновление графики и параметров
 */

public class Game extends Canvas implements Runnable {
	private static final int TARGET_FPS = 60;

	public BufferStrategy bs;
	public volatile int            menuType = 0;
	public volatile boolean        online   = false;

	public volatile ConnectedPlayer connectedPlayer;

	private final    Thread  thread;
	private volatile boolean running;

	private final Button startGameButton;
	private final Button connectGameButton;
	private final Button cancelGameButton;

	private Board board;

	public Game() {
		super();
		this.thread = new Thread(this);
		Assets.init();
		connectedPlayer = null;

		startGameButton = new Button(this, Assets.startGameButtonPressed, Assets.startGameButtonReleased,
				Program.WIDTH / 2, Program.HEIGHT * 3 / 4 - 50, new ButtonPressHandler() {
			@Override
			public void press() {
				startGameButton.setVisible(false);
				connectGameButton.setVisible(false);
				online = false;
				init(Cells.CELL_RUB);
				menuType = 1;
				connectedPlayer = null;
			}
		});

		connectGameButton = new Button(this, Assets.connectButtonPressed, Assets.connectButtonReleased,
				Program.WIDTH / 2, Program.HEIGHT * 3 / 4 + 50, new ButtonPressHandler() {
			@Override
			public void press() {
				try {
					Socket socket = new Socket(Program.ip, Program.port);
					online = true;
					connectedPlayer = new ConnectedPlayer(socket);
					ThreadPool.INSTANCE.submitTask(connectedPlayer);
					startGameButton.setVisible(false);
					connectGameButton.setVisible(false);
					cancelGameButton.setVisible(true);
					menuType = 2;
				}
				catch (IOException e) {
					e.printStackTrace();
				}
			}
		});

		cancelGameButton = new Button(this, Assets.cancelButtonPressed, Assets.cancelButtonReleased,
				Program.WIDTH / 2, Program.HEIGHT / 2 + 50, new ButtonPressHandler() {
			@Override
			public void press() {
				try {
					connectedPlayer.getObjectOutputStream().writeObject(true);
					connectedPlayer.getSocket().close();
				}
				catch (Exception e) {
					e.printStackTrace();
				}
				startGameButton.setVisible(true);
				connectGameButton.setVisible(true);
				cancelGameButton.setVisible(false);
				online = false;
				connectedPlayer = null;
				menuType = 0;
			}
		});
	}

	/**
	 * Запускает поток
	 */
	public void start() {
		this.menuType = 0;
		this.startGameButton.setVisible(true);
		this.connectGameButton.setVisible(true);
		this.cancelGameButton.setVisible(false);
		this.running = true;
		this.thread.start();
	}

	/**
	 * Инициализация
	 */
	public void init(int player) {
		this.board = new Board(this, player);
	}

	public void returnToMainMenu() {
		startGameButton.setVisible(true);
		connectGameButton.setVisible(true);
		cancelGameButton.setVisible(false);
		menuType = 0;
		online = false;
		connectedPlayer = null;
	}

	/**
	 * рендер задника
	 */
	public void render() {
		int w = getWidth();
		int h = getHeight();

		bs = getBufferStrategy();
		if (bs == null) {
			createBufferStrategy(2); //создаем BufferStrategy для нашего холста
			requestFocus();
			return;
		}

		Graphics2D g2d = (Graphics2D) bs.getDrawGraphics(); //получаем Graphics из созданной нами BufferStrategy

		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		g2d.fillRect(0, 0, w, h);
		g2d.setColor(Color.BLACK);
		switch (menuType) {
			case 0 -> {
				BufferedImage img = Assets.gameLogo;
				g2d.drawImage(img, Program.WIDTH / 2 - img.getWidth() / 2, Program.HEIGHT / 4 - img.getHeight() / 2, img.getWidth(), img.getHeight(), null);
				startGameButton.draw(g2d);
				connectGameButton.draw(g2d);
			}
			case 1 -> {
				board.draw(g2d);
			}
			case 2 -> {
				g2d.setColor(Color.WHITE);
				g2d.setFont(new Font("Arial", Font.BOLD, 20));
				g2d.drawString("Waiting for other player...", Program.WIDTH / 2, Program.HEIGHT / 2);
				cancelGameButton.draw(g2d);
			}
		}
		g2d.dispose();
		bs.show();
	}

	public void stop() { //Остановка выполнения главного потока приложения
		this.running = false;
	}

	public void handleMouseReleased() { //обработка отпускания мышки
		switch (menuType) {
			case 0 -> {
				startGameButton.setButtonState(false);
				connectGameButton.setButtonState(false);
				if (startGameButton.canBePressed()) {
					startGameButton.press();
				}
				if (connectGameButton.canBePressed()) {
					connectGameButton.press();
				}
			}
			case 1 -> {
				board.handleMouseReleased();
			}
			case 2 -> {
				cancelGameButton.setButtonState(false);
				if (cancelGameButton.canBePressed()) {
					cancelGameButton.press();
					cancelGameButton.setVisible(false);
				}
			}
		}
	}

	public void handleMousePressed() { //обработка удержания мышки
		switch (menuType) {
			case 0 -> {
				if (startGameButton.canBePressed()) {
					startGameButton.setButtonState(true);
				}
				if (connectGameButton.canBePressed()) {
					connectGameButton.setButtonState(true);
				}
			}
			case 1 -> {
				board.handleMousePressed();
			}
			case 2 -> {
				if (cancelGameButton.canBePressed()) {
					cancelGameButton.setButtonState(true);
				}
			}
		}
	}

	@Override
	public void run() {
		while (running) {
			if (this.isDisplayable()) render();
			try {
				if (Thread.currentThread() == this.thread) Thread.sleep(1000 / TARGET_FPS); //устанавливаем число кадров в секунду
			}
			catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

	public class ConnectedPlayer implements Runnable {
		private final Socket             socket;
		private final ObjectInputStream  objectInputStream;
		private final ObjectOutputStream objectOutputStream;

		public ConnectedPlayer(Socket socket) throws IOException {
			this.socket = socket;
			this.objectOutputStream = new ObjectOutputStream(socket.getOutputStream());
			this.objectInputStream = new ObjectInputStream(socket.getInputStream());
		}

		public Socket getSocket() {
			return this.socket;
		}

		public ObjectInputStream getObjectInputStream() {
			return this.objectInputStream;
		}

		public ObjectOutputStream getObjectOutputStream() {
			return this.objectOutputStream;
		}

		@Override
		public void run() {
			while (online) {
				try {
					Object obj = this.objectInputStream.readObject();
					System.out.println("Read object");
					if (obj instanceof Move) {
						board.makeMove((Move) obj);
					}
					else if(obj instanceof Integer){
						cancelGameButton.setVisible(false);
						init((Integer) obj);
						menuType = 1;
					}
					else if (obj instanceof String) {
						String str = (String) obj;
						if (str.equalsIgnoreCase("disconnect")) {
							online = false;
							socket.close();
							if (board.moveMaker != board.playerChip) {
								if (board.state < 0) {
									board.makeMove(board.ai.move(board.cells.copy()));
								}
								board.state = board.cells.getWinPlayer();
								board.updateCells();
							}
						}
					}
				}
				catch (Exception e) {
					e.printStackTrace();
					online = false;
					try {
						socket.close();
					} catch (IOException ioException) {
						ioException.printStackTrace();
					}
					if (board.moveMaker != board.playerChip) {
						if (board.state < 0) {
							board.makeMove(board.ai.move(board.cells.copy()));
						}
						board.state = board.cells.getWinPlayer();
						board.updateCells();
					}
				}
			}
		}
	}
}
