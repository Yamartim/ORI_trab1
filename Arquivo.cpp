#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Arquivo.h"
#include "Registro.h"

using std::cout;
using std::endl;

/**Construtor de arquivo geral**/
Arquivo::Arquivo(){
    
}
//setter dos paths do arquivo
void Arquivo::setPaths(string p, string p_indice, char t){
    this->path = p;
    this->pathindice = p_indice;
    this->tipo = t;
}

//getter do path do arquivo
string Arquivo::getPath(){
    return this->path;
}

/**ArquivoFIX**/



ArquivoFIX::ArquivoFIX(string p, string p_indice, char t){
    setPaths(p, p_indice, t);
    setOffset();
}

void ArquivoFIX::escreverReg(Registro reg){
   //// Exemplo de escrita no arquivo
    // string buffer;
    // while(1){
    //     std::cin >> buffer;
    //     if(buffer != "0"){
    //         arquivo << buffer << std::endl;
    //     }else{
    //         break;
    //     }
    // }
   
    ofstream arq; /**fica indicando erro pra vcs no ofstream?**/
    
    arq.open(getPath());

    //escreve no arquivo fixo


    arq.close();
}

// Registro ArquivoFIX::buscaKey(int key)
// {

// }


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
    this->separador_cam = sepCam;
    this->separador_reg = sepReg;
}

//Escreve os dados de um registro no arquivo
void ArquivoVAR::escreverReg(Registro reg){
    //// Exemplo de escrita no arquivo
    // string buffer;
    // while(1){
    //     std::cin >> buffer;
    //     if(buffer != "0"){
    //         arquivo << buffer << std::endl;
    //     }else{
    //         break;
    //     }
    // }
   
    ofstream arq;
    arq.open(getPath());

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
}

// Registro ArquivoVAR::buscaKey(int key)
// {
    
// }


// Registro Arquivo::buscaNome(string nome)
// {
    
// }

