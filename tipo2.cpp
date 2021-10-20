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

// Prompt de operação
int inputOperacao(){
    //Exibe opções
    cout << '\n';
    cout << "Escolha a operação desejada:" << '\n';
    cout << "(0) - Para sair" << '\n';
    cout << "(1) - Gravação de Dados" << '\n';
    cout << "(2) - Visualizar registros" << '\n';
    cout << "(3) - Recuperar registro por KEY" << '\n';
    cout << "(4) - Recuperar registro por FIRSTNAME" << '\n';
    cout << "(5) - Remover logicamente um registro" << '\n';
    
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
        cout << "Número inválido, tente novamente.";
    }
    return operacao;
}

// Loop de input dos dados de pessoas
void inputGravarDados(ArquivoVAR *arq){
    Registro inRegistro;
    int intaux;
    string straux = "";
    do{
        cout << "Iniciando gravação." << endl;
        do{
            cout << "KEY: ";
            getline(cin, straux);

            std::stringstream myStream(straux);
            if (myStream >> intaux){
                if(inRegistro.SetKeyVAR(intaux)){
                    break;
                }
            }
            cout << "Número inválido, tente novamente" << endl;
        }while(true);
        do{
            cout << "First Name: ";
            getline(cin, straux);
        }while(!inRegistro.SetFirstNameVAR(straux));
        do{    
            cout << "Last Name: ";
            getline(cin, straux); 
        }while(!inRegistro.SetLastNameVAR(straux));

        cout << "Sobre o endereço," << endl;
        do{
            cout << "Logradouro: ";
            getline(cin, straux);
        }while(!inRegistro.SetLogradouroVAR(straux));
        do{
            cout << "Número: ";
            getline(cin, straux);

            std::stringstream myStream(straux);
            if (myStream >> intaux){
                if(inRegistro.SetANumeroVAR(intaux)){
                    break;
                }
            }
            cout << "Número inválido, tente novamente" << endl;
        }while(true);
        do{
            cout << "Complemento: ";
            getline(cin, straux);
        }while(!inRegistro.SetComplementoVAR(straux));
        do{
            cout << "Cidade: ";
            getline(cin, straux);
        }while(!inRegistro.SetCityVAR(straux));
        do{
            cout << "Estado (Código de 2 letras): ";
            getline(cin, straux);
        }while(!inRegistro.SetStateVAR(straux));
        do{
            cout << "Zipcode/CEP: ";
            getline(cin, straux);

            std::stringstream myStream(straux);
            if (myStream >> intaux){
                if(inRegistro.SetZipcodeVAR(intaux)){
                    break;
                }
            }
            cout << "Número inválido, tente novamente" << endl;
        }while(true);

        cout << "Sobre o celular," << endl;
        do{
            cout << "DDD: ";
            getline(cin, straux);

            std::stringstream myStream(straux);
            if (myStream >> intaux){
                if(inRegistro.SetDDDVAR(intaux)){
                    break;
                }
            }
            cout << "Número inválido, tente novamente" << endl;
        }while(true);
        do{
            cout << "Número: ";
            getline(cin, straux);

            std::stringstream myStream(straux);
            if (myStream >> intaux){
                if(inRegistro.SetPNumeroVAR(intaux)){
                    break;
                }
            }
            cout << "Número inválido, tente novamente" << endl;
        }while(true);

        //DEBUG
        // cout << "\n\nImprimindo valores do registro";
        // inRegistro.print();

        if(arq->escreverReg(&inRegistro)){
            cout << "Registro gravado com sucesso" << endl;
        }
        else{
            cout << "Erro na gravação do registro" << endl;
        }        

        cout << endl << "Digite enter para continuar, ou 0 para parar" << endl;
        getline(cin, straux);

    }while(straux.length() == 0);
}

// Loop de "browsing" do arquivo
void visualizarSequencial(ArquivoVAR *arq){
    cout << "Função buscaSequencial não implementada" << endl;
    return;
    Registro regAux;
    string aux;
    int i = 1;

    // Visualiza registros um-a-um até o usuário parar
    do{
        //regAux = arq->buscaSequencial();
        if(regAux.GetFirstName() != ""){
            regAux.print();
            i++;
        }else{
            // Reinicia para o ínicio dos registros
            cout << "== Fim dos registros, voltando ao ínicio... ==";
            i = 1;
        }

        cout << endl << "Digite enter para continuar, ou 0 para parar" << endl;
        std::getline(cin, aux);
    }while(aux.length() == 0);
}

