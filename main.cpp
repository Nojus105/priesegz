#include "header.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    std::unordered_map<std::string, std::vector<int>> tekstas;
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

            std::transform(x.begin(), x.end(), x.begin(), ::tolower);
            if (!x.empty())
            {
                tekstas[x].push_back(line_number);
            }
        }
    }
    fd.close();
    std::vector<std::string> tlds;
    std::ifstream file("tlds.txt");
    while (std::getline(file, line))
    {
        if (!line.empty())
        {
            std::transform(line.begin(), line.end(), line.begin(), ::tolower);
            tlds.push_back(line);
        }
    }
    std::set<std::string> link_words;
    std::ofstream fr2("url.txt");
    bool url = false;
    for (const auto &p : tekstas)
    {
        for (const auto &tld : tlds)
        {
            std::string tld_with_dot = "." + tld;
            size_t pos = p.first.rfind(tld_with_dot);
            if (pos != std::string::npos)
            {
                size_t after_tld = pos + tld_with_dot.length();
                if (
                    (after_tld == p.first.length()) ||
                    (after_tld < p.first.length() &&
                     (p.first[after_tld] == '/' || p.first[after_tld] == '?' || p.first[after_tld] == '#')))
                {
                    fr2 << p.first << "\n";
                    link_words.insert(p.first);
                    url = true;
                    break;
                }
            }
        }
    }
    if (!url)
    {
        fr2 << "Nerasta nei viena nuoroda";
    }
    fr2.close();
    std::ofstream fr("rezultatai.txt");
    for (const auto &p : tekstas)
    {
        if (p.second.size() > 1 && link_words.find(p.first) == link_words.end())
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
    std::set<std::string> ort_words;
    for (const auto &p : tekstas)
    {
        if (p.first.find("ort") != std::string::npos)
        {
            std::string cleaned = p.first;
            for (size_t i = 0; i < cleaned.size(); ++i)
            {
                if (std::ispunct(cleaned[i]) && cleaned[i] != '-')
                {
                    cleaned = cleaned.substr(0, i);
                    break;
                }
            }
            if (!cleaned.empty())
                ort_words.insert(cleaned);
        }
    }

    std::vector<std::string> ort_vec(ort_words.begin(), ort_words.end());
    std::sort(ort_vec.rbegin(), ort_vec.rend());

    std::ofstream fr3("ort.txt");
    for (const auto &word : ort_vec)
    {
        fr3 << word << "\n";
    }
    fr3.close();
    std::cout << "Rezultatai issaugoti 'rezultatai.txt' 'url.txt' ir 'ort.txt' failuose.\n";
    std::cout << "Iseiti is programos paspauskite bet kuri klavisa...\n";
    _getch();

    return 0;
}