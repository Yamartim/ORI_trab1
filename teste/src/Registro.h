#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>

using std::string;

class Registro
{

protected:

    int key;

    string lastname;
    string firstname;

    struct Address{
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
ADDRESS (i.e., endereço com logradouro, número e complemento) (32 bytes) (20, 10, 2)
CITY (i.e., cidade) (20 bytes)
STATE (i.e., sigla do estado com 2 caracteres, tal como SP) (2 bytes)
ZIP (i.e., CEP, tal como 222222-222) (4 bytes)
PHONE (i.e., número do telefone com DDD, tal como (022)2222-2222) (6 bytes)
*/


public:
    Registro();
    Registro(int k, string ln, string fn, string al, int an, string ac, string ci, string st, int zc, int pd, int pn);

    void print();

    // Set
    bool SetKey(int k);
    virtual bool SetLastName(string ln);
    virtual bool SetFirstName(string fn);
    //Endereço
    virtual bool SetLogradouro(string al);
    bool SetANumero(int an);
    virtual bool SetComplemento(string ac);
    // -- 

    virtual bool SetCity(string ci);
    virtual bool SetState(string st);
    bool SetZipcode(int zc);
    
    //phone
    bool SetDDD(int pd);
    bool SetPNumero(int pn);
    // -- 
    // Get
    int GetKey();
    string GetLastName();
    string GetFirstName();
    string GetLogradouro();
    int GetANumero();
    string GetComplemento();
    string GetCity();
    string GetState();
    int GetZipcode();
    int GetDDD();
    int GetPNumero();

};

class RegistroFIX: public Registro
{
    // Set
    bool SetKey(int k);
    bool SetLastName(string ln);
    bool SetFirstName(string fn);
    //Endereço
    bool SetLogradouro(string al);
    bool SetANumero(int an);
    bool SetComplemento(string ac);
    // -- 

    bool SetCity(string ci);
    bool SetState(string st);
    bool SetZipcode(int zc);
    
    //phone
    bool SetDDD(int pd);
    bool SetPNumero(int pn);
};

#endif