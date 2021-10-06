#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "Arquivo.h"
#include "Registro.h"

using std::string;
using std::cout, std::cin, std::endl;

int inputOperacao(){
    //Exibe opções
    cout << '\n';
    cout << "Escolha a operação desejada:" << '\n';
    cout << "(0) - Para sair" << '\n';
    cout << "(1) - Gravação de Dados" << '\n';
    cout << "(2) - Visualizar registros" << '\n';
    //cout << "(3) - Recuperar registro por número" << '\n';
    //cout << "(4) - Recuperar registro por KEY" << '\n';
    //cout << "(5) - Recuperar registro por FIRSTNAME" << '\n';
    //cout << "(6) - Remover logicamente um registro" << '\n';
    
    cout << endl;

    //Recebe input
    int operacao;
    cin >> operacao;
    return operacao;
}

// Loop de input dos dados de pessoas
void inputGravarDados(Arquivo *arq){
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

        arq->escreverReg(inRegistro);
        cout << " gravado com sucesso" << endl;
        cout << "\nContinuar? (S/N)" << endl;
        cin >> straux;

    }while(straux == "S" || straux == "s");
}

// Loop de "browsing" do arquivo
void visualizar(Arquivo *arq){
    Registro regAux;
    string aux;
    int i = 0;
    do{
        i++;
        cout << "== Exibindo registro " << i << " ==" << '\n';
        // Usar função de leitura sequencial para colocar o registro i no regAux

        cout << " Chave: " << regAux.GetKey() << '\n';
        cout << " First Name: " << regAux.GetKey() << '\n';
        cout << " Last Name: " << regAux.GetKey() << '\n';

        cout << "\n";
        cout << "Endereço" << '\n';
        cout << " Logradouro: " << regAux.GetKey() << '\n';
        cout << " Número: " << regAux.GetKey() << '\n';
        cout << " Complemento: " << regAux.GetKey() << '\n';
        cout << " Cidade: " << regAux.GetKey() << '\n';
        cout << " Estado: " << regAux.GetKey() << '\n';
        cout << " ZIP: " << regAux.GetKey() << '\n';
        cout << " Telefone: " << regAux.GetKey() << '\n';
        cout << "Digite enter para continuar, ou 0 para parar" << endl;
        std::getline(cin, aux);
    }while(aux.length() != 0); // Se digitar algo sair do loop
}

int main(int argc, char const *argv[])
{
    //Criando objeto de Arquivo
    ArquivoFIX arquivoFix("arquivo", "indices", 't');
    
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
                inputGravarDados(&arquivoFix);
            break;
            case 2:
                visualizar(&arquivoFix);
            break;
            //TODO Adicionar outros casos
            default:
                cout << "Não reconhecido" << endl;
            break;
        }
    }

    return 0;
}