package socialnetwork;

public class Post {
    private final String text;
    private int likesCount;
    private Comment[] comments = new Comment[4];
    private int commentsCount;

    public Post(String text) {
        if (text == null || text.isBlank()) {
            System.out.println("Ошибка: текст поста не может быть пустым");
            this.text = "[пустой пост отклонён]";
        } else {
            this.text = text;
        }
    }

    public void addLike() {
        likesCount++;
    }

    public void addComment(String author, String commentText) {
        if (commentsCount == comments.length) {
            Comment[] bigger = new Comment[comments.length * 2];
            for (int i = 0; i < commentsCount; i++) {
                bigger[i] = comments[i];
            }
            comments = bigger;
        }
        comments[commentsCount] = new Comment(author, commentText);
        commentsCount++;
    }

    public boolean editComment(int index, String newText) {
        if (index < 0 || index >= commentsCount) {
            System.out.println("[Отказ] Комментария с номером " + index + " не существует");
            return false;
        }
        return comments[index].edit(newText);
    }

    @Override
    public String toString() {
        String result = "Пост: \"" + text + "\" | Лайков: " + likesCount
                + " | Комментариев: " + commentsCount;
        for (int i = 0; i < commentsCount; i++) {
            result += "\n    " + comments[i];
        }
        return result;
    }
}
