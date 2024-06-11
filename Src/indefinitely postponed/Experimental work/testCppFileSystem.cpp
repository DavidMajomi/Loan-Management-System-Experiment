#include <filesystem>// cpp 17 reference https://en.cppreference.com/w/cpp/filesystem/current_paths

#include <iostream>
#include <string>

namespace fs = std::filesystem;

int main()
{
    std::string testpath =   std::filesystem::current_path().string();
    std::cout << testpath;

    return 0;
}