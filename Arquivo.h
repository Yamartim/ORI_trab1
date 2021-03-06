/*
Arquivo.h

    Daniel Kenichi Tiago Tateishi RA: 790837
    João Dini de Miranda RA: 790716
    Martim Fernandes Ribeiro Lima RA: 756187
*/
#ifndef ARQUIVO_H
#define ARQUIVO_H
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Registro.h"

using std::string;

#define KEY 4
#define LASTNAME 16
#define FIRSTNAME 16
#define ADDRESS 32
#define LOGRADOURO 20
#define COMPLEMENTO 10
#define CITY 20
#define STATE 2
#define ZIP 4
#define PHONE 6

class Arquivo
{
private:
    string path;    //caminho do arquivo
    string pathindice;
    string tipo;      //tipo do arquiv, b = binario, t = texto

    //Registro regs[];

public:

    Arquivo();
    
    //setters
    void setPaths(string p, string p_indice, char t);

    //getters
    string getPath();
    string getTipo();
    string getIndicePath();

    virtual Registro buscaKey(int key) = 0;
    virtual Registro buscaNome(string nome) = 0;

    virtual bool escreverReg(Registro* reg) = 0;
    virtual bool removerReg(int key) = 0;
    virtual bool atualizaIndice(int key, std::string nome) = 0;



};

class ArquivoFIX: public Arquivo
{
private:
    int numRegistros;
    int offset_reg; 
    int* offset_cam;
    char separadorIndice;
    char removedorLogico;
public:
    ArquivoFIX(string p, string p_indice, char t);

    //setters
    void setOffset();

    //getters
    int getOffsetReg();
    Registro buscaKey(int key);
    Registro buscaNome(string nome);

    void ajustaCampo(Registro* reg);
    bool escreverReg(Registro* reg);
    bool removerReg(int key);
    bool atualizaIndice(int key, std::string nome);

    Registro buscaNumReg(int n);

};

class ArquivoVAR: public Arquivo
{
private:
    char separador_reg;
    char separador_cam;
    char removedorLogico;
    int extra;

public:
    ArquivoVAR(string p, string p_indice, char t);

    //setters
    void setSeparadores(char sepCam, char sepReg);

    Registro buscaKey(int key);
    Registro buscaNome(string nome);

    bool escreverReg(Registro* reg);
    bool removerReg(int key);
    bool atualizaIndice(int key, std::string nome);

};
#endif