package socialnetwork;

public class Comment {
    private final String author;
    private String text;

    public Comment(String author, String text) {
        this.author = author;
        if (text == null || text.isBlank()) {
            System.out.println("Ошибка: текст комментария не может быть пустым");
            this.text = "[пустой комментарий отклонён]";
        } else {
            this.text = text;
        }
    }

    public boolean edit(String newText) {
        if (newText == null || newText.isBlank()) {
            System.out.println("[Отказ] Текст комментария не может быть пустым, правка отклонена");
            return false;
        }
        text = newText;
        return true;
    }

    @Override
    public String toString() {
        return "Комментарий от " + author + ": \"" + text + "\"";
    }
}
