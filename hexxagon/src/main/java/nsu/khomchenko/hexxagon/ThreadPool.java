package nsu.khomchenko.hexxagon;

import java.util.concurrent.ScheduledThreadPoolExecutor;
import java.util.concurrent.ThreadPoolExecutor;

public final class ThreadPool {
    public static final ThreadPool INSTANCE = new ThreadPool(4);

    private final ThreadPoolExecutor threadPoolExecutor;

    public ThreadPool(int maxThreads) {
        this.threadPoolExecutor = new ScheduledThreadPoolExecutor(maxThreads);
    }

    public void submitTask(Runnable task) {
        try {
            threadPoolExecutor.submit(task);
        }
        catch (Exception ignored) {}
    }

    public void shutdown() {
        threadPoolExecutor.shutdown();
    }
}