#include <iostream>
#include <string>
#include <fstream>

#include "Arquivo.h"
#include "Registro.h"

using std::string;
using std::cout, std::cin, std::endl;

// Arquivo como variável global
std::ofstream arquivo;

int inputOperacao(){
    //Exibe opções
    cout << endl;
    cout << "Escolha a operação desejada:" << endl;
    cout << "(0) - Para sair" << endl;
    cout << "(1) - Gravação de Dados" << endl;
    //cout << "(2) - Visualizar registros" << endl;
    //cout << "(3) - Recuperar registro por número" << endl;
    //cout << "(4) - Recuperar registro por KEY" << endl;
    //cout << "(5) - Recuperar registro por FIRSTNAME" << endl;
    //cout << "(6) - Remover logicamente um registro" << endl;

    // Acho que isso já estaria incluso na inserção
    //cout << "(7) - Inserir novos registros" << endl;
    
    cout << endl;

    //Recebe input
    int operacao;
    cin >> operacao;
    return operacao;
}

// Loop de input dos dados de pessoas
void inputGravarDados(){
    Registro inRegistro;

    cout << "Iniciando gravação. Digite 0 para parar" << endl;
    cout << "KEY: ";
    //? Usar sets de Registro para depois chamar (?)
    //? gravarDados(), passando o registro para inserir no arquivo
}

int main(int argc, char const *argv[])
{
    // Abrindo Arquivo
    
    arquivo.open("arquivo.txt");

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

    // Loop principal do programa
    // Input(Operacao) -> Loop da operacao Secundário -> Input(sair) -> Saída
    
    bool sair = false;
    while(!sair){
        // Apresenta opções na tela, retorna operação
        switch(inputOperacao())
        {
            case 0:
                cout << "Saindo do programa" << endl;
                sair = true;
            break;
            case 1:
                cout << "1 escolhido" << endl;
                inputGravarDados();
            break;
            //TODO Adicionar outros casos
            default:
                cout << "Não reconhecido" << endl;
            break;
        }
    }

    arquivo.close();

    return 0;
}