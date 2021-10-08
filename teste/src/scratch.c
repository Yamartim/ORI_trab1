

class Registro
{
private:
  int key;
  std::string nome;

  struct Address{
    int numero;
    std::string complemento;
  } address;
  
public:
  int getKey() { return this->key; }
  std::string getNome() { return this->nome; }
  int getNumero() { return this->address.numero; }
  std::string getComplemento() { return this->address.complemento; }

  void setKey(int key) { this->key = key; }
  void setNome(std::string nome) { this->nome = nome; }
  void setNumero(int numero) { this->address.numero = numero; }
  void setAddress(std::string complemento) { this->address.complemento = complemento; }
};
