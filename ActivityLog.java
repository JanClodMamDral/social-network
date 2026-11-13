package socialnetwork;

public class ActivityLog implements AutoCloseable {
    private final String name;
    private int entriesCount;

    public ActivityLog(String name) {
        this.name = name;
        System.out.println("[ActivityLog] журнал \"" + name + "\" открыт");
    }

    public void log(String message) {
        entriesCount++;
        System.out.println("  запись в журнал: " + message);
    }

    @Override
    public void close() {
        System.out.println("[ActivityLog] журнал \"" + name + "\" закрыт, записей: " + entriesCount);
    }
}