// Recuperação por nome
void visualizarNome(ArquivoVAR *arq){
    Registro regAux;
    string input;
    int i = 0;

    // Loop de visualização para i nomes até o usuário parar
    do{
        // Input do nome para pesquisar e verificação
        do{
            cout << "Digite o nome do registro para visualização dos dados: ";
            getline(cin, input);

            if(regAux.SetFirstNameVAR(input)){
                break;
            }

            cout << "Nome inválido, tente novamente" << endl;
        }while(true);

        // Busca do nome e exibição do registro/erro
        regAux = arq->buscaNome(input);
        if(regAux.GetFirstName() != ""){ // Testa se não é um registro vazio
            //TODO Exibição de todos os registros com o mesmo nome
            i++;
            cout << "== Exibindo registro " << i << " ==" << '\n';
            regAux.print();
        }else{
            cout << "Erro: Nome não encontrado." << endl;
        }

        cout << endl << "Digite enter para continuar, ou 0 para parar" << endl;
        std::getline(cin, input);

    }while(input.length() == 0); // Se digitar algo sair do loop
}

// Recuperação por chave
void visualizarKey(ArquivoVAR *arq){
Registro regAux;
    int key;
    string input;
    do{

        // Verificação de número válido
        do{
            cout << "Digite a chave do registro em que deseja visualizar os dados: ";
            getline(cin, input);

            std::stringstream myStream(input);
            if (myStream >> key){
                break;
            }
            cout << "Número inválido, tente novamente" << endl;
        }while(true);
        
        // Busca e exibição do registro / erro
        regAux = arq->buscaKey(key);
        if(regAux.GetFirstName() != ""){ // Testa se não é um registro vazio
            cout << "== Exibindo registro de chave " << key << " ==" << '\n';
            regAux.print();
        }else{
            cout << "Erro: Registro não encontrado." << endl;
        }

        cout << endl << "Digite enter para continuar, ou 0 para parar" << endl;
        std::getline(cin, input);

    }while(input.length() == 0);
}

// Remoção Lógica
void removerLogicamente(ArquivoVAR *arq){
Registro regAux;
    int key;
    string input;
    do{

        // Verificação de número válido
        do{
            cout << "Digite a chave do registro que deseja remover : ";
            getline(cin, input);

            std::stringstream myStream(input);
            if (myStream >> key){
                break;
            }
            cout << "Número inválido, tente novamente" << endl;
        }while(true);
        
        // Busca e exibição do registro / erro
        if(arq->removerReg(key)){
            cout << "Registro de chave " << key << " removido com sucesso." << endl;
        }else{
            cout << "Não foi possível remover o registro... " << endl;
        }

        cout << endl << "Digite enter para continuar, ou 0 para parar" << endl;
        std::getline(cin, input);

    }while(input.length() == 0);
}

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "Portuguese");

    //Criando objeto de Arquivo
    ArquivoVAR arquivoVar("arquivo2.dat", "indices2.bin", 't');

    bool sair = false;
    while(!sair){
        // Apresenta opções na tela, retorna operação
        switch(inputOperacao())
        {
            case 0:
            // SAIR
                cout << "Saindo do programa" << endl;
                sair = true;
            break;
            case 1:
            // GRAVAR DADOS
                inputGravarDados(&arquivoVar);
            break;
            case 2:
            // RECUPERAÇÃO SEQUENCIAL
                visualizarSequencial(&arquivoVar);
            break;
            case 3:
            // RECUPERAÇÃO POR CHAVE
                visualizarKey(&arquivoVar);
            break;
            case 4:
            // RECUPERAÇÃO POR NOME
                visualizarNome(&arquivoVar);
            break;
            case 5:
            // REMOÇÃO LÓGICA
                removerLogicamente(&arquivoVar);
            break;
            default:
                cout << "Número não reconhecido" << endl;
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