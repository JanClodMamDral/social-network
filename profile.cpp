#include "profile.hpp"
#include <iostream>
namespace social_network
{
Profile::Profile(std::string_view bio)
    :m_bio{bio}
{}

Profile::~Profile()
{
    std::cout<<"[Profile] уничтожается" << std::endl;
}

void Profile::ИзменитьОписание(std::string_view bio)
{
    m_bio = std::string(bio);
}

void Profile::Осмотреть() const
{
    std::cout<<"О себе: "<< m_bio << std::endl;
}
}