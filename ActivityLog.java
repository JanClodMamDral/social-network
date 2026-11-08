package socialnetwork;

/**
 * Журнал действий. Держит ресурс, который нужно освободить в предсказуемый
 * момент, поэтому реализует AutoCloseable и используется в try-with-resources.
 */
public class ActivityLog implements AutoCloseable {
    private final String name;
    private int entriesCount;
    private boolean closed;

    public ActivityLog(String name) {
        this.name = name;
        System.out.println("[ActivityLog] журнал \"" + name + "\" открыт");
    }

    public void log(String message) {
        if (closed) {
            System.out.println("[Отказ] Журнал \"" + name + "\" уже закрыт, запись не сделана");
            return;
        }
        entriesCount++;
        System.out.println("  запись в журнал: " + message);
    }

    public int getEntriesCount() {
        return entriesCount;
    }

    @Override
    public void close() {
        if (closed) {
            return;
        }
        closed = true;
        System.out.println("[ActivityLog] журнал \"" + name + "\" закрыт, записей: " + entriesCount);
    }

    @Override
    public String toString() {
        return "Журнал \"" + name + "\" (записей: " + entriesCount + (closed ? ", закрыт" : "") + ")";
    }
}
