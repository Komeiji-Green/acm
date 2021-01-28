#include <iostream>
#include <ctime>

using namespace std;

class Human {

};

class Mengchang {
public:
    void sex(const Human& _human) {
        delete this;
    }
    ~Mengchang() {
        printf("awsl\n");
    }
};

int main()
{
    clock_t st, ed;
    st = clock();
    Mengchang* pMengchang = new Mengchang();
    pMengchang->sex(Human());
    ed = clock();
    cout << (double)(ed - st) / CLOCKS_PER_SEC << endl;
}