#include <string>
#include "Registro.h"

using std::string;

#define KEY 4
#define LASTNAME 16
#define FIRSTNAME 16
#define ADDRESS 32
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

    virtual Registro buscaKey(int key) = 0;
    virtual Registro buscaNome(string nome) = 0;

    virtual bool escreverReg(Registro reg) = 0;
    virtual bool removerReg(Registro reg) = 0;
    virtual bool atualizaIndice(Registro reg) = 0;



};

class ArquivoFIX: public Arquivo
{
private:
    int offset_reg; 
    int* offset_cam;
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
    ArquivoFIX(string p, string p_indice, char t);

    //setters
    void setOffset();

    //getters

    Registro buscaKey(int key);
    Registro buscaNome(string nome);

    bool escreverReg(Registro reg);
    bool removerReg(Registro reg);
    bool atualizaIndice(Registro reg);

    Registro buscaNumReg(int n);

};

class ArquivoVAR: public Arquivo
{
private:
    char separador_reg;
    char separador_cam;

public:
    ArquivoVAR(string p, string p_indice, char t);

    //setters
    void setSeparadores(char sepCam, char sepReg);

    Registro buscaKey(int key);
    Registro buscaNome(string nome);

    bool escreverReg(Registro reg);
    bool removerReg(Registro reg);
    bool atualizaIndice(Registro reg);

};