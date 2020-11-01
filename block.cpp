#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>
#include <numeric>
#include <limits>
#include <fstream>
#include <random>
#include <chrono>
#include <algorithm>
#include <sstream>
#include <locale>

class Studentas1
{
  public:
      std::string vardas;
      std::string pavarde;
      int egz; 
};

std::string StrRotate(std::string& s, int nLeft)
{
    int size = s.size();

    nLeft %= size;

    if (nLeft == 0) return s;

    std::string after = s.substr(0, nLeft);
    std::string before = s.substr(nLeft, size - nLeft);

    return before + after;
}

std::string toHex(int num1) 
{
    if (num1 == 0)
        return "0";
    int num = num1;
    std::string s = "";
    while (num) 
    {
        int temp = num % 16;
        if (temp <= 9)
            s += (48 + temp);
        else
            s += (87 + temp);
        num = num / 16;
    }
    reverse(s.begin(), s.end());
    return s;
}

bool is_hex(char text)
{
    if (!((text >= '0' && text <= '9') || (text >= 'a' && text <= 'f')))
    {
        return false;
    }

    return true;
}

std::string hash (std::string& txt)
{
    int lenght  = 64;
    std::string default_str =   "gets is considered unsafeand has been removed from the latest Ca";
    std::string default_str2  = "Animacinis serialas apie geltonaja seimynele is Springfildo - Ho"; 
    std::string default_str3  = "Start by adding these lines of code into HelloWorld.cpp file. Th";
    std::string default_str4  = "78542695qwg15862423 Hash'avimo metu bet koks92104638724822loph64";
                               
    std::string copy1 = StrRotate(default_str, 32);
    std::string copy2 = StrRotate(default_str2, 17);
    std::string copy3 = StrRotate(default_str3, 32);
    std::string copy4 = StrRotate(default_str4, 50);
    std::string hash = default_str;
    
    if (!txt.empty())
    {
        int  sum = 0;
            for (int i = 0; txt[i] != '\0'; i++)
                sum = sum + txt[i];

    for(int i = 0; i < txt.length(); i++)
        {
            for(int j = 0; j < lenght; j++)
            {
                int b = 0;
                do
                {
                    b++;
                    hash[j] = (txt[i] * txt[i] + hash[j] + b + i * j * b + (hash[b * i % lenght] * default_str[j]) ^ (txt[b % txt.length()] * sum)) % 128;
                } while (is_hex(hash[j]) != 1);
            }
        }
    }

     if (txt.empty())
        {
            int a1 = 0;
            std::string hash = "";
            for (int i = 0; i < 64; i++)
            {
                int newsymb;
                int tmp1;
                int tmp2;
                int tmp3;
                a1++;
                tmp1 = (copy1[i * i % 64] * a1 *  i) ^ (5 * a1 * i);
                tmp2 = tmp1 & copy4[i * 7 % 64];
                tmp3 = (tmp1 * a1) ^ (tmp2 * i) * 3 + (i * a1) & tmp2;
                newsymb = (tmp3 * 4) ^ (default_str3[i] * a1);
                hash += toHex(newsymb);
            }

            hash = hash.substr(3, 64);
        }

        return hash;
};

void I_FAILA_pazymiu_generavimas (Studentas1& Studentas)
{
    int galas=0; int kiek1; int ST;  int galas_st=0; int nezinau_kas_vyksta=0;  int kiek = 1;
    std::string pavadinimas="1000.txt";

    std::ofstream i_faila(pavadinimas);
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(100, 1000000);
    int a=0; std::vector<int> vektoriukas;

    std::ostringstream eilutis ("");
    eilutis << std::setw(20) << std::left << "VARDAS" << std::setw(21) << "PAVARDE";
    eilutis << "                                                   Egz.\n";
    i_faila << eilutis.str();   
    std::string txt = "";

    for (int i = 0; i < 1000; i ++) 
    {
        eilutis.str(""); 
        eilutis << "Vardas" << std::setw(14) << std::left << i+1;
        txt = static_cast<std::ostringstream*>( &(std::ostringstream() << i+1) )->str();
        eilutis <<  hash(txt) << "        ";
        eilutis << dist(mt);
        eilutis << "\n";
        i_faila << eilutis.str();
    }
}

int main()
{
    Studentas1 laikinas;
    I_FAILA_pazymiu_generavimas (laikinas); 

    return 0;

}
