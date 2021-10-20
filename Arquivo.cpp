/*
Arquivo.cpp

    Daniel Kenichi Tiago Tateishi RA: 790837
    João Dini de Miranda RA: 790716
    Martim Fernandes Ribeiro Lima RA: 756187
*/
#include "Arquivo.h"
#include "Registro.h"
#include <exception>

using std::cout;
using std::endl;

/**Construtor de arquivo geral**/
Arquivo::Arquivo(){}
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
std::string Arquivo::getIndicePath(){
    return this->pathindice;
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
    separadorIndice = '|';
    removedorLogico = '*';
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
    aux = reg->GetFirstName();
    reg->SetFirstName(aux.append((16 - reg->GetFirstName().length()), '#'));
    
    aux = reg->GetLastName();
    reg->SetLastName(aux.append((16 - reg->GetLastName().length()), '#'));

    aux = reg->GetLogradouro();
    reg->SetLogradouro(aux.append((20 - reg->GetLogradouro().length()), '#'));

    aux = reg->GetComplemento();
    reg->SetComplemento(aux.append((10 - reg->GetComplemento().length()), '#'));

    aux = reg->GetCity();
    reg->SetCity(aux.append((20 - reg->GetCity().length()), '#'));

    aux = reg->GetState();
    reg->SetState(aux.append((2 - reg->GetState().length()), '#'));
}

