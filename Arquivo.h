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

    virtual Registro buscaKey(int key) = 0;
    virtual Registro buscaNome(string nome) = 0;

    virtual void escreverReg(Registro reg) = 0;
    virtual void removerReg(Registro reg) = 0;
    virtual void atualizaIndice(Registro reg) = 0;



};

class ArquivoFIX: public Arquivo
{
private:
    int offset_reg;
    int offset_cam[];

public:
    ArquivoFIX(string p, char t);

    Registro buscaKey(int key);
    Registro buscaNome(string nome);

    void escreverReg(Registro reg);
    void removerReg(Registro reg);
    void atualizaIndice(Registro reg);

    Registro buscaNumReg(int n);

};

class ArquivoVAR: public Arquivo
{
private:
    char separador_reg;
    char separador_cam;

public:
    ArquivoVAR(string p, char t);

    
    Registro buscaKey(int key);
    Registro buscaNome(string nome);

    void escreverReg(Registro reg);
    void removerReg(Registro reg);
    void atualizaIndice(Registro reg);

};