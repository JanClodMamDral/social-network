#pragma once

#include <string>
#include <string_view>

namespace social_network
{

class Comment
{
private:
    std::string m_author{};
    std::string m_text{};

public:
    Comment(std::string_view author, std::string_view text);
    ~Comment();

    bool Edit(std::string_view newText);
    void Inspect() const;

    [[nodiscard]] std::string_view GetAuthor() const
    {
        return m_author;
    }

    [[nodiscard]] std::string_view GetText() const
    {
        return m_text;
    }
};

} // namespace social_network
