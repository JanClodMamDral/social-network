package socialnetwork;

import java.lang.ref.Cleaner;
import java.util.ArrayList;
import java.util.List;

/**
 * Запись. Владеет своими комментариями (композиция): список и комментарии
 * создаёт сама, наружу ссылки на комментарии не отдаёт.
 */
public final class Post {
    private static final Cleaner CLEANER = Cleaner.create();

    private final String text;
    private int likesCount;
    private final List<Comment> comments;

    public Post(String text) {
        if (text == null || text.isBlank()) {
            System.out.println("Ошибка: текст поста не может быть пустым");
            this.text = "[пустой пост отклонён]";
        } else {
            this.text = text;
        }
        this.comments = new ArrayList<>();
        CLEANER.register(this, new PostCleanup(this.text));
    }

    public void addLike() {
        likesCount++;
    }

    public void addComment(String author, String commentText) {
        comments.add(new Comment(author, commentText));
    }

    public boolean editComment(int index, String newText) {
        if (index < 0 || index >= comments.size()) {
            System.out.println("[Отказ] Комментария с номером " + index + " не существует");
            return false;
        }
        return comments.get(index).edit(newText);
    }

    public String getText() {
        return text;
    }

    public int getLikesCount() {
        return likesCount;
    }

    public int getCommentsCount() {
        return comments.size();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Пост: \"").append(text).append("\" | Лайков: ").append(likesCount)
                .append(" | Комментариев: ").append(comments.size());
        for (Comment comment : comments) {
            sb.append(System.lineSeparator()).append("    ").append(comment);
        }
        return sb.toString();
    }

    /**
     * Действие очистки. Не должно ссылаться на сам Post, иначе пост никогда
     * не станет недостижимым, поэтому хранит только копию текста.
     */
    private static class PostCleanup implements Runnable {
        private final String postText;

        PostCleanup(String postText) {
            this.postText = postText;
        }

        @Override
        public void run() {
            System.out.println("[Post] уничтожен сборщиком мусора: \"" + postText + "\"");
        }
    }
}
