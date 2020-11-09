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
    int difficulty;
    std::vector<transaction> data;
    block* next;

};

block *t;
block *prev;

class Timer 
{
    private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    public:
    Timer() : start{std::chrono::high_resolution_clock::now()} {}
    void reset() {
    start = std::chrono::high_resolution_clock::now();
    }
    double elapsed() const {
    return std::chrono::duration<double>
    (std::chrono::high_resolution_clock::now() - start).count();
    }
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

std::string hash (std::string const& txt)
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
}

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
}

std::vector<transaction> transactions()
{
    std::vector<user> gen_user;
    net_users (gen_user); 
    std::vector<transaction> T;

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

        std::uniform_int_distribution<unsigned> dist1(1, gen_user[ran].balance - 1);
        n.sum = dist1(gen);

        gen_user[ran].balance = gen_user[ran].balance - n.sum;
        gen_user[ran1].balance = gen_user[ran1].balance + n.sum;

        std::string id, num;
        id = n.sender + n.recipient;
        num = static_cast<std::ostringstream*>( &(std::ostringstream() << n.sum) )->str();
        id.append(num); 
        n.id = hash(id);
		
		T.push_back(n);
	}

          int dydis = 0;

    for(int i=0; i < T.size(); i++)
    {    
        if (T[i].sum < 0 )
        {
            kiek++;
            for(int j=0; j < 1; j++)
            {
                    T.erase(T.begin());
            }
        }
              dydis ++;
    }
     //   std::cout << "NEIGIAMOS TRANSAKCIJU SUMOS ->  ";
     //   std::cout << kiek << std::endl;
     //   std::cout << "KIEK LIKO TRANSAKCIJU PO NEIGIAMU SUMU SALINIMO ->  ";
      //  std::cout << dydis << std::endl;

    int sutampa = 0;
    for(int i=0; i < T.size(); i++)
    {   
        if (T[i].id == hash(T[i].sender + T[i].recipient + std::to_string(T[i].sum)))
        {
            sutampa++;
        }
    }
  //  std::cout << "kiek tranksakcijos informacijos hash'u sutampa su transakcijos ID ->  ";
  //  std::cout << sutampa << std::endl;
	
        return T;
}

std::vector<transaction> slicing(std::vector<transaction>& arr) 
{ 
    int X = 0, Y = 99; 
    auto start = arr.begin() + X; 
    auto end = arr.begin() + Y + 1; 
  
    std::vector<transaction> result(Y - X + 1); 
  
    copy(start, end, result.begin()); 
  
    return result; 
} 

std::string hash_2(std::string &first, std::string &second) 
{
    std::string firstHash = hash(first);
    std::string secondHash = hash(second);
    
    std::string concat = firstHash + secondHash;
    
    std::string ats = hash(concat); 
    
    return ats;
}

std::vector<std::string> merkle(std::vector <std::string> &root_hash) 
{
 
    if (root_hash.size() == 1) 
    {
        return root_hash;
    }

    std::vector <std::string> temp;
    
    for (int i = 0; i < root_hash.size() - 1; i = i + 2) 
    {
        temp.push_back(hash_2(root_hash[i], root_hash[i + 1]));
    }
    
    if (root_hash.size() % 2 == 1) 
    {
        temp.push_back(hash_2(root_hash[root_hash.size() - 1], root_hash[root_hash.size() - 1]));
    }
    
    return merkle(temp);
}


