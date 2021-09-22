#include <string>
#include "Registro.h"

using std::string;


class Arquivo
{
private:
    string path;    //caminho do arquivo
    string pathindice;
    char tipo;      //tipo do arquiv, b = binario, t = texto

    //Registro regs[];

public:

    Arquivo(string p, char t);

    virtual Registro buscaKey(int key);
    virtual Registro buscaNome(string nome);

    virtual void escreverReg(Registro reg);


};

class ArquivoFIX: public Arquivo
{
private:
    int offset;

public:
    Registro buscaNumReg(int n);

};

class ArquivoVAR: public Arquivo
{

};