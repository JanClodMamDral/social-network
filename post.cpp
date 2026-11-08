#include "post.hpp"

#include <iostream>
#include <utility>

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
    std::cout<<"[Post] уничтожается: \""<<m_text<<"\""<< "\" (комментариев: " << m_commentsCount << ")" << std::endl;
}

void Post::AddLike()
{
    ++m_likesCount;
}

void Post::Inspect() const
{
    std::cout<<"Пост: \""<<m_text<<"\"| Лайков: "<<m_likesCount<< " | Комментариев: " << m_commentsCount << std::endl;

    for (std::size_t i = 0; i < m_commentsCount; ++i)
    {
        std::cout << "    ";
        m_comments[i]->Inspect();
    }
}

void Post::GrowComments()
{
    const std::size_t newCapacity = (m_commentsCapacity == 0) ? 4 : m_commentsCapacity * 2;

    auto newComments = std::make_unique<std::unique_ptr<Comment>[]>(newCapacity);
    for (std::size_t i = 0; i < m_commentsCount; ++i)
    {
        newComments[i] = std::move(m_comments[i]);
    }

    m_comments = std::move(newComments);
    m_commentsCapacity = newCapacity;
}

void Post::AddComment(std::string_view author, std::string_view text)
{
    AddComment(std::make_unique<Comment>(author, text));
}

void Post::AddComment(std::unique_ptr<Comment> comment)
{
    if (comment == nullptr)
    {
        std::cout << "Ошибка: нельзя добавить пустой указатель вместо комментария" << std::endl;
        return;
    }

    if (m_commentsCount == m_commentsCapacity)
    {
        GrowComments();
    }

    m_comments[m_commentsCount] = std::move(comment);
    ++m_commentsCount;
}

bool Post::EditComment(std::size_t index, std::string_view newText)
{
    if (index >= m_commentsCount)
    {
        std::cout << "[Отказ] Комментария с номером " << index << " не существует" << std::endl;
        return false;
    }

    return m_comments[index]->Edit(newText);
}

bool Post::EditText(std::string_view newText)
{
    if (newText.empty())
    {
        std::cout << "[Отказ] Текст поста не может быть пустым, правка отклонена" << std::endl;
        return false;
    }

    m_text = std::string(newText);
    return true;
}
}
