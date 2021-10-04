#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

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
    do{
        //cin.ignore() usado para ignorar /n que seria absorvido pelo getline()

        cout << "Iniciando gravação." << endl;
        do{
            cout << "KEY: ";
            cin >> intaux; 
            cin.ignore();
        }while(!inRegistro.SetKey(intaux));
        do{
            cout << "First Name: ";
            getline(cin, straux);
        }while(!inRegistro.SetFirstName(straux));
        do{
            cout << "Last Name: ";
            getline(cin, straux); 
        }while(!inRegistro.SetLastName(straux));

        cout << "Sobre o endereço," << endl;
        do{
            cout << "Logradouro: ";
            getline(cin, straux);
        }while(!inRegistro.SetLogradouro(straux));
        do{
            cout << "Número: ";
            cin >> intaux; 
            cin.ignore();
        }while(!inRegistro.SetANumero(intaux));
        do{
            cout << "Complemento: ";
            getline(cin, straux);
        }while(!inRegistro.SetComplemento(straux));
        do{
            cout << "Cidade: ";
            getline(cin, straux);
        }while(!inRegistro.SetCity(straux));
        do{
            cout << "Estado (Código de 2 letras): ";
            cin >> straux; 
        }while(!inRegistro.SetState(straux));
        do{
            cout << "Zipcode/CEP: ";
            cin >> intaux; 
            cin.ignore();
        }while(!inRegistro.SetZipcode(intaux));

        cout << "Sobre o celular," << endl;
        do{
            cout << "DDD: ";
            cin >> intaux; 
            cin.ignore();
        }while(!inRegistro.SetDDD(intaux));
        do{
            cout << "Número: ";
            cin >> intaux; 
            cin.ignore();
        }while(!inRegistro.SetPNumero(intaux));

        // gravarDados(&inRegistro);
        //cout << " gravado com sucesso" << endl;
        cout << "\nContinuar? (S/N)" << endl;
        cin >> straux;

    }while(straux == "S" || straux == "s");
}

int main(int argc, char const *argv[])
{
    //Criando objeto de Arquivo
    ArquivoFIX arquivoFix("arquivo.txt", "indices.txt", 't');
    
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
                inputGravarDados();
            break;
            //TODO Adicionar outros casos
            default:
                cout << "Não reconhecido" << endl;
            break;
        }
    }

    return 0;
}