#include "post.hpp"
#include "profile.hpp"
#include "user.hpp"
#include <iostream>

using namespace social_network;

int main()
{
    system("chcp 65001");
    Post welcomePost("Хей это первая запись");
    std::cout<<std::endl;

    User ivan("ivan34");
    ivan.ЗаполнитьПрофиль("люблю запах напалма по утрам");
    ivan.ДобавитьЗапись(&welcomePost);
    ivan.ПоказатьЛенту();
    std::cout<<std::endl;

    std::cout<<"---Проверка пустой текст поста---"<<std::endl;
    Post emptyPost("");
    std::cout<<std::endl;

    std::cout<<"---Проверка пустое имя пользователя---"<<std::endl;
    User noName("");
    std::cout<<std::endl;

    std::cout<<"---Динамический Post---"<<std::endl;
    Post* dynamicPost = new Post("Пост, созданный динамически");
    dynamicPost->Осмотреть();
    delete dynamicPost;
    std::cout<<std::endl;

    Post referencePost("Пост для демонстрации ссылки и указателя");
    Post& postRef = referencePost;
    Post* postPtr = &referencePost;
    postRef.ПоставитьЛайк();
    postPtr->ПоставитьЛайк();
    postPtr->Осмотреть();
    std::cout<<std::endl;

    std::cout<<"---Динамический массив Post---"<<std::endl;
    Post* postsArray = new Post[2]{Post("Пост 1"),Post("Пост 2")};
    for (int i=0;i<2;++i)
    {
        postsArray[i].Осмотреть();
    }
    delete[] postsArray;
    std::cout<<std::endl;

    std::cout<<"---Массив динамических Post---"<<std::endl;
    Post* postPtrs[2];
    postPtrs[0] = new Post("Динамический пост 1");
    postPtrs[1] = new Post("Динамический пост 2");
    for(int i=0; i<2;++i)
    {
        postPtrs[i]->Осмотреть();
    }
    for(int i=0;i<2;++i)
    {
        delete postPtrs[i];
    }
    std::cout<<std::endl;

    std::cout<<"---Демонстрация композиции---"<<std::endl;
    {
        User temp("megaKnight");
        temp.ЗаполнитьПрофиль("Временный пользователь");
    }
    std::cout<<"Блок закрыт. Сначала уничтожился User, сразу за ним Profile"<<std::endl;
    std::cout<<std::endl;

    std::cout<<"---Демонстрация агрегации---"<<std::endl;
    Post tempPost("Пост, который останется");
    {
        User temp2("hihiha");
        temp2.ДобавитьЗапись(&tempPost);
        temp2.ПоказатьЛенту();
    }
    std::cout<<"User уничтожен, но пост жив:"<<std::endl;
    tempPost.Осмотреть();

    return 0;
}