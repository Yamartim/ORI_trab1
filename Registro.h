#include <string>

using std::string;

class Registro
{

private:

    int key;

    string lastname;
    string firstname;

    struct Address
    {
        string logradouro;
        int numero;
        string complemento;
    } address;
    
    string city;
    string state;
    
    int zipcode;
    
    struct Phone
    {
        int ddd;
        int numero;
    } phone;
    
/*
KEY (i.e., número que identifica a pessoa)
LASTNAME (i.e., sobrenome da pessoa)
FIRSTNAME (i.e., primeiro nome da pessoa)
ADDRESS (i.e., endereço com logradouro, número e complemento)
CITY (i.e., cidade)
STATE (i.e., sigla do estado com 2 caracteres, tal como SP)
ZIP (i.e., CEP, tal como 222222-222)
PHONE (i.e., número do telefone com DDD, tal como (022)2222-2222)
*/


public:

    Registro(int k, string ln, string fn, string al, int an, string ac, string ci, string st, int zc, int pd, int pn);

    void print();

};