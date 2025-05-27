#include "header.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    std::unordered_map<std::string, std::vector<int>> tekstas;
    cout << "Iveskite failo pavadinima: ";
    std::string failas;
    cin >> failas;
    std::ifstream fd(failas);
    while (!fd.is_open())
    {
        cout << "Failas nerastas, iveskite dar karta: ";
        cin >> failas;
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
            for (size_t i = 0; i < p.second.size(); ++i)
            {
                if (p.second[i] != p.second[i + 1])
                    fr << p.second[i];
                if ((i != p.second.size() - 1) && p.second[i] != p.second[i + 1])
                    fr << ", ";
            }
            fr << "\n";
        }
    }
    fr.close();

    return 0;
}