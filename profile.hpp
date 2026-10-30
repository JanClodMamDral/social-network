#pragma once

#include <string>
#include <string_view>

namespace social_network
{
class Profile
{
private:    
    std::string m_bio{};

public:
    Profile()=default;
    Profile(std::string_view bio);    
    ~Profile();

    void ИзменитьОписание(std::string_view bio); 
    void Осмотреть() const;

    [[nodiscard]] std::string_view GetBio() const
    {
        return m_bio;
    }
};
}