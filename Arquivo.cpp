#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "Arquivo.h"
#include "Registro.h"

using std::cout;
using std::endl;

/**Construtor de arquivo geral**/
Arquivo::Arquivo(){
    
}
//setter dos paths do arquivo
void Arquivo::setPaths(string p, string p_indice, char t){
    path = p;
    pathindice = p_indice;
    tipo = t;
}

//getter do path do arquivo
string Arquivo::getPath(){
    return this->path;
}

string Arquivo::getTipo(){
    return this->tipo;
}

/**ArquivoFIX**/
ArquivoFIX::ArquivoFIX(string p, string p_indice, char t){
    setPaths(p, p_indice, t);
    setOffset();
}

void ArquivoFIX::setOffset(){
    offset_reg = 100;
    offset_cam = new int[7];

    offset_cam[0] = KEY;
    offset_cam[1] = LASTNAME;
    offset_cam[2] = FIRSTNAME;
    offset_cam[3] = ADDRESS;
    offset_cam[4] = CITY;
    offset_cam[5] = STATE;
    offset_cam[6] = ZIP;
    offset_cam[7] = PHONE;

}

bool ArquivoFIX::escreverReg(Registro reg){
    FILE *arq;
    
    string aux = getPath();
    string aux2 = getTipo();

    int tam = aux.length();
    char* path = new char[tam + 1];
    strcpy(path, aux.c_str());

    tam = aux2.length();
    char* type = new char[tam + 1];
    strcpy(type, aux2.c_str());
    
    arq = fopen(path, type);

    if(arq == NULL){
        puts("Erro: Nao foi possivel abrir o arquivo");
        return false;
    }

    if(fwrite(&reg, sizeof(reg), 1, arq) != 1){
        puts("Erro: Nao foi possivel escrever o registro no arquivo");
        return false;
    }

    fclose(arq);

    puts("Registro gravado com sucesso");

    return true;
   
}

 Registro ArquivoFIX::buscaKey(int key) {
    FILE *arq;
    string aux = getPath();
    string aux2 = getTipo();
    Registro auxReg;

    int tam = aux.length();
    char* path = new char[tam + 1];
    strcpy(path, aux.c_str());

    tam = aux2.length();
    char* type = new char[tam + 1];
    strcpy(type, aux2.c_str());
    
    arq = fopen(path, type);
    if(arq == NULL){
        puts("Erro: Nao foi possivel abrir o arquivo");
        return auxReg;
    }

    while (!feof(arq) && (auxReg.GetKey() != key)){
        fread(&auxReg, sizeof(Registro), 1, arq);
    }

    fclose(arq);

    return auxReg;
 }


// Registro ArquivoFIX::buscaNome(string nome)
// {
    
// }




/**ArquivoVAR**/

//construtor 
 ArquivoVAR::ArquivoVAR(string p, string p_indice, char t){
    setPaths(p, p_indice, t);
    setSeparadores('|', '#');
}

//setter dos separadores de campo e registro
void ArquivoVAR::setSeparadores(char sepCam, char sepReg){
    separador_cam = sepCam;
    separador_reg = sepReg;
}

//Escreve os dados de um registro no arquivo
bool ArquivoVAR::escreverReg(Registro reg){
    /**Tentativa de escrever individualmente cada campo direto no arquivo sem fwrite**/

    ofstream arq; /**Meu editor de texto indicava erro aqui por isso tentei reescrever usando fwrite e ai surgiu a duvida que mandei no grupo**/ 
    string aux = getPath();
    
    int tam = aux.length();
    char* path = new char[tam + 1];
    strcpy(path, aux.c_str());

    arq.open(path, ios::out | ios::trunc );    

    arq << reg.GetKey() << separador_cam;
    arq << reg.GetLastName() << separador_cam;
    arq << reg.GetFirstName() << separador_cam;
    arq << reg.GetLogradouro() << separador_cam;              
    arq << reg.GetANumero() << separador_cam;
    arq << reg.GetComplemento() << separador_cam;
    arq << reg.GetCity() << separador_cam;
    arq << reg.GetState() << separador_cam;
    arq << reg.GetZipcode() << separador_cam;
    arq << reg.GetDDD() << separador_cam;
    arq << reg.GetPNumero() << separador_cam;
    arq << separador_reg;
    
    arq.close();

    /**Possibilidade com fwrite se for permitido gravar o objeto direto no arquivo binario**?
    /*FILE *arq;
    string aux = getPath();
    string aux2 = getTipo();

    //conversao de string para char*
    int tam = aux.length();
    char* path = new char[tam + 1];
    strcpy(path, aux.c_str());

    tam = aux2.length();
    char* type = new char[tam + 1];
    strcpy(type, aux2.c_str());
    
    arq = fopen(path, type);

    if(arq == NULL){
        puts("Erro: Nao foi possivel abrir o arquivo");
        return false;
    }

    if(fwrite(&reg, sizeof(reg), 1, arq) != 1){
        puts("Erro: Nao foi possivel escrever o registro no arquivo");
        return false;
    }

    fclose(arq);

    puts("Registro gravado com sucesso");

    return true;*/
}

Registro ArquivoVAR::buscaKey(int key){
    FILE *arq;
    string aux = getPath();
    string aux2 = getTipo();
    Registro auxReg;

    int tam = aux.length();
    char* path = new char[tam + 1];
    strcpy(path, aux.c_str());

    tam = aux2.length();
    char* type = new char[tam + 1];
    strcpy(type, aux2.c_str());
    
    arq = fopen(path, type);
    if(arq == NULL){
        puts("Erro: Nao foi possivel abrir o arquivo");
        return auxReg;
    }

    while (!feof(arq) && (auxReg.GetKey() != key)){
        fread(&auxReg, sizeof(Registro), 1, arq);
    }

    fclose(arq);

    return auxReg;
}


// Registro Arquivo::buscaNome(string nome)
// {
    
// }