bool ArquivoFIX::escreverReg(Registro *reg){
    std::fstream arq;
    std::fstream arqIndice; 
    char c; 
    char nome[FIRSTNAME];
    int pos;
    int intAux;
    int auxKey;
    short int shortIntAux;
    bool existe = false;

    //convertendo de string para char*
    int tam = getPath().length();
    char* path = new char[tam + 1];
    strcpy(path, getPath().c_str());

    tam = getIndicePath().length();
    char* pathIndice = new char[tam + 1];
    strcpy(pathIndice, getIndicePath().c_str());
    
    ajustaCampo(reg);

    arq.open(path, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
    arqIndice.open(pathIndice, std::ios_base::in | std::ios_base::out | std::ios_base::binary);

    //caso falhe em abrir o arquivo
    if(!arq.is_open()){
        //criando arquivo caso ele nao exista
        arq.open(path,std::ios_base::out | std::ios_base::binary);
        cout << "Criando arquivo novo" << endl;
        if(!arq.is_open()){
            cout << "Erro: Nao foi possivel abrir o arquivo" << endl;
            return false;
        }    
    }

    if(!arqIndice.is_open()){
        //criando arquivo caso ele nao exista
        arqIndice.open(pathIndice, std::ios_base::out | std::ios_base::binary);
        cout << "Criando arquivo novo" << endl;
        if(!arqIndice.is_open()){
            cout << "Erro: Nao foi possivel abrir o arquivo" << endl;
            return false;
        }
    }

    //garantindo que os ponteiros de leitura e escrita começam no começo do arquivo
    arq.seekg(0, std::ios::beg);
    arq.seekp(0, std::ios::beg);
    arqIndice.seekg(0, std::ios::beg);
    arqIndice.seekp(0, std::ios::beg);

    arq.get(c);

    //verificando por remoçoes logicas
    while(c != '*' && !arq.eof()){
        arq.clear();
        arq.seekg(-1 , std::ios::cur);
        arq.read((char*)&auxKey, sizeof(auxKey));
        if(auxKey == reg->GetKey())
            existe = true;
        arq.seekg(getOffsetReg() - sizeof(int), std::ios::cur);
        arq.get(c);
    } 
    arq.clear();
    
    if(existe){
        cout << "Registro com chave ja existente!" << endl;
        arq.close();
        arqIndice.close();
        return false;
    }

    if(c == '*')
        arq.seekg(-1, std::ios::cur);

    strcpy(nome, reg->GetFirstName().c_str());
    pos = arq.tellp();
     
    arqIndice.get(c);
    //verificando por remoçoes logicas no arquivo de indices
    while(c != '*' && !arqIndice.eof()){
        arqIndice.clear();
        arqIndice.seekg(-1 , std::ios::cur);
        arqIndice.seekg(FIRSTNAME , std::ios::cur);
        arqIndice.seekg(sizeof(int) , std::ios::cur);
        arqIndice.get(c);
    } 
   
    //escrevendo no arquivo de indice
    arqIndice.clear();
    if(c == '*'){   
        arqIndice.seekp(-1 , std::ios::cur);
        arqIndice << nome;
        arqIndice.write((char*)&pos, sizeof(pos));
    }
    else{
        arqIndice << nome;
        arqIndice.write((char*)&pos, sizeof(int));
    }
    //extraindo campos da classe registro e escrevendo no arquivo
    intAux = reg->GetKey(); //key
    arq.write((char*)&intAux, sizeof(intAux));
    arq << reg->GetFirstName().c_str(); //fname
    arq << reg->GetLastName().c_str(); //lname
    arq << reg->GetLogradouro().c_str();//logradouro           
    shortIntAux = reg->GetANumero(); //anumero
    arq.write((char*)&shortIntAux, sizeof(shortIntAux));
    arq << reg->GetComplemento().c_str(); //complemento
    arq << reg->GetCity().c_str(); //city
    arq << reg->GetState().c_str(); //state
    intAux = reg->GetZipcode();//zip
    arq.write((char*)&intAux, sizeof(intAux));
    shortIntAux = reg->GetDDD();//ddd
    arq.write((char*)&shortIntAux, sizeof(shortIntAux));
    intAux = reg->GetPNumero();//pnumero
    arq.write((char*)&intAux, sizeof(intAux));
    
    arq.close();
    arqIndice.close();

    return true;
}

Registro ArquivoFIX::buscaKey(int key) {
    std:: ifstream arq;
    Registro auxReg;
    Registro regVazio;
    int auxKey;
    int i;

    //convertendo de string para char
    int tam = getPath().length();
    char* path = new char[tam + 1];
    strcpy(path, getPath().c_str());

    arq.open(path, std::ios::in | std::ios::binary);

    //caso falhe em abrir o arquivo
    if(!arq.is_open()){
        cout << "Erro: Nao foi possivel abrir o arquivo" << endl;
        return regVazio; //retorna registro vazio, tratar na main esse retorno
    }

    //garantindo que os ponteiros de leitura e escrita começam no começo do arquivo
    arq.seekg(0, std::ios::beg);

    arq.read((char*)&auxKey, sizeof(auxKey));
    
    while(auxKey != key && !arq.eof()){
        arq.clear();
        arq.seekg(-sizeof(auxKey), std::ios::cur);
        arq.seekg(getOffsetReg(), std::ios::cur);

        if(!arq.eof()){
            arq.clear();
            arq.read((char*)&auxKey, sizeof(auxKey));
        }
    }          

    //caso achou, atribui retorna o registro do arquivo
    if(auxKey == key){
        char firstName[FIRSTNAME];
        char lastName[LASTNAME];
        char logradouro[LOGRADOURO];
        char complemento[COMPLEMENTO];
        short int aNumero;
        char city[CITY];
        char state[STATE];
        int zipCode;
        short int ddd;
        int pNumero;
        std::string converter;

        //lendo do arquivo para colocar no registro auxiliar de retorno
        arq.read(firstName, sizeof(firstName));
        arq.read(lastName, sizeof(lastName));
        arq.read(logradouro, sizeof(logradouro));
        arq.read((char*)&aNumero, sizeof(aNumero));
        arq.read(complemento, sizeof(complemento));
        arq.read(city, sizeof(city));
        arq.read(state, sizeof(state));
        arq.read((char*)&zipCode, sizeof(zipCode));
        arq.read((char*)&ddd, sizeof(ddd));
        arq.read((char*)&pNumero, sizeof(pNumero));
 
        auxReg.SetKey(auxKey);

        for(i = 0; i < FIRSTNAME && firstName[i] != '#'; i++){
            converter += firstName[i];
        }
        auxReg.SetFirstName(converter);

        converter.clear();
        for(i = 0; i < LASTNAME && lastName[i] != '#'; i++){
            converter += lastName[i];
        }
        auxReg.SetLastName(converter);

        converter.clear();
        for(i = 0; i < LOGRADOURO && logradouro[i] != '#'; i++){
            converter += logradouro[i];
        }
        auxReg.SetLogradouro(converter);

        auxReg.SetANumero(aNumero);

        converter.clear();
        for(i = 0; i < COMPLEMENTO && complemento[i] != '#'; i++){
            converter += complemento[i];
        }
        auxReg.SetComplemento(converter);

        converter.clear();
        for(i = 0; i < CITY && city[i] != '#'; i++){
            converter += city[i];
        }
        auxReg.SetCity(converter);

        converter.clear();
        for(i = 0; i < STATE && state[i] != '#'; i++){
            converter += state[i];
        }
        auxReg.SetState(converter);

        auxReg.SetZipcode(zipCode);
        auxReg.SetDDD(ddd);
        auxReg.SetPNumero(pNumero);

        arq.close();     
        return auxReg;
    }
    arq.close();
    return regVazio;    
 }

Registro ArquivoFIX::buscaNome(std::string nome){  
    std::fstream arq;
    std::fstream arqIndice; 
    Registro auxReg;
    Registro regVazio;
    std::string auxStr;
    char auxArray[FIRSTNAME];
    bool achou = false;
    int offset;
    int i;

    //convertendo de string para char*
    int tam = getPath().length();
    char* path = new char[tam + 1];
    strcpy(path, getPath().c_str());

    tam = getIndicePath().length();
    char* pathIndice = new char[tam + 1];
    strcpy(pathIndice, getIndicePath().c_str());

    arq.open(path, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
    arqIndice.open(pathIndice, std::ios_base::in | std::ios_base::binary);

    if(!arq.is_open()){
        cout << "Erro: Nao foi possivel abrir o arquivo" << endl;
        return regVazio; //retorna registro vazio, tratar na main esse retorno
    }

    if(!arqIndice.is_open()){
        cout << "Erro: Nao foi possivel abrir o arquivo" << endl;
        return regVazio; //retorna registro vazio, tratar na main esse retorno
    }

    //buscando pelo nome no arquivo de indices
    arqIndice.read(auxArray, sizeof(auxArray));
    while(!arqIndice.eof() && !achou){
        auxStr.clear();
        for(int i = 0; i < FIRSTNAME && auxArray[i] != '#'; i++){
            auxStr += auxArray[i];
        } 
        if(auxStr == nome)
            achou = true;
        else{
            arqIndice.seekg(sizeof(int), std::ios::cur);
            arqIndice.read(auxArray, sizeof(auxArray));
        }
    }   
    
    //caso nao tenha encontrado o nome, retorna o registro vazio
    if(!achou){
        arq.close();
        arqIndice.close();
        return regVazio;
    }

    //else
    arqIndice.read((char*)&offset, sizeof(int));

    arq.seekg(offset, std::ios::beg);

    int auxKey;
    char firstName[FIRSTNAME];
    char lastName[LASTNAME];
    char logradouro[LOGRADOURO];
    char complemento[COMPLEMENTO];
    short int aNumero;
    char city[CITY];
    char state[STATE];
    int zipCode;
    short int ddd;
    int pNumero;
    std::string converter;

    //lendo do arquivo para colocar no registro auxiliar de retorno
    arq.read((char*)&auxKey, sizeof(auxKey));
    arq.read(firstName, sizeof(firstName));
    arq.read(lastName, sizeof(lastName));
    arq.read(logradouro, sizeof(logradouro));
    arq.read((char*)&aNumero, sizeof(aNumero));
    arq.read(complemento, sizeof(complemento));
    arq.read(city, sizeof(city));
    arq.read(state, sizeof(state));
    arq.read((char*)&zipCode, sizeof(zipCode));
    arq.read((char*)&ddd, sizeof(ddd));
    arq.read((char*)&pNumero, sizeof(pNumero));

    auxReg.SetKey(auxKey);

    for(i = 0; i < FIRSTNAME && firstName[i] != '#'; i++){
        converter += firstName[i];
    }
    auxReg.SetFirstName(converter);

    converter.clear();
    for(i = 0; i < LASTNAME && lastName[i] != '#'; i++){
        converter += lastName[i];
    }
    auxReg.SetLastName(converter);

    converter.clear();
    for(i = 0; i < LOGRADOURO && logradouro[i] != '#'; i++){
        converter += logradouro[i];
    }
    auxReg.SetLogradouro(converter);

    auxReg.SetANumero(aNumero);

    converter.clear();
    for(i = 0; i < COMPLEMENTO && complemento[i] != '#'; i++){
        converter += complemento[i];
    }
    auxReg.SetComplemento(converter);

    converter.clear();
    for(i = 0; i < CITY && city[i] != '#'; i++){
        converter += city[i];
    }
    auxReg.SetCity(converter);

    converter.clear();
    for(i = 0; i < STATE && state[i] != '#'; i++){
        converter += state[i];
    }
    auxReg.SetState(converter);

    auxReg.SetZipcode(zipCode);
    auxReg.SetDDD(ddd);
    auxReg.SetPNumero(pNumero);

    arq.close();
    arqIndice.close();
    return auxReg;     
}

bool ArquivoFIX::removerReg(int key){
    std::fstream arq;
    int auxKey;
    char nome[FIRSTNAME];
    std::string auxStr;
    //convertendo de string para char*
    int tam = getPath().length();
    char* path = new char[tam + 1];
    strcpy(path, getPath().c_str());

    arq.open(path, std::ios_base::in | std::ios_base::out | std::ios_base::binary);

    if(!arq.is_open()){
        cout << "Erro: Nao foi possivel abrir o arquivo" << endl;
        return false; //retorna false caso falhe em abrir o arquivo
    }

    //garantindo que os ponteiros de leitura e escrita começam no começo do arquivo
    arq.seekg(0, std::ios::beg);
    arq.seekp(0, std::ios::beg);

    arq.read((char*)&auxKey, sizeof(auxKey));

    while(auxKey != key && !arq.eof()){
        arq.clear();
        arq.seekg(-sizeof(auxKey), std::ios::cur);
        arq.seekg(getOffsetReg(), std::ios::cur);

        if(!arq.eof()){
            arq.clear();
            arq.read((char*)&auxKey, sizeof(auxKey));
        }
    }
    
    if(auxKey != key){
        arq.close();
        return false;
    }
    //fazendo a remoçao logica
    arq.read(nome, sizeof(nome));

    for(int i = 0; (i < FIRSTNAME) && (nome[i] != '#'); i++){
        auxStr += nome[i];
    }    
    arq.seekg(-sizeof(nome), std::ios::cur);
    arq.seekg(-sizeof(auxKey), std::ios::cur);
    arq.write(&removedorLogico, sizeof(char));
    atualizaIndice(key, auxStr);

    arq.close();
    return true;
}

bool ArquivoFIX::atualizaIndice(int key, std::string nome){
    std::fstream arqIndice; 
    char auxArray[FIRSTNAME];
    bool achou;
    std::string auxStr;
    //int auxKey;

    int tam = getIndicePath().length();
    char* pathIndice = new char[tam + 1];
    strcpy(pathIndice, getIndicePath().c_str());

    arqIndice.open(pathIndice, std::ios_base::in | std::ios_base::out | std::ios_base::binary);

    if(!arqIndice.is_open()){
        cout << "Erro: Nao foi possivel abrir o arquivo" << endl;
        return false; //retorna false caso falhe em abrir o arquivo
    }
    //buscando pelo nome no arquivo de indices
    arqIndice.read(auxArray, sizeof(auxArray));

    while(!arqIndice.eof() && !achou){
        auxStr.clear();
        for(int i = 0; i < FIRSTNAME && auxArray[i] != '#'; i++){
            auxStr += auxArray[i];
        } 
        if(auxStr == nome)
            achou = true;
        else{
            arqIndice.seekg(sizeof(int), std::ios::cur);
            arqIndice.read(auxArray, sizeof(auxArray));
        }
    }   
    
    //caso nao tenha encontrado o nome, retorna false
    if(!achou){
        arqIndice.close();
        return false;
    }
    //else
    //fazendo a remoçao logica
    arqIndice.seekg(-sizeof(auxArray), std::ios::cur);
    arqIndice.write(&removedorLogico, sizeof(char));

    arqIndice.close();
    return true;
}

Registro ArquivoFIX::buscaNumReg(int n){
    std::fstream arq;
    Registro auxReg;
    Registro regVazio;
    int i;
    char c;
    //convertendo de string para char
    int tam = getPath().length();
    char* path = new char[tam + 1];
    strcpy(path, getPath().c_str());

    arq.open(path, std::ios_base::in | std::ios_base::out |std::ios_base::binary);
    
    //caso falhe em abrir o arquivo
    if(!arq.is_open()){
        cout << "Erro: Nao foi possivel abrir o arquivo" << endl;
        return regVazio; //retorna registro vazio, tratar na main esse retorno
    }
    arq.seekg((n-1) * getOffsetReg(), std::ios::beg);
    arq.get(c); 
    if(!arq.eof()){
        arq.clear();
        arq.seekg(-1, std::ios::cur);
        int auxKey;
        char firstName[FIRSTNAME];
        char lastName[LASTNAME];
        char logradouro[LOGRADOURO];
        char complemento[COMPLEMENTO];
        short int aNumero;
        char city[CITY];
        char state[STATE];
        int zipCode;
        short int ddd;
        int pNumero;
        std::string converter;

        //lendo do arquivo para colocar no registro auxiliar de retorno
        arq.read((char*)&auxKey, sizeof(auxKey));
        arq.read(firstName, sizeof(firstName));
        arq.read(lastName, sizeof(lastName));
        arq.read(logradouro, sizeof(logradouro));
        arq.read((char*)&aNumero, sizeof(aNumero));
        arq.read(complemento, sizeof(complemento));
        arq.read(city, sizeof(city));
        arq.read(state, sizeof(state));
        arq.read((char*)&zipCode, sizeof(zipCode));
        arq.read((char*)&ddd, sizeof(ddd));
        arq.read((char*)&pNumero, sizeof(pNumero));

        auxReg.SetKey(auxKey);

        for(i = 0; i < FIRSTNAME && firstName[i] != '#'; i++){
            converter += firstName[i];
        }
        auxReg.SetFirstName(converter);

        converter.clear();
        for(i = 0; i < LASTNAME && lastName[i] != '#'; i++){
            converter += lastName[i];
        }
        auxReg.SetLastName(converter);

        converter.clear();
        for(i = 0; i < LOGRADOURO && logradouro[i] != '#'; i++){
            converter += logradouro[i];
        }
        auxReg.SetLogradouro(converter);

        auxReg.SetANumero(aNumero);

        converter.clear();
        for(i = 0; i < COMPLEMENTO && complemento[i] != '#'; i++){
            converter += complemento[i];
        }
        auxReg.SetComplemento(converter);

        converter.clear();
        for(i = 0; i < CITY && city[i] != '#'; i++){
            converter += city[i];
        }
        auxReg.SetCity(converter);

        converter.clear();
        for(i = 0; i < STATE && state[i] != '#'; i++){
            converter += state[i];
        }
        auxReg.SetState(converter);

        auxReg.SetZipcode(zipCode);
        auxReg.SetDDD(ddd);
        auxReg.SetPNumero(pNumero);

        arq.close();
        return auxReg;
    }
    arq.close();
    return regVazio;
}

/**ArquivoVAR**/
//construtor 
 ArquivoVAR::ArquivoVAR(std::string p, std::string p_indice, char t){
    setPaths(p, p_indice, t);
    setSeparadores('|', '#');
    extra = 44;
}

//setter dos separadores de campo e registro
void ArquivoVAR::setSeparadores(char sepCam, char sepReg){
    separador_cam = sepCam;
    separador_reg = sepReg;
}

//Escreve os dados de um registro no arquivo
/*TRATAR CASOS DE REGISTRS REMOVIDOS LOGICAMENTE*/
bool ArquivoVAR::escreverReg(Registro* reg){
    std::fstream arq; 
    std::fstream arqIndice;
    int registerSize;
    int intAux;
    int pos;
    short int shortIntAux;
    char c;

    //convertendo de string para char*
    int tam = getPath().length();
    char* path = new char[tam + 1];
    strcpy(path, getPath().c_str());

    tam = getIndicePath().length();
    char* pathIndice = new char[tam + 1];
    strcpy(pathIndice, getIndicePath().c_str());
    
    arq.open(path, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
    arqIndice.open(pathIndice, std::ios_base::in | std::ios_base::out | std::ios_base::binary);

    //caso falhe em abrir o arquivo
    if(!arq.is_open()){
        //criando arquivo caso ele nao exista
        arq.open(path,std::ios_base::out | std::ios_base::binary);
        cout << "Criando arquivo novo" << endl;
        if(!arq.is_open()){
            cout << "Erro: Nao foi possivel abrir o arquivo" << endl;
            return false;
        }    
    }

    if(!arqIndice.is_open()){
        //criando arquivo caso ele nao exista
        arqIndice.open(pathIndice, std::ios_base::out | std::ios_base::binary);
        cout << "Criando arquivo novo" << endl;
        if(!arqIndice.is_open()){
            cout << "Erro: Nao foi possivel abrir o arquivo" << endl;
            return false;
        }
    }
    //garantindo que os ponteiros de leitura e escrita começam no começo do arquivo
    arq.seekg(0, std::ios::beg);
    arq.seekp(0, std::ios::beg);
    arqIndice.seekg(0, std::ios::beg);
    arqIndice.seekp(0, std::ios::beg);

    arq.get(c);

    while(c != '~' && !arq.eof()){
        arq.clear();
        arq.get(c);
    }
    arq.clear();

    pos = arq.tellp();

    while(c != '~' && !arqIndice.eof()){
        arqIndice.clear();
        arqIndice.get(c);
    }
    arqIndice.clear();
    //escrevendo no arquivo de indices
    intAux = reg->GetFirstName().length();
    arqIndice.write((char*)&intAux, sizeof(intAux));
    arqIndice << reg->GetFirstName().c_str();
    arqIndice.write((char*)&pos, sizeof(pos));

    registerSize = 0;
    registerSize += sizeof(reg->GetKey());
    registerSize += reg->GetFirstName().length();
    registerSize += reg->GetLastName().length();
    registerSize += reg->GetLogradouro().length();
    registerSize += sizeof(reg->GetANumero());
    registerSize += reg->GetComplemento().length();
    registerSize += reg->GetCity().length();
    registerSize += reg->GetState().length();
    registerSize += sizeof(reg->GetZipcode());
    registerSize += sizeof(reg->GetDDD());
    registerSize += sizeof(reg->GetPNumero());

    //escrevendo no arquivo 44 bytes de indicadores de tamanho , 45 se considerar o indicador de fim de registro

    arq.write((char*)&registerSize, sizeof(registerSize)); 

    intAux = sizeof(reg->GetKey());
    arq.write((char*)&intAux, sizeof(intAux)); 
    intAux = reg->GetKey();
    arq.write((char*)&intAux, sizeof(intAux)); 
    //arq << separador_cam;

    intAux = reg->GetFirstName().length();
    arq.write((char*)&intAux, sizeof(intAux)); 
    arq << reg->GetFirstName().c_str();

    intAux = reg->GetLastName().length();
    arq.write((char*)&intAux, sizeof(intAux));
    arq << reg->GetLastName().c_str();

    intAux = reg->GetLogradouro().length();
    arq.write((char*)&intAux, sizeof(intAux)); 
    arq << reg->GetLogradouro().c_str();  

    intAux = sizeof(reg->GetANumero());
    arq.write((char*)&intAux, sizeof(intAux)); 
    shortIntAux = reg->GetANumero();
    arq.write((char*)&shortIntAux, sizeof(shortIntAux)); 
    //arq << separador_cam;

    intAux = reg->GetComplemento().length();
    arq.write((char*)&intAux, sizeof(intAux)); 
    arq << reg->GetComplemento().c_str();

    intAux = reg->GetCity().length();
    arq.write((char*)&intAux, sizeof(intAux)); 
    arq << reg->GetCity().c_str();

    intAux = reg->GetState().length();
    arq.write((char*)&intAux, sizeof(intAux)); 
    arq << reg->GetState().c_str();

    intAux = sizeof(reg->GetZipcode());
    arq.write((char*)&intAux, sizeof(intAux)); 
    intAux = reg->GetZipcode();
    arq.write((char*)&intAux, sizeof(intAux)); 
    //arq << separador_cam;

    intAux = sizeof(reg->GetDDD());
    arq.write((char*)&intAux, sizeof(intAux)); 
    shortIntAux = reg->GetDDD();
    arq.write((char*)&shortIntAux, sizeof(shortIntAux)); 
    //arq << separador_cam;

    intAux = sizeof(reg->GetPNumero());
    arq.write((char*)&intAux, sizeof(intAux)); 
    intAux = reg->GetPNumero();
    arq.write((char*)&intAux, sizeof(intAux)); 
    //arq << separador_cam;

    arq << separador_reg;
    
    arq.close();
    return true;
}

Registro ArquivoVAR::buscaKey(int key){
    std:: ifstream arq;
    Registro auxReg;
    Registro regVazio;
    int registerSize;
    int auxKey;
    int fieldSize;
    char c;
    int i;

    //convertendo de string para char
    int tam = getPath().length();
    char* path = new char[tam + 1];
    strcpy(path, getPath().c_str());

    arq.open(path, std::ios::in | std::ios::binary);

    //caso falhe em abrir o arquivo
    if(!arq.is_open()){
        cout << "Erro: Nao foi possivel abrir o arquivo" << endl;
        return regVazio; //retorna registro vazio, tratar na main esse retorno
    }

    //garantindo que os ponteiros de leitura e escrita começam no começo do arquivo
    arq.seekg(0, std::ios::beg);
    arq.read((char*)&registerSize, sizeof(registerSize));
    arq.read((char*)&fieldSize, sizeof(fieldSize));
    arq.read((char*)&auxKey, sizeof(auxKey));

    while(auxKey != key && !arq.eof()){
        arq.clear();
        arq.seekg(-(fieldSize + sizeof(fieldSize)), std::ios::cur);
        arq.seekg(registerSize + extra, std::ios::cur);
        arq.get(c);
        if(c == '#'){
            arq.read((char*)&registerSize, sizeof(registerSize));
            arq.read((char*)&fieldSize, sizeof(fieldSize));
            arq.read((char*)&auxKey, sizeof(auxKey));
        }
        else{
            std::cout << "Erro na leitura do registro em Busca Key" << std::endl;
        }
    }
    arq.clear();
    //caso achou, atribui retorna o registro do arquivo
    if(auxKey == key){
        char* firstName;
        char* lastName;
        char* logradouro;
        char* complemento;
        short int aNumero;
        char* city;
        char* state;
        int zipCode;
        short int ddd;
        int pNumero;
        std::string converter;
        //lendo do arquivo para colocar no registro auxiliar de retorno
        //key
        auxReg.SetKey(auxKey);

        //firstname
        arq.read((char*)&fieldSize, sizeof(fieldSize));
        firstName = new char[fieldSize];
        arq.read(firstName, fieldSize);
        for(i = 0; i < fieldSize; i++){
            converter += firstName[i];
        }
        auxReg.SetFirstName(converter);
        delete firstName;
        converter.clear();

        //lastname
        arq.read((char*)&fieldSize, sizeof(fieldSize));
        lastName = new char[fieldSize];
        arq.read(lastName, fieldSize);
        for(i = 0; i < fieldSize; i++){
            converter += lastName[i];
        }
        auxReg.SetLastName(converter);
        delete lastName;
        converter.clear();

        //logradouro
        arq.read((char*)&fieldSize, sizeof(fieldSize));
        logradouro = new char[fieldSize];
        arq.read(logradouro, fieldSize);
        for(i = 0; i < fieldSize; i++){
            converter += logradouro[i];
        }
        auxReg.SetLogradouro(converter);
        delete logradouro;
        converter.clear();

        //aNumero
        arq.read((char*)&fieldSize, sizeof(fieldSize));
        arq.read((char*)&aNumero, sizeof(aNumero));
        auxReg.SetANumero(aNumero);

        //complemento
        arq.read((char*)&fieldSize, sizeof(fieldSize));
        complemento = new char[fieldSize];
        arq.read(complemento, fieldSize);
        for(i = 0; i < fieldSize; i++){
            converter += complemento[i];
        }
        auxReg.SetComplemento(converter);
        delete complemento;
        converter.clear();
        
        //city
        arq.read((char*)&fieldSize, sizeof(fieldSize));
        city = new char[fieldSize];
        arq.read(city, fieldSize);
        for(i = 0; i < fieldSize; i++){
            converter += city[i];
        }
        auxReg.SetCity(converter);
        delete city;
        converter.clear();

        //state
        arq.read((char*)&fieldSize, sizeof(fieldSize));
        state = new char[fieldSize];
        arq.read(state, fieldSize);
        for(i = 0; i < fieldSize; i++){
            converter += state[i];
        }
        auxReg.SetState(converter);
        delete state;
        converter.clear();

        //Zipcode
        arq.read((char*)&fieldSize, sizeof(fieldSize));
        arq.read((char*)&zipCode, sizeof(zipCode));
        auxReg.SetZipcode(zipCode);
        
        //DDD
        arq.read((char*)&fieldSize, sizeof(fieldSize));
        arq.read((char*)&ddd, sizeof(ddd));
        auxReg.SetDDD(ddd);
        
        //pNumero
        arq.read((char*)&fieldSize, sizeof(fieldSize));
        arq.read((char*)&pNumero, sizeof(pNumero));
        auxReg.SetPNumero(pNumero);

        arq.close();     
        return auxReg;
    }  
    arq.close();
    return regVazio;
}

Registro ArquivoVAR::buscaNome(std::string nome){
    std::fstream arq;
    std::fstream arqIndice;
    Registro auxReg;
    Registro regVazio;
    std::string auxStr;
    int nameSize;
    int offset;
    int i;
    bool achou;
    char* auxArray;

    //convertendo de string para char*
    int tam = getPath().length();
    char* path = new char[tam + 1];
    strcpy(path, getPath().c_str());

    tam = getIndicePath().length();
    char* pathIndice = new char[tam + 1];
    strcpy(pathIndice, getIndicePath().c_str());

    arq.open(path, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
    arqIndice.open(pathIndice, std::ios_base::in | std::ios_base::binary);

    if(!arq.is_open()){
        cout << "Erro: Nao foi possivel abrir o arquivo" << endl;
        return regVazio; //retorna registro vazio, tratar na main esse retorno
    }

    if(!arqIndice.is_open()){
        cout << "Erro: Nao foi possivel abrir o arquivo" << endl;
        return regVazio; //retorna registro vazio, tratar na main esse retorno
    }
    
    arqIndice.read((char*)&nameSize, sizeof(nameSize));
    auxArray = new char[nameSize];
    arqIndice.read(auxArray, nameSize);

    while(!achou && !arqIndice.eof()){
        auxStr.clear();
        for(i = 0; i  < nameSize; i++){
            auxStr += auxArray[i];
        }
        if(auxStr == nome){
            achou = true;
        }
        else{
            delete auxArray;
            arqIndice.seekg(sizeof(int), std::ios::cur);
            arqIndice.read((char*)&nameSize, sizeof(nameSize));
            auxArray = new char[nameSize];
            arqIndice.read(auxArray, nameSize);
        }
    }
    if(!achou){
        arq.close();
        arqIndice.close();
        return regVazio;
    }
    //else
    arqIndice.read((char*)&offset, sizeof(offset));

    int registerSize;
    int auxKey;
    int fieldSize;
    char* firstName;
    char* lastName;
    char* logradouro;
    char* complemento;
    short int aNumero;
    char* city;
    char* state;
    int zipCode;
    short int ddd;
    int pNumero;
    std::string converter;

    arq.seekg(offset, std::ios::beg);
    //lendo do arquivo para colocar no registro auxiliar de retorno
    //key
    arq.read((char*)&registerSize, sizeof(registerSize));
    arq.read((char*)&fieldSize, sizeof(fieldSize));
    arq.read((char*)&auxKey, sizeof(auxKey));
    auxReg.SetKey(auxKey);

    //firstname
    arq.read((char*)&fieldSize, sizeof(fieldSize));
    firstName = new char[fieldSize];
    arq.read(firstName, fieldSize);
    for(i = 0; i < fieldSize; i++){
        converter += firstName[i];
    }
    auxReg.SetFirstName(converter);
    delete firstName;
    converter.clear();

    //lastname
    arq.read((char*)&fieldSize, sizeof(fieldSize));
    lastName = new char[fieldSize];
    arq.read(lastName, fieldSize);
    for(i = 0; i < fieldSize; i++){
        converter += lastName[i];
    }
    auxReg.SetLastName(converter);
    delete lastName;
    converter.clear();

    //logradouro
    arq.read((char*)&fieldSize, sizeof(fieldSize));
    logradouro = new char[fieldSize];
    arq.read(logradouro, fieldSize);
    for(i = 0; i < fieldSize; i++){
        converter += logradouro[i];
    }
    auxReg.SetLogradouro(converter);
    delete logradouro;
    converter.clear();

    //aNumero
    arq.read((char*)&fieldSize, sizeof(fieldSize));
    arq.read((char*)&aNumero, sizeof(aNumero));
    auxReg.SetANumero(aNumero);

    //complemento
    arq.read((char*)&fieldSize, sizeof(fieldSize));
    complemento = new char[fieldSize];
    arq.read(complemento, fieldSize);
    for(i = 0; i < fieldSize; i++){
        converter += complemento[i];
    }
    auxReg.SetComplemento(converter);
    delete complemento;
    converter.clear();
    
    //city
    arq.read((char*)&fieldSize, sizeof(fieldSize));
    city = new char[fieldSize];
    arq.read(city, fieldSize);
    for(i = 0; i < fieldSize; i++){
        converter += city[i];
    }
    auxReg.SetCity(converter);
    delete city;
    converter.clear();

    //state
    arq.read((char*)&fieldSize, sizeof(fieldSize));
    state = new char[fieldSize];
    arq.read(state, fieldSize);
    for(i = 0; i < fieldSize; i++){
        converter += state[i];
    }
    auxReg.SetState(converter);
    delete state;
    converter.clear();

    //Zipcode
    arq.read((char*)&fieldSize, sizeof(fieldSize));
    arq.read((char*)&zipCode, sizeof(zipCode));
    auxReg.SetZipcode(zipCode);
    
    //DDD
    arq.read((char*)&fieldSize, sizeof(fieldSize));
    arq.read((char*)&ddd, sizeof(ddd));
    auxReg.SetDDD(ddd);
    
    //pNumero
    arq.read((char*)&fieldSize, sizeof(fieldSize));
    arq.read((char*)&pNumero, sizeof(pNumero));
    auxReg.SetPNumero(pNumero);

    arq.close(); 
    arqIndice.close();    
    return auxReg;
}

bool ArquivoVAR::removerReg(int key){
    return true;
}
bool ArquivoVAR::atualizaIndice(int key, std::string nome){
    return true;
}
