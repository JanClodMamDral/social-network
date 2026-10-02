#pragma once

#include <string>
#include <string_view>

namespace social_network
{
class Post
{
    std::string m_text{};
    int m_likesCount{0};

public:
    Post() = default;
    Post(std::string_view text);
    ~Post();

    void ПоставитьЛайк();
    void Осмотреть() const;

    [[nodiscard]]std::string_view GetText() const
    {
        return m_text;
    }

    [[nodiscard]] auto GetLikesCount() const
    {
        return m_likesCount;
    }
};
}