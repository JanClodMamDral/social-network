package socialnetwork;

import java.util.ArrayList;
import java.util.List;

/**
 * Пользователь. Хранит ссылки на записи, созданные снаружи (агрегация):
 * записи не принадлежат пользователю и существуют, пока на них есть ссылки.
 */
public class User {
    private final String username;
    private String bio = "";
    private final List<Post> posts = new ArrayList<>();

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
        posts.add(post);
    }

    public void showFeed() {
        System.out.println("---Лента пользователя " + username + "---");
        System.out.println("О себе: " + bio);
        for (Post post : posts) {
            System.out.println(post);
        }
    }

    public String getUsername() {
        return username;
    }

    public String getBio() {
        return bio;
    }

    @Override
    public String toString() {
        return "Пользователь " + username + " (записей: " + posts.size() + ")";
    }
}
