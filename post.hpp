#pragma once

#include "comment.hpp"

#include <cstddef>
#include <memory>
#include <string>
#include <string_view>

namespace social_network
{
class Post
{
private:
    std::string m_text{};
    int m_likesCount{0};
    std::unique_ptr<std::unique_ptr<Comment>[]> m_comments{};
    std::size_t m_commentsCount{ 0 };
    std::size_t m_commentsCapacity{ 0 };

    void GrowComments();

public:
    Post() = default;
    Post(std::string_view text);
    ~Post();

    void AddLike();
    void AddComment(std::string_view author, std::string_view text);
    void AddComment(std::unique_ptr<Comment> comment);
    bool EditComment(std::size_t index, std::string_view newText);
    bool EditText(std::string_view newText);
    void Inspect() const;

    [[nodiscard]]std::string_view GetText() const
    {
        return m_text;
    }

    [[nodiscard]] auto GetLikesCount() const
    {
        return m_likesCount;
    }

    [[nodiscard]] std::size_t GetCommentsCount() const
    {
        return m_commentsCount;
    }
};
}