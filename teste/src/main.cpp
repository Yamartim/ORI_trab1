#include <iostream>
#include <fstream>

#include "Registro.h"

using namespace std;

int main() {

  // escrita
  Registro reg;
  std::fstream file;
  file.open("test.bin", std::fstream::out | std::fstream::binary);

  reg.SetKey(1234);
  reg.SetLastName("a");
  reg.SetFirstName("a");
  reg.SetLogradouro("a");
  reg.SetANumero(1234);
  reg.SetComplemento("a");
  reg.SetCity("a");
  reg.SetState("a");
  reg.SetZipcode(1234);
  reg.SetDDD(1234);
  reg.SetPNumero(1234);

  file.write((char*)&reg, sizeof(Registro));
  file.close();

  // leitura
  Registro reg2;
  std::fstream file2;
  file2.open("test.bin", std::fstream::in | std::fstream::binary);
  file2.read((char*)&reg2, sizeof(Registro));
  file2.close();

  cout << " Chave: " << reg2.GetKey() << '\n';
  cout << " First Name: " << reg2.GetFirstName() << '\n';
  cout << " Last Name: " << reg2.GetLastName() << '\n'; cout << "\n";
  cout << " Endereço" << '\n';
  cout << " Logradouro: " << reg2.GetLogradouro() << '\n';
  cout << " Número: " << reg2.GetANumero() << '\n';
  cout << " Complemento: " << reg2.GetComplemento() << '\n';
  cout << " Cidade: " << reg2.GetCity() << '\n';
  cout << " Estado: " << reg2.GetState() << '\n';
  cout << " ZIP: " << reg2.GetZipcode() << '\n';
  cout << " Telefone: " << reg2.GetPNumero() << '\n';
  cout << " Digite enter para continuar, ou 0 para parar" << endl;
}
