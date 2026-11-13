package socialnetwork;

import java.lang.ref.WeakReference;

public class Main {
    public static void main(String[] args) {
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

        System.out.println("---Ссылки и копии---");
        Post original = new Post("Исходный пост");
        Post alias = original;
        System.out.println("alias = original — копируется ссылка, а не объект");
        alias.addLike();
        alias.addComment("masha", "Добавлено через вторую переменную");
        System.out.println("Изменили через alias, смотрим через original:");
        System.out.println(original);
        System.out.println("original == alias: " + (original == alias));
        alias = new Post("Совсем другой пост");
        System.out.println("alias теперь указывает на новый объект, original не изменился:");
        System.out.println(original);
        System.out.println("original == alias: " + (original == alias));
        System.out.println();

        System.out.println("---Освобождение ресурса: try-with-resources---");
        try (ActivityLog log = new ActivityLog("сеанс ivan34")) {
            User user = new User("ivan34");
            log.log("создан " + user);
            log.log("пользователь вышел");
            System.out.println("Конец блока try");
        }
        System.out.println("Блок try закрыт, журнал уже освобождён автоматически вызовом close()");
        System.out.println();

        System.out.println("---Сборщик мусора---");
        WeakReference<Post> observer = createForgottenPost();
        System.out.println("Метод завершился, ссылок на пост нет, но объект ещё не уничтожен");
        System.out.println("Объект ещё в памяти: " + (observer.get() != null));
        System.out.println("Просим сборщик мусора: System.gc()");
        System.gc();
        System.out.println("Объект ещё в памяти: " + (observer.get() != null));
    }

    private static WeakReference<Post> createForgottenPost() {
        Post temporary = new Post("Временный пост");
        return new WeakReference<>(temporary);
    }
}
