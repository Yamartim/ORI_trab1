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
    /**Possibilidade com fwrite se for permitido gravar o objeto direto no arquivo binario**/
    FILE *arq;
    
    std::string aux = getPath();
    std::string aux2 = getTipo();

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
     /**Leitura se for permitido gravar o objeto inteiro em binario, ainda nao implementei da outra forma**/
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


/*Registro ArquivoFIX::buscaNome(std::string nome){
    Registro auxReg;
    //to do
    return auxReg;     
}*/



/**ArquivoVAR**/

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
    /**Tentativa de escrever individualmente cada campo direto no arquivo sem fwrite 
      (se for fazer assim a assinatura da funcao volta a ser void)**/

    std::ofstream arq; /**Meu editor de texto indicava erro aqui por isso tentei reescrever usando fwrite e ai surgiu a duvida que mandei no grupo**/ 
    std::string aux = getPath();
    
    int tam = aux.length();
    char* path = new char[tam + 1];
    strcpy(path, aux.c_str());

    arq.open(path, std::ios::out | std::ios::trunc );    

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

    return true;

    /**Possibilidade com fwrite se for permitido gravar o objeto direto no arquivo binario**
    /*FILE *arq;
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

    return true;*/
}

Registro ArquivoVAR::buscaKey(int key){
    /**Leitura se for permitido gravar o objeto inteiro em binario, ainda nao implementei da outra forma**/
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


/*Registro Arquivo::buscaNome(std::string nome){
    Registro auxReg;
    // to do
    return auxReg; 
 }*/

