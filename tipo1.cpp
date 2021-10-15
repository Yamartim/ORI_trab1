#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <locale>

#include "Arquivo.h"
#include "Registro.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

int inputOperacao(){
    //Exibe opÁıes
    cout << '\n';
    cout << "Escolha a operaÁ„o desejada:" << '\n';
    cout << "(0) - Para sair" << '\n';
    cout << "(1) - GravaÁ„o de Dados" << '\n';
    cout << "(2) - Visualizar registros" << '\n';
    //cout << "(3) - Recuperar registro por n˙mero" << '\n';
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

        cout << "Iniciando gravaÁ„o." << endl;
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

        cout << "Sobre o endereÁo," << endl;
        do{
            cout << "Logradouro: ";
            getline(cin, straux);
        }while(!inRegistro.SetLogradouro(straux));
        do{
            cout << "N˙mero: ";
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
            cout << "Estado (CÛdigo de 2 letras): ";
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
            cout << "N˙mero: ";
            cin >> intaux; 
            cin.ignore();
        }while(!inRegistro.SetPNumero(intaux));

        //DEBUG
        cout << "\n\nImprimindo valores do registro";
        inRegistro.print();

        if(arq->escreverReg(&inRegistro)){
            cout << " gravado com sucesso" << endl;
        }
        else cout << "Erro" << endl;
        cout << "\nContinuar? (S/N)" << endl;
        cin >> straux;

    }while(straux == "S" || straux == "s");
}

// Loop de "browsing" do arquivo
void visualizar(Arquivo *arq){
    Registro regAux;
    string aux;
    string nome;
    //int key;
    int i = 0;
    //cout << "Digite a chave do registro em que deseja visualizar os dados" << endl;
    //cin >> key;

    cout << "Digite o nome do registro em que deseja visualizar os dados" << endl;
    cin >> nome;

    //regAux = arq->buscaKey(key);
    regAux = arq->buscaNome(nome);
    do{
        i++;
        cout << "== Exibindo registro " << i << " ==" << '\n';
        // Usar fun√ß√£o de leitura sequencial para colocar o registro i no regAux

        cout << " Chave: " << regAux.GetKey() << '\n';
        cout << " First Name: " << regAux.GetFirstName() << '\n';
        cout << " Last Name: " << regAux.GetLastName() << '\n'; 
        cout << "\n";
        cout << " EndereÁo" << '\n';
        cout << " Logradouro: " << regAux.GetLogradouro() << '\n';
        cout << " N˙mero: " << regAux.GetANumero() << '\n';
        cout << " Complemento: " << regAux.GetComplemento() << '\n';
        cout << " Cidade: " << regAux.GetCity() << '\n';
        cout << " Estado: " << regAux.GetState() << '\n';
        cout << " ZIP: " << regAux.GetZipcode() << '\n';
        cout << " Telefone: " << regAux.GetPNumero() << '\n';
        cout << " Digite enter para continuar, ou 0 para parar" << endl;
        std::getline(cin, aux);
    }while(aux.length() != 0); // Se digitar algo sair do loop
}

int main(int argc, char const *argv[])
{
    //Criando objeto de Arquivo
    ArquivoFIX arquivoFix("arquivo.dat", "indices.bin", 't');
    setlocale(LC_ALL, "Portuguese");
    // Loop principal do programa
    // Input(Operacao) -> Loop da operacao Secund√°rio -> Input(sair) -> Sa√≠da

    bool sair = false;
    while(!sair){
        // Apresenta op√ß√µes na tela, retorna opera√ß√£o
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
                cout << "N„o reconhecido" << endl;
            break;
        }
    }

    return 0;
}