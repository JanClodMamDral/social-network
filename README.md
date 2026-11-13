# ЛР 3, часть 1 — консольная социальная сеть на Java

Перенос проекта из ЛР 2 (C++) на Java. Классы те же: `User`, `Post`, `Comment`;
дополнительно `ActivityLog` (журнал, демонстрация `AutoCloseable`).
Демонстрации работы Java с памятью находятся в `Main`.
Из стандартной библиотеки используется только `java.lang.ref.WeakReference`.

## Структура

```
lab3-java/
├── src/socialnetwork/
│   ├── Comment.java      — комментарий (часть поста)
│   ├── Post.java         — запись; владеет комментариями (композиция)
│   ├── User.java         — пользователь; хранит ссылки на посты (агрегация)
│   ├── ActivityLog.java  — журнал, AutoCloseable
│   └── Main.java         — демонстрационная программа
└── README.md
```

## Связи

- **Композиция `Post` → `Comment`:** пост сам создаёт массив и комментарии
  (`new Comment(...)` внутри `addComment`) и не отдаёт ссылки на них наружу.
- **Агрегация `User` → `Post`:** пост создаётся снаружи и передаётся готовым
  в `addPost(Post)`; пользователь хранит только ссылку.

## Требования

JDK 11 или новее (используется `String.isBlank`). Проверить: `javac -version`.

## Сборка

PowerShell (Windows):

```powershell
javac -encoding UTF-8 -d out (Get-ChildItem *.java).FullName
```

bash (Linux / macOS):

```bash
javac -encoding UTF-8 -d out src/socialnetwork/*.java
```

## Запуск

PowerShell (Windows):

```powershell
java -cp out socialnetwork.Main
```

Linux / macOS:

```
java -cp out socialnetwork.Main
```

## Что показывает программа

1. Основной сценарий: пост, комментарии, пользователь, лента.
2. Проверки правил: пустой пост, пустое имя, пустой комментарий, правка
   несуществующего комментария.
3. Композиция и агрегация (ссылки, кто кого создаёт).
4. **Ссылки и копии:** присваивание копирует ссылку; изменение через
   вторую переменную видно через первую.
5. **Освобождение ресурса:** `ActivityLog` в `try`-with-resources,
   `close()` вызывается при выходе из блока.
6. **Сборщик мусора:** объект без сильных ссылок не уничтожается при выходе
   из метода, а только после `System.gc()`; это видно по `WeakReference`.
   `System.gc()` — лишь просьба сборщику.
