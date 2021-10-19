#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <locale>
#include <limits>

#include "Arquivo.h"
#include "Registro.h"

using std::string;
using std::cout;
using std::cin;
using std::endl; 

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Prompt de opera��o
int inputOperacao(){
    //Exibe op��es
    cout << '\n';
    cout << "Escolha a opera��o desejada:" << '\n';
    cout << "(0) - Para sair" << '\n';
    cout << "(1) - Grava��o de Dados" << '\n';
    cout << "(2) - Visualizar registros" << '\n';
    cout << "(3) - Recuperar registro por n�mero" << '\n';
    cout << "(4) - Recuperar registro por KEY" << '\n';
    cout << "(5) - Recuperar registro por FIRSTNAME" << '\n';
    cout << "(6) - Remover logicamente um registro" << '\n';
    
    cout << endl;

    //Recebe input
    int operacao;
    cin >> operacao;
    return operacao;
}

// Loop de input dos dados de pessoas
void inputGravarDados(ArquivoFIX *arq){
    Registro inRegistro;
    int intaux;
    string straux;
    do{
        //cin.ignore() usado para ignorar /n que seria absorvido pelo getline()

        cout << "Iniciando grava��o." << endl;
        do{
            cin.clear();
            ignoreLine();
            cout << "KEY: ";
            cin >> intaux; 
        }while(std::cin.fail() || !inRegistro.SetKey(intaux));
        do{
            ignoreLine();
            cout << "First Name: ";
            getline(cin, straux);
        }while(!inRegistro.SetFirstName(straux));
        do{
            ignoreLine();
            cout << "Last Name: ";
            getline(cin, straux); 
        }while(!inRegistro.SetLastName(straux));

        cout << "Sobre o endere�o," << endl;
        do{
            ignoreLine();
            cout << "Logradouro: ";
            getline(cin, straux);
        }while(!inRegistro.SetLogradouro(straux));
        do{
            cin.clear();
            ignoreLine();
            cout << "N�mero: ";
            cin >> intaux; 
        }while(std::cin.fail() || !inRegistro.SetANumero(intaux));
        do{
            ignoreLine();
            cout << "Complemento: ";
            getline(cin, straux);
        }while(!inRegistro.SetComplemento(straux));
        do{
            ignoreLine();
            cout << "Cidade: ";
            getline(cin, straux);
        }while(!inRegistro.SetCity(straux));
        do{
            ignoreLine();
            cout << "Estado (C�digo de 2 letras): ";
            cin >> straux; 
        }while(!inRegistro.SetState(straux));
        do{
            cin.clear();
            ignoreLine();
            cout << "Zipcode/CEP: ";
            cin >> intaux; 
        }while(std::cin.fail() || !inRegistro.SetZipcode(intaux));

        cout << "Sobre o celular," << endl;
        do{
            cin.clear();
            ignoreLine();
            cout << "DDD: ";
            cin >> intaux; 
        }while(std::cin.fail() || !inRegistro.SetDDD(intaux));
        do{
            cin.clear();
            ignoreLine();
            cout << "N�mero: ";
            cin >> intaux; 
        }while(std::cin.fail() || !inRegistro.SetPNumero(intaux));

        //DEBUG
        // cout << "\n\nImprimindo valores do registro";
        // inRegistro.print();

        if(arq->escreverReg(&inRegistro)){
            cout << " gravado com sucesso" << endl;
        }
        else cout << "Erro" << endl;

        ignoreLine();
        cout << endl << "Digite enter para continuar, ou 0 para parar" << endl;
        std::getline(cin, straux);

    }while(straux.length() == 0);
}

// Loop de "browsing" do arquivo
void visualizarSequencial(ArquivoFIX *arq){
    Registro regAux;
    string aux;
    int i = 1;
    regAux = arq->buscaNumReg(i);
    while(regAux.GetFirstName() != ""){
        cout << "Exibindo registro " << i << endl;
        regAux = arq->buscaNumReg(i);

        regAux.print();

        //cout << endl << "Digite enter para continuar, ou 0 para parar" << endl;
        //cin.ignore() <- Tire o coment�rio se por algum motivo entrar em um loop infinito aqui (N�o deveria entrar, avisar dini)
        //std::getline(cin, aux);
        i++;
     // Se digitar algo sair do loop
    }
}

