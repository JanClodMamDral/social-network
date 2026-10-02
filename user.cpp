#include "user.hpp"
#include "post.hpp"
#include <iostream>

namespace social_network
{
User::User(std::string_view username)
{
    if (username.empty())
    {
        std::cout<<"Ошибка: имя пользователя не может быть пустым. Присвоено имя по умолчанию"<<std::endl;
        m_username = "unknown";
    }
    else
    {
        m_username = std::string(username);
    }
}    
User::~User()
{
    std::cout<<"[User] уничтожается: "<<m_username<<std::endl;
}

void User::ЗаполнитьПрофиль(std::string_view bio)
{
    m_profile.ИзменитьОписание(bio);
}

void User::ДобавитьЗапись(Post* post)
{
    m_posts.push_back(post);
}

void User::ПоказатьЛенту() const
{
    std::cout<<"---Лента пользователя "<<m_username<<"---"<<std::endl;
    m_profile.Осмотреть();
    for(const Post* post : m_posts)
    {
        post->Осмотреть();
    }
}
}