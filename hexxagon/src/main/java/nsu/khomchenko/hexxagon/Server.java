package nsu.khomchenko.hexxagon;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    private          ServerSocket serverSocket;
    private volatile int          playersConnected = 0;

    private ConnectedPlayer player1;
    private ConnectedPlayer player2;

    public Server(String ipAddr, int port) {
        try {
            this.serverSocket = new ServerSocket(port, 8, InetAddress.getByName(ipAddr));
        }
        catch (Exception e) {
            this.serverSocket = null;
            System.out.println("Can't create server: " + e.getLocalizedMessage() + ". Try again.");
            System.exit(0);
        }
        player1 = null;
        player2 = null;
        System.out.println("Server created.");
    }

    public static void main(String[] args) {
        String ip;
        int port;
        try {
            ip = args[0];
            port = Integer.parseInt(args[1]);
        }
        catch (Exception ignored) {
            ip = "localhost";
            port = 5555;
        }
        Server server = new Server(ip, port);
        server.listenForConnections();
        ThreadPool.INSTANCE.shutdown();
    }

    private void listenForConnections() {
        while (true) {
            try {
                Socket socket = serverSocket.accept();
                if (player1 == null) {
                    player1 = new ConnectedPlayer(socket);
                    ThreadPool.INSTANCE.submitTask(player1);
                }
                else {
                    player2 = new ConnectedPlayer(socket);
                    ThreadPool.INSTANCE.submitTask(player2);
                }
                System.out.print("Player connected\n");
                playersConnected++;
                if (playersConnected == 2) {
                    try {
                        player1.getObjectOutputStream().writeObject(Cells.CELL_RUB);
                        player2.getObjectOutputStream().writeObject(Cells.CELL_PEARL);
                    }
                    catch (Exception e) {
                        e.printStackTrace();
                    }
                    System.out.println("2 players connected. Starting a match.");
                    while (playersConnected == 2) {
                        Thread.onSpinWait();
                    }
                }
            }
            catch (Exception e) {
                System.out.println("Error in server: " + e.getLocalizedMessage());
            }
        }
    }

    private class ConnectedPlayer implements Runnable {
        private final Socket             socket;
        private final ObjectInputStream  objectInputStream;
        private final ObjectOutputStream objectOutputStream;
        private volatile boolean working;

        public ConnectedPlayer(Socket socket) throws IOException {
            this.socket = socket;
            this.objectOutputStream = new ObjectOutputStream(socket.getOutputStream());
            this.objectInputStream = new ObjectInputStream(socket.getInputStream());
            this.working = true;
        }

        public ObjectOutputStream getObjectOutputStream() {
            return this.objectOutputStream;
        }

        @Override
        public void run() {
            while(working) {
                try {
                    Object obj = this.objectInputStream.readObject();
                    if (obj instanceof Move) {
                        Move move = (Move) obj;
                        if (player1 == this) {
                            player2.objectOutputStream.writeObject(move);
                        }
                        else {
                            player1.objectOutputStream.writeObject(move);
                        }
                    }
                    else if (obj instanceof Boolean) {
                        playersConnected--;
                        if (player1 == this) player1 = null;
                        else player2 = null;
                        working = false;
                    }
                }
                catch (Exception e) {
                    e.printStackTrace();
                    if (player1 == this) {
                        player1 = null;
                        try {
                            player2.getObjectOutputStream().writeObject("disconnect");
                        } catch (IOException ioException) {
                            ioException.printStackTrace();
                        }
                        player2.working = false;
                    }
                    else {
                        player2 = null;
                        try {
                            player1.getObjectOutputStream().writeObject("disconnect");
                        } catch (IOException ioException) {
                            ioException.printStackTrace();
                        }
                        player1.working = false;
                    }
                    playersConnected = 0;
                    working = false;
                }
            }
        }
    }
}
