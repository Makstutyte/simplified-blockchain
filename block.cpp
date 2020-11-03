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
#include <cmath>
#include <time.h>


class user
{
  public:
      std::string name;
      std::string public_key;
      int balance; 
};

class transaction
{
  public:
      std::string id;
      std::string sender;
      std::string recipient;
      int sum; 
};

class block 
{
    public:
    std::string prev_hash;
    int64_t timestamp;
    std::string version;
    std::string merkel_root;
    int nonce;
    uint32_t difficulty; // only possitive values
    std::vector<transaction> data;
    block* next;

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

std::random_device rd;
    std::mt19937::result_type seed = rd() ^ (
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now().time_since_epoch()
                ).count() +
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()
                ).count() );
 
    std::mt19937 gen(seed);

void net_users (std::vector<user>& gen_user)
{
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(100, 1000000);

    char key[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
    std::uniform_int_distribution<unsigned> dist1(0, 15);

    std::string txt = "";
    std::string txt1 = "";

    for (int i = 0; i < 1000; i ++) 
    {
        user user1;
        txt = "Vardas"; 
        txt1 = static_cast<std::ostringstream*>( &(std::ostringstream() << i+1) )->str();
        txt.append(txt1); 
        user1.name = txt;

        for(int j = 0; j < 64; j++)
        {
            user1.public_key = user1.public_key + key[dist1(gen)];
        }

        user1.balance = dist(mt);
        gen_user.push_back(user1);

    }
/*std::cout << "--------------------------------------------------------------------------------"<< std::endl;
    for(int i=0; i < gen_user.size(); i++)
        std::cout << std::setw(20) << std::left << gen_user[i].name << std::setw(21) << gen_user[i].public_key <<"\t\t" << gen_user[i].balance << std::endl;

    std::cout << "--------------------------------------------------------------------------------"<< std::endl;*/

}

void transactions(std::vector<transaction>& T)
{
    std::vector<user> gen_user;
    net_users (gen_user); 

	transaction n;
    int kiek=0;
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(0, 999); 

	for (int i = 0; i < 10000; i++)
	{
		int ran, ran1, ran2;
		std::string u1, siuntejas, u3;

		ran = dist(mt);
		n.sender = gen_user[ran].public_key;

        do
        {
            ran1 = dist(mt);
        } while (ran1 == ran);

        n.recipient = gen_user[ran1].public_key;

            do
            {
                    std::uniform_int_distribution<unsigned> dist1(1, gen_user[ran].balance - 1);
                    n.sum = dist1(gen);

                    // TODO aptvarkyti
                    gen_user[ran].balance = gen_user[ran].balance - n.sum;
                    gen_user[ran1].balance = gen_user[ran1].balance + n.sum;
                    //----------------------

            } while(gen_user[ran].balance<0);

        std::string id, num;
        id = n.sender + n.recipient;
        num = static_cast<std::ostringstream*>( &(std::ostringstream() << n.sum) )->str();
        id.append(num); 
        n.id = hash(id);
		
      //  std::cout << std::setw(20) << std::left << n.sender << "\t\t" <<  n.recipient <<  "\t\t" <<  gen_user[ran].balance << " - " << "\t\t" << n.sum  << "\t\t" << " = " << gen_user[ran1].balance << std::endl;

        if (gen_user[ran].balance<=0 )
        kiek++;
  

		T.push_back(n);
	}
    
/*
      std::cout << "--------------------------------------------------------------------------------"<< std::endl;
    for(int i=0; i < T.size(); i++)
        std::cout << std::setw(20) << std::left << T[i].id <<"\t\t" << T[i].sender <<"\t\t" << T[i].recipient<<"\t\t" << T[i].sum << std::endl;
        std::cout << "ATS ->  ";*/
        std::cout << kiek << std::endl;
}


void block_generation (std::vector<block>& gen_block, int x)
{
    block* b;
    std::vector<transaction> T;
    
    
    for(int i=0; i < x; i++)
    {
        b = new block;
      

        int64_t time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        b->timestamp = time;
        b->version = "first";
      //  b->merkel_root = ;
        b->nonce = 1;
        b->difficulty = 2;

        if(i == 0)
        {
             b->prev_hash = "first block";
        }

        else
        {//nepabaigta
            std::string previous = "";
            for(int i=0; i < T.size()/100; i++)
            {
                    std::string tarpinis = "";
                    std::string num;
                    tarpinis =  T[i].id + T[i].sender + T[i].recipient;
                    num = static_cast<std::ostringstream*>( &(std::ostringstream() << T[i].sum) )->str();
                    tarpinis.append(num);
                    hash(tarpinis);



            }

            //b->prev_hash = hash()
        }
        // b->data = transactions(T);
    }

}

int main()
{
    user laikinas;
    std::vector<user> gen_user;
    std::vector<transaction> T;
   // net_users (gen_user); 
    transactions(T);

    return 0;

}
