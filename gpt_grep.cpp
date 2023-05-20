#include <iostream>
#include <thread>
#include <vector>
#include <filesystem>
#include <fstream>
#include <regex>

namespace fs = std::filesystem;

class GrepTool
{
public:
    explicit GrepTool(const std::string &pattern)
        : pattern_(pattern), regex_(pattern)
    {
    }

    void search(const fs::path &path)
    {
        if (fs::is_directory(path))
        {
            for (const auto &entry : fs::directory_iterator(path))
            {
                search(entry.path());
            }
        }
        else if (fs::is_regular_file(path))
        {
            search_in_file(path);
        }
    }

private:
    void search_in_file(const fs::path &path)
    {
        std::ifstream file(path);

        std::string line;
        size_t line_number = 0;
        while (std::getline(file, line))
        {
            line_number++; // increment line number for each line read
            if (std::regex_search(line, regex_))
            {
                std::cout << "Match in file: " << path
                          << " at line " << line_number
                          << ": " << line << '\n';
            }
        }
    }

    std::string pattern_;
    std::regex regex_;
};

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " PATTERN PATH\n";
        return 1;
    }

    GrepTool tool(argv[1]);
    tool.search(argv[2]);

    return 0;
}