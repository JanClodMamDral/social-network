#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <string_view>


namespace social_network
{
class Post;

class User
{
private:    
    std::string m_username{};
    std::string m_bio{};
    std::unique_ptr<std::weak_ptr<Post>[]> m_posts{};
    std::size_t m_postsCount{ 0 };
    std::size_t m_postsCapacity{ 0 };

    void GrowPosts();

public:
    User(std::string_view username);
    ~User();

    void ChangeBio(std::string_view bio);
    void Inspect() const;
    void AddPost(const std::shared_ptr<Post>& post);
    void ShowFeed() const;

    [[nodiscard]] std::string_view GetUsername() const
    {
        return m_username;
    }

    [[nodiscard]] std::string_view GetBio() const
    {
        return m_bio;
    }

    [[nodiscard]] std::size_t CountAlivePosts() const;
};
}