// Recupera��o por n�mero
void visualizarNumero(ArquivoFIX *arq){
    Registro regAux;
    int num;
    cout << "Digite o n�mero que deseja visualizar: ";
    cin >> num;
    
    regAux = arq->buscaNumReg(num);

    regAux.print();
}

// Recupera��o por nome
void visualizarNome(ArquivoFIX *arq){
    Registro regAux;
    string aux;
    string nome;
    int i = 0;

    do{
        cout << "Digite o nome do registro em que deseja visualizar os dados" << endl;
        cin >> nome;
        regAux = arq->buscaNome(nome);
        cin.ignore();

        i++;
        cout << "== Exibindo registro " << i << " ==" << '\n';
        regAux.print();
        cout << endl << "Digite enter para continuar, ou 0 para parar" << endl;
        std::getline(cin, aux);
    }while(aux.length() == 0); // Se digitar algo sair do loop
}

// Recupera��o por chave
void visualizarKey(ArquivoFIX *arq){
    Registro regAux;
    string aux;
    int key;

    cout << "Digite a chave do registro em que deseja visualizar os dados" << endl;
    cin >> key;
    regAux = arq->buscaKey(key);

    regAux.print();
}

// Remo��o L�gica
void removerLogicamente(ArquivoFIX *arq){
    int key;
    string aux;
    do{
        cout << "Digite a chave do registro que deseja remover" << endl;
        cin >> key;
        cin.ignore();

        if(arq->removerReg(key)){
            cout << "Registro removido com sucesso" << endl;
        }else{
            cout << "Registro n�o encontrado" << endl;
        }

        cout << endl << "Digite enter para continuar, ou 0 para parar" << endl;
        std::getline(cin, aux);
    }while(aux.length() == 0);
    
}

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "Portuguese");

    //Criando objeto de Arquivo
    ArquivoFIX arquivoFix("arquivo.dat", "indices.bin", 't');

    bool sair = false;
    while(!sair){
        // Apresenta op��es na tela, retorna opera��o
        switch(inputOperacao())
        {
            case 0:
            // SAIR
                cout << "Saindo do programa" << endl;
                sair = true;
            break;
            case 1:
            // GRAVAR DADOS
                inputGravarDados(&arquivoFix);
            break;
            case 2:
            // RECUPERA��O SEQUENCIAL
                visualizarSequencial(&arquivoFix);
            break;
            case 3:
            // RECUPERA��O N�MERO
                visualizarNumero(&arquivoFix);
            break;
            case 4:
            // RECUPERA��O POR CHAVE
                visualizarKey(&arquivoFix);
            break;
            case 5:
            // RECUPERA��O POR NOME
                visualizarNome(&arquivoFix);
            break;
            case 6:
            // REMO��O L�GICA
                removerLogicamente(&arquivoFix);
            break;
            default:
                cout << "N�o reconhecido" << endl;
            break;
        }
    }
    return 0;
}


// favor ignorar
// cout << " Chave: " << regAux.GetKey() << '\n';
// cout << " First Name: " << regAux.GetFirstName() << '\n';
// cout << " Last Name: " << regAux.GetLastName() << '\n'; 
// cout << "\n";
// cout << " Endere�o" << '\n';
// cout << " Logradouro: " << regAux.GetLogradouro() << '\n';
// cout << " N�mero: " << regAux.GetANumero() << '\n';
// cout << " Complemento: " << regAux.GetComplemento() << '\n';
// cout << " Cidade: " << regAux.GetCity() << '\n';
// cout << " Estado: " << regAux.GetState() << '\n';
// cout << " ZIP: " << regAux.GetZipcode() << '\n';
// cout << " Telefone: " << regAux.GetPNumero() << '\n';
// cout << endl << "Digite enter para continuar, ou 0 para parar" << endl;