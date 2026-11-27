#include "post.hpp"
#include "user.hpp"

#include <iostream>
#include <memory>
#include <utility>

using namespace social_network;

int main()
{
    system("chcp 65001");
    std::cout << "===== unique_ptr: объект уничтожается при выходе из блока =====" << std::endl;
    {
        auto post = std::make_unique<Post>("Пост под управлением unique_ptr");
        post->Inspect();
        std::cout << "Конец блока, освобождать память вручную не нужно" << std::endl;
    }
    std::cout << "Блок закрыт" << std::endl;
    std::cout << std::endl;

    std::cout << "===== unique_ptr: передача владения через std::move =====" << std::endl;
    {
        auto first = std::make_unique<Post>("Пост, у которого меняется владелец");
        auto second = std::move(first);
        std::cout << "После move: first пуст? " << (first == nullptr ? "да" : "нет")
                  << ", second владеет постом? " << (second != nullptr ? "да" : "нет") << std::endl;

        auto comment = std::make_unique<Comment>("anna", "Комментарий передан через move");
        second->AddComment(std::move(comment));
        std::cout << "После передачи комментария посту: comment пуст? "
                  << (comment == nullptr ? "да" : "нет") << std::endl;
        second->Inspect();
    }
    std::cout << std::endl;

    std::cout << "===== shared_ptr: счётчик владельцев =====" << std::endl;
    {
        auto owner1 = std::make_shared<Post>("Пост с несколькими владельцами");
        std::cout << "Создан, use_count = " << owner1.use_count() << std::endl;

        auto owner2 = owner1;
        std::cout << "Копия owner2, use_count = " << owner1.use_count() << std::endl;
        {
            auto owner3 = owner1;
            std::cout << "Копия owner3 во вложенном блоке, use_count = " << owner1.use_count() << std::endl;
        }
        std::cout << "owner3 уничтожена, use_count = " << owner1.use_count() << std::endl;

        owner2.reset();
        std::cout << "owner2.reset(), use_count = " << owner1.use_count() << std::endl;

        std::cout << "owner1.reset() — последний владелец уходит:" << std::endl;
        owner1.reset();
        std::cout << "Объект уничтожен вместе с последним владельцем" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "===== weak_ptr: наблюдатель =====" << std::endl;
    {
        auto sharedPost = std::make_shared<Post>("Пост для наблюдателя");
        std::weak_ptr<Post> observer = sharedPost;
        std::cout << "weak_ptr создан, use_count = " << sharedPost.use_count()
                  << " (наблюдатель владельцем не считается)" << std::endl;

        if (const auto locked = observer.lock())
        {
            std::cout << "lock() вернул указатель, use_count = " << locked.use_count() << std::endl;
            locked->Inspect();
        }

        std::cout << "Последний владелец уходит:" << std::endl;
        sharedPost.reset();

        if (const auto locked = observer.lock())
        {
            locked->Inspect();
        }
        else
        {
            std::cout << "lock() вернул пустой указатель, observer.expired() = "
                      << (observer.expired() ? "true" : "false") << std::endl;
        }
    }
    std::cout << std::endl;

    std::cout << "===== Основной сценарий и проверки правил =====" << std::endl;
    auto welcomePost = std::make_shared<Post>("Хей это первая запись");
    welcomePost->AddComment("masha", "Классный пост");
    welcomePost->AddComment("petr", "Согласен");

    User ivan("ivan34");
    ivan.ChangeBio("люблю запах напалма по утрам");
    ivan.AddPost(welcomePost);
    ivan.ShowFeed();
    std::cout << std::endl;

    Post emptyPost("");
    User noName("");
    welcomePost->AddComment("anon", "");
    welcomePost->EditComment(0, "Очень классный пост");
    welcomePost->EditComment(0, "");
    welcomePost->EditComment(10, "несуществующий");
    welcomePost->Inspect();
    std::cout << std::endl;

    std::cout << "===== Композиция: комментарии умирают вместе с постом =====" << std::endl;
    {
        Post temp("Временный пост");
        temp.AddComment("anna", "Первый!");
        temp.AddComment("boris", "Второй");
        temp.Inspect();
    }
    std::cout << "Блок закрыт" << std::endl;
    std::cout << std::endl;

    std::cout << "===== Агрегация: пост переживает пользователя =====" << std::endl;
    auto tempPost = std::make_shared<Post>("Пост, который останется");
    {
        User temp2("hihiha");
        temp2.AddPost(tempPost);
        temp2.ShowFeed();
    }
    std::cout << "User уничтожен, пост жив, use_count = " << tempPost.use_count() << std::endl;
    tempPost->Inspect();
    std::cout << std::endl;

    std::cout << "===== Агрегация: пользователь переживает пост =====" << std::endl;
    {
        auto vanishing = std::make_shared<Post>("Пост, который скоро удалят");
        ivan.AddPost(vanishing);
        std::cout << "Живых записей в ленте: " << ivan.CountAlivePosts() << std::endl;
    }
    std::cout << "Пост удалён, живых записей в ленте: " << ivan.CountAlivePosts() << std::endl;
    ivan.ShowFeed();
    std::cout << std::endl;

    std::cout << "===== Массив объектов: make_unique<Post[]> =====" << std::endl;
    {
        auto postsArray = std::make_unique<Post[]>(2);
        postsArray[0].EditText("Пост 1");
        postsArray[1].EditText("Пост 2");
        for (int i = 0; i < 2; ++i)
        {
            postsArray[i].Inspect();
        }
    }
    std::cout << std::endl;

    std::cout << "===== Массив умных указателей =====" << std::endl;
    {
        std::unique_ptr<Post> postPtrs[2];
        postPtrs[0] = std::make_unique<Post>("Динамический пост 1");
        postPtrs[1] = std::make_unique<Post>("Динамический пост 2");
        for (int i = 0; i < 2; ++i)
        {
            postPtrs[i]->Inspect();
        }
    }
    std::cout << std::endl;

    std::cout << "===== Конец main =====" << std::endl;
    return 0;
}
