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

// Prompt de operaï¿œï¿œo
int inputOperacao(){
    //Exibe opï¿œï¿œes
    cout << '\n';
    cout << "Escolha a operaï¿œï¿œo desejada:" << '\n';
    cout << "(0) - Para sair" << '\n';
    cout << "(1) - Gravaï¿œï¿œo de Dados" << '\n';
    cout << "(2) - Visualizar registros" << '\n';
    cout << "(3) - Recuperar registro por nï¿œmero" << '\n';
    cout << "(4) - Recuperar registro por KEY" << '\n';
    cout << "(5) - Recuperar registro por FIRSTNAME" << '\n';
    cout << "(6) - Remover logicamente um registro" << '\n';
    
    cout << endl;

    //Recebe input
    int operacao;
    string input;
    while(true){
        getline(cin, input);

        std::stringstream myStream(input);
        if(myStream >> operacao){
            break;
        }
        cout << "NÃºmero invÃ¡lido, tente novamente.";
    }
    return operacao;
}

// Loop de input dos dados de pessoas
void inputGravarDados(ArquivoFIX *arq){
    Registro inRegistro;
    int intaux;
    string straux = "";
    do{
        //cin.ignore() usado para ignorar /n que seria absorvido pelo getline()

        cout << "Iniciando gravaï¿œï¿œo." << endl;
        do{
            cout << "KEY: ";
            getline(cin, straux);

            std::stringstream myStream(straux);
            if (myStream >> intaux){
                if(inRegistro.SetKey(intaux)){
                    break;
                }
            }
            cout << "NÃºmero invÃ¡lido, tente novamente" << endl;
        }while(true);
        do{
            cout << "First Name: ";
            getline(cin, straux);
        }while(!inRegistro.SetFirstName(straux));
        do{    
            cout << "Last Name: ";
            getline(cin, straux); 
        }while(!inRegistro.SetLastName(straux));

        cout << "Sobre o endereï¿œo," << endl;
        do{
            cout << "Logradouro: ";
            getline(cin, straux);
        }while(!inRegistro.SetLogradouro(straux));
        do{
            cout << "NÃºmero: ";
            getline(cin, straux);

            std::stringstream myStream(straux);
            if (myStream >> intaux){
                if(inRegistro.SetANumero(intaux)){
                    break;
                }
            }
            cout << "NÃºmero invÃ¡lido, tente novamente" << endl;
        }while(true);
        do{
            cout << "Complemento: ";
            getline(cin, straux);
        }while(!inRegistro.SetComplemento(straux));
        do{
            cout << "Cidade: ";
            getline(cin, straux);
        }while(!inRegistro.SetCity(straux));
        do{
            cout << "Estado (Cï¿œdigo de 2 letras): ";
            getline(cin, straux);
        }while(!inRegistro.SetState(straux));
        do{
            cout << "Zipcode/CEP: ";
            getline(cin, straux);

            std::stringstream myStream(straux);
            if (myStream >> intaux){
                if(inRegistro.SetZipcode(intaux)){
                    break;
                }
            }
            cout << "NÃºmero invÃ¡lido, tente novamente" << endl;
        }while(true);

        cout << "Sobre o celular," << endl;
        do{
            cout << "DDD: ";
            getline(cin, straux);

            std::stringstream myStream(straux);
            if (myStream >> intaux){
                if(inRegistro.SetDDD(intaux)){
                    break;
                }
            }
            cout << "NÃºmero invÃ¡lido, tente novamente" << endl;
        }while(std::cin.fail() || !inRegistro.SetDDD(intaux));
        do{
            cout << "NÃºmero: ";
            getline(cin, straux);

            std::stringstream myStream(straux);
            if (myStream >> intaux){
                if(inRegistro.SetPNumero(intaux)){
                    break;
                }
            }
            cout << "NÃºmero invÃ¡lido, tente novamente" << endl;
        }while(true);

        //DEBUG
        // cout << "\n\nImprimindo valores do registro";
        // inRegistro.print();

        if(arq->escreverReg(&inRegistro)){
            cout << "Registro gravado com sucesso" << endl;
        }
        else cout << "Erro na gravaÃ§Ã£o do registro" << endl;

        
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
        regAux = arq->buscaNumReg(i);
        if(regAux.GetFirstName()!= "")
            regAux.print();
        i++;
    }
}

// Recuperaï¿œï¿œo por nï¿œmero
void visualizarNumero(ArquivoFIX *arq){
    Registro regAux;
    int num;
    cout << "Digite o nï¿œmero que deseja visualizar: ";
    cin >> num;
    
    regAux = arq->buscaNumReg(num);

    regAux.print();
}

// Recuperaï¿œï¿œo por nome
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

// Recuperaï¿œï¿œo por chave
void visualizarKey(ArquivoFIX *arq){
    Registro regAux;
    string aux;
    int key;

    cout << "Digite a chave do registro em que deseja visualizar os dados" << endl;
    cin >> key;
    regAux = arq->buscaKey(key);

    regAux.print();
}

// Remoï¿œï¿œo Lï¿œgica
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
            cout << "Registro nï¿œo encontrado" << endl;
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
        // Apresenta opï¿œï¿œes na tela, retorna operaï¿œï¿œo
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
            // RECUPERAï¿œï¿œO SEQUENCIAL
                visualizarSequencial(&arquivoFix);
            break;
            case 3:
            // RECUPERAï¿œï¿œO Nï¿œMERO
                visualizarNumero(&arquivoFix);
            break;
            case 4:
            // RECUPERAï¿œï¿œO POR CHAVE
                visualizarKey(&arquivoFix);
            break;
            case 5:
            // RECUPERAï¿œï¿œO POR NOME
                visualizarNome(&arquivoFix);
            break;
            case 6:
            // REMOï¿œï¿œO Lï¿œGICA
                removerLogicamente(&arquivoFix);
            break;
            default:
                cout << "NÃºmero nÃ£o reconhecido" << endl;
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
// cout << " Endereï¿œo" << '\n';
// cout << " Logradouro: " << regAux.GetLogradouro() << '\n';
// cout << " Nï¿œmero: " << regAux.GetANumero() << '\n';
// cout << " Complemento: " << regAux.GetComplemento() << '\n';
// cout << " Cidade: " << regAux.GetCity() << '\n';
// cout << " Estado: " << regAux.GetState() << '\n';
// cout << " ZIP: " << regAux.GetZipcode() << '\n';
// cout << " Telefone: " << regAux.GetPNumero() << '\n';
// cout << endl << "Digite enter para continuar, ou 0 para parar" << endl;