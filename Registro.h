#ifndef REGISTRO_H
#define REGISTRO_H

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
Total(100 bytes offset)
KEY (i.e., número que identifica a pessoa) (4 bytes)
LASTNAME (i.e., sobrenome da pessoa) (16 bytes)
FIRSTNAME (i.e., primeiro nome da pessoa) (16 bytes)
ADDRESS (i.e., endereço com logradouro, número e complemento) (32 bytes)
CITY (i.e., cidade) (20 bytes)
STATE (i.e., sigla do estado com 2 caracteres, tal como SP) (2 bytes)
ZIP (i.e., CEP, tal como 222222-222) (4 bytes)
PHONE (i.e., número do telefone com DDD, tal como (022)2222-2222) (6 bytes)
*/


public:
    Registro();
    Registro(int k, string ln, string fn, string al, int an, string ac, string ci, string st, int zc, int pd, int pn);

    void print();

};

#endif