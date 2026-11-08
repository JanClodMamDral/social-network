package socialnetwork;

import java.io.PrintStream;
import java.nio.charset.StandardCharsets;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        System.setOut(new PrintStream(System.out, true, StandardCharsets.UTF_8));

        System.out.println("===== Основной сценарий =====");
        Post welcomePost = new Post("Хей это первая запись");
        welcomePost.addComment("masha", "Классный пост");
        welcomePost.addComment("petr", "Согласен");

        User ivan = new User("ivan34");
        ivan.changeBio("люблю запах напалма по утрам");
        ivan.addPost(welcomePost);
        ivan.showFeed();
        System.out.println();

        System.out.println("===== Проверки правил =====");
        new Post("");
        new User("");
        welcomePost.addComment("anon", "");
        welcomePost.editComment(0, "Очень классный пост");
        welcomePost.editComment(0, "");
        welcomePost.editComment(10, "несуществующий");
        System.out.println(welcomePost);
        System.out.println();

        System.out.println("===== Композиция =====");
        Post commented = new Post("Пост с комментариями");
        commented.addComment("anna", "Первый!");
        commented.addComment("boris", "Второй");
        System.out.println(commented);
        System.out.println("Комментарии создал сам пост, снаружи на них нет ссылок");
        System.out.println();

        System.out.println("===== Агрегация =====");
        Post sharedPost = new Post("Пост, созданный снаружи");
        {
            User temp = new User("hihiha");
            temp.addPost(sharedPost);
            temp.showFeed();
        }
        System.out.println("Блок закрыт, пост доступен по своей ссылке:");
        System.out.println(sharedPost);
        System.out.println();

        MemoryDemo.demonstrateReferences();
        System.out.println();
        MemoryDemo.demonstrateResource();
        System.out.println();
        MemoryDemo.demonstrateGarbageCollector();
    }
}
