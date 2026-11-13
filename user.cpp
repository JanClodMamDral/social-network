#include "user.hpp"
#include "post.hpp"

#include <iostream>
#include <utility>

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
    std::cout<<"[User] уничтожается: " << m_username<< " (записей в ленте: " << m_postsCount << ")" << std::endl;;
}

void User::Inspect() const
{
    std::cout << "О себе: " << m_bio << std::endl;
}

void User::ChangeBio(std::string_view bio)
{
    m_bio = std::string(bio);
}

void User::AddPost(const std::shared_ptr<Post>& post)
{
    if (post == nullptr)
    {
        std::cout << "Ошибка: нельзя добавить пустой указатель вместо записи" << std::endl;
        return;
    }

    if (m_postsCount == m_postsCapacity)
    {
        GrowPosts();
    }

    m_posts[m_postsCount] = post;
    ++m_postsCount;
}

void User::ShowFeed() const
{
    std::cout<<"---Лента пользователя "<<m_username<<"---"<<std::endl;
    Inspect();
    for (std::size_t i = 0; i < m_postsCount; ++i)
    {
        if (const auto post = m_posts[i].lock())
        {
            post->Inspect();
        }
        else
        {
            std::cout << "[запись удалена]" << std::endl;
        }
    }
}

void User::GrowPosts()
{
    const std::size_t newCapacity = (m_postsCapacity == 0) ? 4 : m_postsCapacity * 2;

    auto newPosts = std::make_unique<std::weak_ptr<Post>[]>(newCapacity);
    for (std::size_t i = 0; i < m_postsCount; ++i)
    {
        newPosts[i] = std::move(m_posts[i]);
    }

    m_posts = std::move(newPosts);
    m_postsCapacity = newCapacity;
}

std::size_t User::CountAlivePosts() const
{
    std::size_t alive = 0;
    for (std::size_t i = 0; i < m_postsCount; ++i)
    {
        if (!m_posts[i].expired())
        {
            ++alive;
        }
    }
    return alive;
}
}