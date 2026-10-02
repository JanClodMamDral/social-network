#include "post.hpp"
#include <iostream>
namespace social_network
{
Post::Post(std::string_view text)
{
    if (text.empty())
    {
        std::cout<<"Ошибка: текст поста не может быть пустым"<<std::endl;
        m_text = "[пустой пост отклонен]";
    }
    else
    {
        m_text = std::string(text);
    }
}
Post::~Post()
{
    std::cout<<"[Post] уничтожается: \""<<m_text<<"\""<<std::endl;
}

void Post::ПоставитьЛайк()
{
    ++m_likesCount;
}

void Post::Осмотреть() const
{
    std::cout<<"Пост: \""<<m_text<<"\"| Лайков: "<<m_likesCount<<std::endl;
}
}
