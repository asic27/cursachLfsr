#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdint>
using namespace std;
typedef unsigned long long int	_uint64_t;
int LFSR_Galois (_uint64_t branch)
{
    // for polynomial 0x80000057, reversed 0xea000001 poli.find("^")+i!='+';
    typedef unsigned long long int	_uint64_t;
    static _uint64_t S = 0x80000001;
    if (S & 0x00000001) {
        S = ((S ^ branch) >> 1) | 0x8000000000000000;
        return 1;
    } else {
        S >>= 1;
        return 0;
    }
}
int main(int argc, char **argv)
{
    typedef unsigned long long int	_uint64_t;
    int n;
    string path;
    string poli;
    string prov;
    prov.clear();
    int b;
    _uint64_t chislo=0;
    cout<<"Введите полином: ";
    cin>>poli;
    //cout<<poli<<endl;
    int len=poli.size();
    for(int i=0; i<=len; i++) {
        if (poli[i]=='^') {
            for(int k=1; poli[i+k]!='+'; k++) {
                prov=prov+poli[i+k];
            }
            b=atoi(prov.c_str());
            // cout<<b<<endl;
            _uint64_t x=pow(2,b-1);
            chislo=chislo+x;
            //cout<<chislo<<endl;
            prov.clear();
        }

    }
    cout<<chislo<<endl;
    cout<<hex<<chislo<<endl;
    ofstream fout;
    cout<<"Введите длину генирируемой последовательности: ";
    cin>>n;
    cout<<"Введите путь к файлу ";
    cin>>path;
    try {
        fout.open(path);
        if(!fout.is_open()) 
            throw 1;
    }
    catch(int a){
        cerr<<"Неверный путь к файлу"<<endl;
        return a;
    }
    for(int i=0; i<n; i++)
                fout<<LFSR_Galois(chislo);
            fout.close();
       
    return 0;
}
