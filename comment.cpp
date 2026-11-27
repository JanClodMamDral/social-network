#include "comment.hpp"

#include <iostream>

namespace social_network
{

Comment::Comment(std::string_view author, std::string_view text)
    : m_author{ author }
{
    if (text.empty())
    {
        std::cout << "Ошибка: текст комментария не может быть пустым" << std::endl;
        m_text = "[пустой комментарий отклонён]";
    }
    else
    {
        m_text = std::string(text);
    }
}

Comment::~Comment()
{
    std::cout << "[Comment] уничтожается: " << m_author << ": \"" << m_text << "\"" << std::endl;
}

bool Comment::Edit(std::string_view newText)
{
    if (newText.empty())
    {
        std::cout << "[Отказ] Текст комментария не может быть пустым, правка отклонена" << std::endl;
        return false;
    }

    m_text = std::string(newText);
    return true;
}

void Comment::Inspect() const
{
    std::cout << "Комментарий от " << m_author << ": \"" << m_text << "\"" << std::endl;
}

} // namespace social_network
