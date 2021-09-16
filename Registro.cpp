#include <stdio.h>
#include <iostream>
#include "Registro.h"

using std::cout;
using std::endl;

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