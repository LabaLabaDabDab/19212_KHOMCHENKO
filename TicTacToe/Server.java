import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    private ServerSocket serverSocket;
    private final ConnectedPlayer[] players;

    public Server(String ipAddress, int port){
        try {
            this.serverSocket = new ServerSocket(port, 8, InetAddress.getByName(ipAddress));
        }
        catch (Exception e){
            this.serverSocket = null;
            System.out.println("Can't create server: " + e.getLocalizedMessage() + ". Try again.");
            System.exit(0);
        }
        players = new ConnectedPlayer[2];
        System.out.println("Server created.");
    }

    public static void main(String[] args) {
        String ip;
        int port;

        try {
            ip = args[0];
            port = Integer.parseInt(args[1]);
        } catch (Exception ignored) {
            ip = "localhost";
            port = 2222;
        }

        Server server = new Server(ip, port);
        server.listenForConnections();
    }

    private boolean allPlayersConnected() {
        for (int i = 0; i < 2; i++) {
            if (players[i] == null) {
                return false;
            }
        }
        return true;
    }

    private void listenForConnections() {
        while (true) {
            try {
                Socket socket = serverSocket.accept();
                synchronized (players) {
                    for (int i = 0; i < 2; i++) {
                        if (players[i] == null) {
                            System.out.println("Player connected");
                            players[i] = new ConnectedPlayer(socket, i);
                            players[i].start();
                            break;
                        }
                    }
                }

                if (allPlayersConnected()) {
                    System.out.println("Game is start...");
                    boolean success = true;
                    for (int i = 0; i < 2; i++) {
                        try {
                            players[i].getObjectOutputStream().writeObject(i);
                        } catch (Exception e) {
                            e.printStackTrace();
                            players[i].getSocket().close();
                            players[i] = null;
                            success = false;
                        }
                    }
                    if (!success) continue;

                    synchronized (players) {
                        while (players[0] != null && players[1] != null) {
                            players.wait();
                        }
                        for (int i = 0; i < 2; i++) {
                            if (players[i] != null) {
                                players[i].closeSocket();
                                players[i] = null;
                            }
                        }
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    private class ConnectedPlayer extends PlayerThread {
        private final int index;
        private boolean working;

        public ConnectedPlayer(Socket socket, int index) throws IOException {
            super(socket);
            this.index = index;
            this.working = true;
        }

        private int getOtherIndex() {
            return index == 0 ? 1 : 0;
        }

        @Override
        public void run() {
            while (working) {
                try {
                    Object obj = getObjectInputStream().readObject();
                    if (obj instanceof Move) {
                        players[getOtherIndex()].getObjectOutputStream().writeObject(obj);
                    }
                } catch (Exception e) {
                    working = false;
                }
            }
            synchronized (players) {
                System.out.println("Player disconnected");
                closeSocket();
                players[index] = null;
                players.notifyAll();
            }
        }
    }
}
