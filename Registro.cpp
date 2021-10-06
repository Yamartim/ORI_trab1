#include <stdio.h>
#include <iostream>
#include <string>
#include "Registro.h"

using std::cout;
using std::endl;

Registro::Registro(){
    key = 0;

    lastname = "";
    firstname = "";

    address.logradouro = "";
    address.numero = 0;
    address.complemento = "";

    city = "";
    state = "";

    zipcode = 0;

    phone.ddd = 0;
    phone.numero = 0;
}

Registro::Registro(int k, std::string ln, std::string fn, std::string al, int an, std::string ac, std::string ci, std::string st, int zc, int pd, int pn)
{
    //Set(Requisitado) ? : Senão Set(Padrão)
    SetKey(k) ? : SetKey(0);

    SetFirstName(fn) ? : SetFirstName("");
    SetLastName(ln) ? : SetLastName("");

    SetLogradouro(al) ? : SetLogradouro("");
    SetANumero(an) ? : SetANumero(0);
    SetComplemento(ac) ? : SetComplemento("");

    SetCity(ci) ? : SetCity("");
    SetState(st) ? : SetState("NA");

    SetZipcode(zc) ? : SetZipcode(0);

    SetDDD(pd) ? : SetDDD(0);
    SetPNumero(pn) ? : SetPNumero(0);
}

void Registro::print()
{
    cout << endl;
    cout << "REGISTRO-------------------" << endl << endl;
    cout << "- chave: " << key << endl;
    cout << "- nome: " << firstname << " " << lastname << endl;
    cout << "- endereço: " << address.logradouro << ", num " << address.numero << ", " << address.complemento << endl;
    cout << "- cidade: " << city << " no estado de " << state << endl;
    cout << "- cep: " << zipcode/1000 << "-" << zipcode%1000 << endl;
    cout << "- telefone: (" << phone.ddd << ") " << phone.numero/10000 << "-" << phone.numero%10000 << endl;
    cout << "--------------------------" << endl << endl;

}

// Sets
//! Talvez faltem algumas verificações aqui
bool Registro::SetKey(int k){
    if(k >= 0){
        key = k;
        return 1;
    }
    return 0;
}

bool Registro::SetLastName(std::string ln){
    lastname = ln;
    return 1;
}

bool Registro::SetFirstName(std::string fn){
    firstname = fn;
    return 1;
}

bool Registro::SetLogradouro(std::string al){
    address.logradouro = al;
    return 1;
}

bool Registro::SetANumero(int an){
    address.numero = an;
    return 1;
}

bool Registro::SetComplemento(std::string ac){
    address.complemento = ac;
    return 1;
}

bool Registro::SetCity(std::string ci){
    city = ci;
    return 1;
}

bool Registro::SetState(std::string st){
    if(st.length() == 2){
        state = st;
        return 1;
    }
    return 0;
}

bool Registro::SetZipcode(int zc){
    if(zc >= 0){
        zipcode = zc;
        return 1;
    }
    return 0;
}

bool Registro::SetDDD(int pd){
    if(pd >= 0){
        phone.ddd = pd;
        return 1;
    }
    return 0;
}

bool Registro::SetPNumero(int pn){
    if(pn >= 0){
        phone.numero = pn;
        return 1;
    }
    return 0;
}

// Get
int Registro::GetKey(){
    return this->key;
}

std::string Registro::GetLastName(){
    return this->lastname;
}

std::string Registro::GetFirstName(){
    return this->firstname;
}

std::string Registro::GetLogradouro(){
    return this->address.logradouro;
}

int Registro::GetANumero(){
    return this->address.numero;
}

std::string Registro::GetComplemento(){
    return this->address.complemento;
}

std::string Registro::GetCity(){
    return this->city;
}

std::string Registro::GetState(){
    return this->state;
}

int Registro::GetZipcode(){
    return this->zipcode;
}

int Registro::GetDDD(){
    return this->phone.ddd;
}

int Registro::GetPNumero(){
    return this->phone.numero;
}
//TODO