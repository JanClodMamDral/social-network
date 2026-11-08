package socialnetwork;

import java.lang.ref.WeakReference;

/**
 * Демонстрации работы Java с памятью: ссылки и копии, освобождение ресурса
 * без деструктора, сборщик мусора.
 */
public final class MemoryDemo {
    private MemoryDemo() {
    }

    public static void demonstrateReferences() {
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
    }

    public static void demonstrateResource() {
        System.out.println("---Освобождение ресурса: try-with-resources---");
        try (ActivityLog log = new ActivityLog("сеанс ivan34")) {
            User user = new User("ivan34");
            log.log("создан " + user);
            log.log("пользователь вышел");
            System.out.println("Конец блока try");
        }
        System.out.println("Блок try закрыт, журнал уже освобождён автоматически вызовом close()");
    }

    public static void demonstrateGarbageCollector() throws InterruptedException {
        System.out.println("---Сборщик мусора---");
        WeakReference<Post> observer = createForgottenPost();
        System.out.println("Метод завершился, ссылок на пост нет, но сообщения об уничтожении не было");
        System.out.println("Объект ещё в памяти: " + (observer.get() != null));

        System.out.println("Просим сборщик мусора: System.gc()");
        System.gc();
        Thread.sleep(300);
        System.out.println("Объект ещё в памяти: " + (observer.get() != null));
    }

    private static WeakReference<Post> createForgottenPost() {
        Post temporary = new Post("Временный пост");
        System.out.println("Создан: " + temporary.getText());
        return new WeakReference<>(temporary);
    }
}
