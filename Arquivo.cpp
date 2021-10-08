#include "Arquivo.h"
#include "Registro.h"

using std::cout;
using std::endl;


/**Construtor de arquivo geral**/
Arquivo::Arquivo(){
    
}
//setter dos paths do arquivo
void Arquivo::setPaths(std::string p, std::string p_indice, char t){
    path = p;
    pathindice = p_indice;
    tipo = t;
}

//getter do path do arquivo
std::string Arquivo::getPath(){
    return this->path;
}

std::string Arquivo::getTipo(){
    return this->tipo;
}

/**ArquivoFIX**/
ArquivoFIX::ArquivoFIX(std::string p, std::string p_indice, char t){
    setPaths(p, p_indice, t);
    setOffset();
}

//getter

int ArquivoFIX::getOffsetReg(){
    return this->offset_reg;
}

//setter
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
/*Ajusta os campos para escrita no registro de tamanho fixo*/
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
void ArquivoFIX::ajustaCampo(Registro* reg){
    std::string aux;
    while(reg->GetLastName().length() < 16){
        aux = reg->GetLastName();
        reg->SetLastName(aux.append("#"));
    }
    while(reg->GetFirstName().length() < 16){
        aux = reg->GetFirstName();
        reg->SetFirstName(aux.append("#"));
    }
    while(reg->GetLogradouro().length() < 20){
        aux = reg->GetLogradouro();
        reg->SetLogradouro(aux.append("#"));
    }   
    while(reg->GetComplemento().length() < 10){
        aux = reg->GetComplemento();
        reg->SetComplemento(aux.append("#"));
    }
    while(reg->GetCity().length() < 20){
        aux = reg->GetCity();
        reg->SetCity(aux.append("#"));
    }
    while(reg->GetState().length() < 2){
        aux = reg->GetState();
        reg->SetState(aux.append("#"));
    }
}

bool ArquivoFIX::escreverReg(Registro *reg){
    std::fstream arq;//arquivo para leitura e escrita
    char c; //variavel para receber os caracteres 1 a 1 do arquivo
    //convertendo de string para char*
    std::string aux = getPath();
    int tam = aux.length();
    char* path = new char[tam + 1];
    strcpy(path, aux.c_str());
    
    ajustaCampo(reg);

    //criando arquivo caso ele nao exista
    arq.open(path,std::ios_base::out | std::ios_base::binary);
    arq.close();

    //std::fstream arq(path, std::ios_base::binary|std::ios_base::out|std::ios_base::in);
    arq.open(path, std::ios_base::in | std::ios_base::out | std::ios_base::binary);

    //caso falhe em abrir o arquivo
    if(!arq.is_open()){
        cout << "Erro: Nao foi possivel abrir o arquivo" << endl;
        return false;
    }

    //garantindo que os ponteiros de leitura e escrita começam no começo do arquivo
    arq.seekg(0, std::ios::beg);
    arq.seekp(0, std::ios::beg);

    /*------DEBUG--------*/
    int pos;

    pos = arq.tellg();
    std::cout << "Posicao do pointer get " << pos << endl;
    pos = arq.tellp();
    std::cout << "Posicao do pointer put " << pos << endl;

    /*--------------*/
    arq.get(c);

    //verificando por remoçoes logicas
    while(c != '*' && !arq.eof()){
        arq.clear();
        arq.seekg(getOffsetReg() , std::ios::cur);
        arq.seekp(getOffsetReg() , std::ios::cur);
        arq.get(c);
    }

    arq.clear();
    
    arq.write((char*)&reg, sizeof(Registro));

    arq.close();

    return true;
}

 Registro ArquivoFIX::buscaKey(int key) {
    std:: ifstream arq;
    std::string aux = getPath();
    Registro auxReg;
    Registro regVazio;
    //int keyValue;
    //bool achou = false;

    //convertendo de string para char
    int tam = aux.length();
    char* path = new char[tam + 1];
    strcpy(path, aux.c_str());

    arq.open(path, std::ios::in | std::ios::binary);

    //caso falhe em abrir o arquivo
    if(!arq.is_open()){
        cout << "Erro: Nao foi possivel abrir o arquivo" << endl;
        return regVazio; //retorna registro vazio, tratar na main esse retorno
    }
    /*------DEBUG--------*/
    int pos;
    pos = arq.tellg();
    std::cout << "Posicao do pointer get antes " << pos << endl;
    /*--------------*/

    //garantindo que os ponteiros de leitura e escrita começam no começo do arquivo
    arq.seekg(0, std::ios::beg);

    /*------DEBUG--------*/
    pos = arq.tellg();
    std::cout << "Posicao do pointer get depois " << pos << endl;
    /*--------------*/

     /*----DEBUG-------*/
    bool fimArquivo = arq.eof();
    std::cout<<"Arquivo vazio? " << fimArquivo << endl;
    /*------------*/

    //procurando registro com a chave especificada no arquivo
    //arq.read((char*)&keyValue, sizeof(int));    
    arq.read((char*)&auxReg, sizeof(Registro));
    while((auxReg.GetKey() != key) && !arq.eof()){
        arq.clear();
        arq.seekg(getOffsetReg(), std::ios::cur);
        if(!arq.eof())
            arq.read((char*)&auxReg, sizeof(Registro));
        arq.clear();
    }
    arq.close();

    //caso achou, atribui retorna o registro do arquivo
    if(auxReg.GetKey() == key){
        return auxReg;
    }
    
    return regVazio;    
 }


Registro ArquivoFIX::buscaNome(std::string nome){
    Registro auxReg;
    //to do
    return auxReg;     
}

bool ArquivoFIX::removerReg(Registro reg){return false;}
bool ArquivoFIX::atualizaIndice(Registro reg){return false;}

Registro ArquivoFIX::buscaNumReg(int n){
    Registro auxReg;
    return auxReg;
}


/**ArquivoVAR**/
/*
//construtor 
 ArquivoVAR::ArquivoVAR(std::string p, std::string p_indice, char t){
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

    std::ofstream arq; 
    std::string aux = getPath();
    
    int tam = aux.length();
    char* path = new char[tam + 1];
    strcpy(path, aux.c_str());

    arq.open(path, std::ios::out | std::ios::trunc);    

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

    FILE *arq;
    std::string aux = getPath();
    std::string aux2 = getTipo();

    //conversao de std::string para char*
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

Registro ArquivoVAR::buscaKey(int key){

    FILE *arq;
    std::string aux = getPath();
    std::string aux2 = getTipo();
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


Registro Arquivo::buscaNome(std::string nome){
    Registro auxReg;
    // to do
    return auxReg; 
 }*/

