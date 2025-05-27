#include "header.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    std::unordered_map<std::string, std::vector<int>> tekstas;
    std::set<std::string> url;
    std::cout << "Iveskite failo pavadinima: ";
    std::string failas;
    std::cin >> failas;
    std::ifstream fd(failas);
    while (!fd.is_open())
    {
        std::cout << "Failas nerastas, iveskite dar karta: ";
        std::cin >> failas;
        fd.open(failas);
    }
    std::string line;
    int line_number = 0;
    while (std::getline(fd, line))
    {
        ++line_number;
        std::istringstream iss(line);
        std::string x;
        while (iss >> x)
        {
            while (!x.empty() && std::ispunct(x.back()))
                x.pop_back();
            while (!x.empty() && std::ispunct(x.front()))
                x.erase(x.begin());

            for (const auto &tld : tlds)
            {
                size_t pos = x.find(tld);
                if (pos != std::string::npos)
                {
                    if (pos + tld.length() == x.length() || x[pos + tld.length()] == '/' || x[pos + tld.length()] == '?' || x[pos + tld.length()] == '#')
                    {
                        url.insert(x);
                        break;
                    }
                }
            }

            x.erase(std::remove_if(x.begin(), x.end(), [](unsigned char c)
                                   { return std::ispunct(c); }),
                    x.end());
            std::transform(x.begin(), x.end(), x.begin(), ::tolower);
            if (!x.empty())
            {
                tekstas[x].push_back(line_number);
            }
        }
    }
    fd.close();
    std::ofstream fr("rezultatai.txt");
    for (const auto &p : tekstas)
    {
        if (p.second.size() > 1)
        {
            fr << p.first << " (" << p.second.size() << " kartus) eilutese: ";
            std::set<int> lines(p.second.begin(), p.second.end());
            size_t count = 0;
            for (int line : lines)
            {
                fr << line;
                if (++count < lines.size())
                    fr << ", ";
            }
            fr << "\n";
        }
    }
    fr.close();
    std::ofstream fr2("url.txt");
    if (url.empty())
    {
        fr2 << "Nerasta nei viena nuoroda";
    }
    else
    {
        for (const auto &u : url)
        {
            fr2 << u << "\n";
        }
    }
    fr2.close();

    return 0;
}