void block_generation(block* &b, std::vector<transaction> &T, int x, int lo)
{
    if(!b)
    {
            b = new block;

        b->version = "first";
        b->difficulty = x;
        b->nonce = 0;

        int64_t time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        b->timestamp = time;

        std::vector<transaction> Tran(100); 

            for(int i=0; i < 100; i++)
            {
                std::uniform_int_distribution<unsigned> dist1(1, T.size() - 1);
                Tran.push_back(T[dist1(gen)]);
            }

        b->data = Tran;


        std::string h = "";
         std::vector<std::string> v(100);
        for(int i = 0; i < 100; i++)
        {
            v.push_back(b->data[i].id);
          //  h += b->data[i].id;
        }                           

        std::vector<std::string> aha;
        aha = merkle(v);

        std::stringstream s;
        std::for_each(std::begin(aha), std::end(aha), [&s](const std::string &elem) { s << elem; } );
   
        std::string labas;
        labas = s.str();

        b->merkel_root = labas;
        b->prev_hash = "0";
        b->next = NULL;
    }

    else
    {
        t = b;
        int n = 0;

        while(t->next)
        {
            t = t->next;
            n++;
        }

        t->next = new block;
        t = t->next;

        prev = b;
        int i = 0;

        while(i < n)
        {
            prev = prev->next;
            i++;
        }

        t->version = "fist";
        t->difficulty = x;
        t->nonce = 0;

        int64_t time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        t->timestamp = time;

        std::vector<transaction> A1(100); 

            for(int i=0; i < 100; i++)
            {
                std::uniform_int_distribution<unsigned> dist1(1, T.size() - 1);
                A1.push_back(T[dist1(gen)]);
            }

        std::vector<transaction> B1(100); 

            for(int i=0; i < 100; i++)
            {
                std::uniform_int_distribution<unsigned> dist1(1, T.size() - 1);
                B1.push_back(T[dist1(gen)]);
            }

        std::vector<transaction> C1(100); 

            for(int i=0; i < 100; i++)
            {
                std::uniform_int_distribution<unsigned> dist1(1, T.size() - 1);
                C1.push_back(T[dist1(gen)]);
            }

        std::vector<transaction> D1(100); 

            for(int i=0; i < 100; i++)
            {
                std::uniform_int_distribution<unsigned> dist1(1, T.size() - 1);
                D1.push_back(T[dist1(gen)]);
            }

        std::vector<transaction> E1(100); 

            for(int i=0; i < 100; i++)
            {
                std::uniform_int_distribution<unsigned> dist1(1, T.size() - 1);
                E1.push_back(T[dist1(gen)]);
            }

                int apsisukimai = 0;

                char diff_target[x + 1];
                for (int i = 0; i < x; ++i) 
                {
                    diff_target[i] = '0';
                }
                diff_target[x] = '\0';

                std::string a(diff_target);


                    std::string next;
                
                    std::string time_int, stringis, diff;
                    stringis = prev->version + prev->prev_hash + prev->merkel_root;
                    time_int = static_cast<std::ostringstream*>( &(std::ostringstream() << prev->timestamp) )->str();
                    diff = static_cast<std::ostringstream*>( &(std::ostringstream() << prev->difficulty) )->str();

                    stringis.append(time_int);
                    stringis.append(diff); 

    bool ar_pavyko = false;
            do
            {
                int what;
                std::uniform_int_distribution<unsigned> dist1(1, 5);
                what = dist1(gen);

                if(what == 1)
                {
                    t->data = A1;
                }

                else if(what == 2)
                {
                    t->data = B1;
                }

               else if(what == 3)
                {
                    t->data = C1;
                }

               else if(what == 4)
                {
                    t->data = D1;
                }

               else if(what == 5)
                {
                    t->data = E1;
                }

                std::vector<std::string> v(100);
                for(int i = 0; i < 100; i++)
                {
                    v.push_back(t->data[i].id);
                }                           

                std::vector<std::string> aha;
                aha = merkle(v);

                std::stringstream s;
                std::for_each(std::begin(aha), std::end(aha), [&s](const std::string &elem) { s << elem; } );
        
                std::string labas;
                labas = s.str();

                t->merkel_root = labas;

                next = stringis;

                do
                {
                    prev->nonce++;
                    std::string h = next + std::to_string(prev->nonce);
                    t->prev_hash = hash(h);
                    apsisukimai++;
                }while(t->prev_hash.substr(0, x) != a || apsisukimai < 100000);


                if(t->prev_hash.substr(0, x) == a )
                    ar_pavyko = true;

            }while(!ar_pavyko);
      


    

        std::cout << "blokas " << lo-1 << "  " << t->prev_hash << std::endl;
        t->next = NULL;
    }
}

int main()
{
    Timer t;
    int kiek = 5;

    std::vector<user> U;
    net_users(U);

    std::vector<transaction> T;
    T = transactions();


    std::cout <<  "generuojami "  << kiek-1 << "   blokai"<< "\n";

    block* B = NULL;
    int i = 1;
    while(kiek)
    {
        block_generation(B, T, 2, i);
        i++;
        kiek --;
    }

    std::cout <<  t.elapsed() << " s\n";

    return 0;

}

