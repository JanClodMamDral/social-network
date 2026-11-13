package socialnetwork;

public class User {
    private final String username;
    private String bio = "";
    private Post[] posts = new Post[4];
    private int postsCount;

    public User(String username) {
        if (username == null || username.isBlank()) {
            System.out.println("Ошибка: имя пользователя не может быть пустым. Присвоено имя по умолчанию");
            this.username = "unknown";
        } else {
            this.username = username;
        }
    }

    public void changeBio(String bio) {
        this.bio = bio;
    }

    public void addPost(Post post) {
        if (post == null) {
            System.out.println("Ошибка: нельзя добавить пустую ссылку вместо записи");
            return;
        }
        if (postsCount == posts.length) {
            Post[] bigger = new Post[posts.length * 2];
            for (int i = 0; i < postsCount; i++) {
                bigger[i] = posts[i];
            }
            posts = bigger;
        }
        posts[postsCount] = post;
        postsCount++;
    }

    public void showFeed() {
        System.out.println("---Лента пользователя " + username + "---");
        System.out.println("О себе: " + bio);
        for (int i = 0; i < postsCount; i++) {
            System.out.println(posts[i]);
        }
    }

    @Override
    public String toString() {
        return "Пользователь " + username + " (записей: " + postsCount + ")";
    }
}
