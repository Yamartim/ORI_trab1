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

Registro::Registro(int k, string ln, string fn, string al, int an, string ac, string ci, string st, int zc, int pd, int pn)
{
    key = k;

    lastname = ln;
    firstname = fn;

    address.logradouro = al;
    address.numero = an;
    address.complemento = ac;

    city = ci;
    state = st;

    zipcode = zc;

    phone.ddd = pd;
    phone.numero = pn;

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

bool Registro::SetLastName(string ln){
    lastname = ln;
    return 1;
}

bool Registro::SetFirstName(string fn){
    firstname = fn;
    return 1;
}

bool Registro::SetLogradouro(string al){
    address.logradouro = al;
    return 1;
}

bool Registro::SetANumero(int an){
    address.numero = an;
    return 1;
}

bool Registro::SetComplemento(string ac){
    address.complemento = ac;
    return 1;
}

bool Registro::SetCity(string ci){
    city = ci;
    return 1;
}

bool Registro::SetState(string st){
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
//TODO