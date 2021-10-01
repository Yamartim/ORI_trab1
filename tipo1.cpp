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
    int intaux;
    string straux;

    cout << "Iniciando gravação. Digite 0 para parar" << endl;
    do{
        cout << "KEY: ";
        cin >> intaux; 
    }while(!inRegistro.SetKey(intaux));
    do{
        cout << "First Name: ";
        cin >> straux; 
    }while(!inRegistro.SetFirstName(straux));
    do{
        cout << "Last Name: ";
        cin >> intaux; 
    }while(!inRegistro.SetLastName(straux));

    cout << "Sobre o endereço," << endl;
    do{
        cout << "Logradouro: ";
        cin >> intaux; 
    }while(!inRegistro.SetLogradouro(straux));
    do{
        cout << "Número: ";
        cin >> intaux; 
    }while(!inRegistro.SetANumero(intaux));
    do{
        cout << "Complemento: ";
        cin >> intaux; 
    }while(!inRegistro.SetComplemento(straux));
    do{
        cout << "Cidade: ";
        cin >> intaux; 
    }while(!inRegistro.SetCity(straux));
    do{
        cout << "Estado (Código de 2 letras): ";
        cin >> intaux; 
    }while(!inRegistro.SetState(straux));
    do{
        cout << "Zipcode/CEP: ";
        cin >> intaux; 
    }while(!inRegistro.SetZipcode(intaux));

    cout << "Sobre o celular," << endl;
    do{
        cout << "DDD: ";
        cin >> intaux; 
    }while(!inRegistro.SetDDD(intaux));
    do{
        cout << "Número: ";
        cin >> intaux; 
    }while(!inRegistro.SetPNumero(intaux));

    // gravarDados(&inRegistro);
    //cout << " gravado com sucesso" << endl;
    //cout << " Continuar? (S/N)";
    //TODO Loop S/N
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