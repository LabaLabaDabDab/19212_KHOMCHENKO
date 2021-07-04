public class Program {
    public static String ip;
    public static int port;

    public static void main(String[] args) {
        try {
            ip = args[0];
            port = Integer.parseInt(args[1]);
        } catch (Exception ignored) {
            ip = "localhost";
            port = 2222;
        }

        new SwingView();
    }
}

