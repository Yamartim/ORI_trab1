#include <string>
#include "Registro.h"

using std::string;


class Arquivo
{
private:
    string path;    //caminho do arquivo
    char tipo;      //tipo do arquiv, b = binario, t = texto
    int offset;     //
    //Registro regs[];

public:

    Arquivo(string p, char t);

    Registro buscaKey(int key);
    Registro buscaNome(string nome);


};
