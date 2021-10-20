#include <stdio.h>
#include <iostream>
#include <iomanip>
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
    SetKey(k) ? true : SetKey(0);

    SetFirstName(fn) ? true : SetFirstName("");
    SetLastName(ln) ? true : SetLastName("");

    SetLogradouro(al) ? true : SetLogradouro("");
    SetANumero(an) ? true : SetANumero(0);
    SetComplemento(ac) ? true : SetComplemento("");

    SetCity(ci) ? true : SetCity("");
    SetState(st) ? true : SetState("NA");

    SetZipcode(zc) ? true : SetZipcode(0);

    SetDDD(pd) ? true : SetDDD(0);
    SetPNumero(pn) ? true : SetPNumero(0);
}

void Registro::print()
{
    cout << endl;
    cout << "REGISTRO-------------------" << endl;
    cout << "- chave: " << key << endl;
    cout << "- nome: " << firstname << " " << lastname << endl;
    cout << "- endereço: " << address.logradouro << ", num " << address.numero << ", " << address.complemento << endl;
    cout << "- cidade: " << city << " no estado de " << state << endl;
    cout << "- cep: " << std::setw(5) << std::setfill('0') << zipcode/1000 << "-" << std::setw(3) << zipcode%1000 << endl;
    cout << "- telefone: (" << phone.ddd << ") " << std::setw(5) << std::setfill('0') << phone.numero/10000 << "-" << std::setw(4) << phone.numero%10000 << endl;
    cout << "--------------------------" << endl << endl;

}

// Sets
//! Talvez faltem algumas verificações aqui -> Registro fixo ou variável?
bool Registro::SetKey(int k){
    if(k >= 0){
        key = k;
        return 1;
    }
    return 0;
}

bool Registro::SetLastName(std::string ln){
    if(ln.length() > 0){
        lastname = ln;
        return 1;
    }else{
        return 0;
    }
}

bool Registro::SetFirstName(std::string fn){
    if(fn.length() > 0){
        firstname = fn;
        return 1;
    }else{
        return 0;
    }
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

// Sets do Fixo (Restrições a mais no tamanho das strings)
bool RegistroFIX::SetLastName(std::string ln){
    if(ln.length() > 16){
        return 0;
    }
    lastname = ln;
    return 1;
}

bool RegistroFIX::SetFirstName(std::string fn){
    if(fn.length() > 16){
        return 0;
    }
    firstname = fn;
    return 1;
}

bool RegistroFIX::SetLogradouro(std::string al){
    if(al.length() > 20){
        return 0;
    }
    address.logradouro = al;
    return 1;
}

bool RegistroFIX::SetComplemento(std::string ac){
    if(ac.length() > 10){
        return 0;
    }
    address.complemento = ac;
    return 1;
}

bool RegistroFIX::SetCity(std::string ci){
    if(ci.length() > 16){
        return 0;
    }
    city = ci;
    return 1;
}

bool RegistroFIX::SetState(std::string st){
    if(st.length() == 2){
        state = st;
        return 1;
    }
    return 0;
}
