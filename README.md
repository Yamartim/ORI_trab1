# ORI_trab1
 
## Introdução
	O programa se trata de uma CLI para gerenciamento de um banco de dados de pessoas. Cada registro nesse banco de dados contém nome, endereço e telefone de uma pessoa e pelo programa é possível fazer várias operações como adicionar um registro ao banco, remover um registro do banco, buscar um registro baseado no nome da pessoa ou em uma chave identificadora e imprimir na tela os registros armazenados.
	Existem duas versões do programa, uma que gerencia um banco de dados com registros de tamanho fixo e outra que que faz o mesmo com registros de tamanho variável. A experiência do usuário é a mesma em ambas as versões.

## Principais conceitos
	Ao ser executado o programa recupera o arquivo do banco de dados e o atribui ao objeto correspondente que contém uma variedade de métodos para realizar as operações. Em seguida exibe uma interface que detalha as opções de operações disponíveis e permite ao usuário escolher qual será realizada digitando um número:

* Ao digitar 0 a execução do programa é interrompida.

* Ao digitar 1 o usuário é capaz de adicionar um registro ao arquivo
	- O programa exibirá sequencialmente prompts para dar entrada em cada campo.

* Ao digitar 2 o programa recupera e imprime todos os registros atualmente presentes no banco de dados.

* Ao digitar 3 o usuário pode buscar um registro pela ordem de inserção em ordem crescente no banco de dados.
	- O usuário oferece como input um número de 0 a “n-1”, com n sendo o número de registros no banco de dados.
		- zero recuperará e mostrará o primeiro registro inserido no banco.
		- “n-1” recuperará e mostrará o registro mais recentemente inserido no banco.

* Ao digitar 4 o usuário pode buscar um registro pela sua chave única (o campo KEY)
	- O usuário oferece como input um número.
	- Se o número corresponder à KEY de algum registro armazenado, este será recuperado e impresso na tela.

* Ao digitar 5 o usuário pode buscar um registro pelo primeiro nome da pessoa associada (o campo FIRSTNAME).
	- O usuário oferece como input uma string.
	- Se o nome corresponder ao FIRSTNAME de algum registro armazenado, este será recuperado e impresso na tela.

* Ao digitar 6 o usuário pode remover um registro buscando-o por sua KEY assim como na operação do número 4.
	- O usuário oferece como input um número
	- Se o número corresponder à KEY de algum registro armazenado, este será removido logicamente do banco de dados, e será mostrada uma mensagem de confirmação da remoção na tela.
	
Após cada uma dessas operações será mostrada ao usuário uma prompt para repetir a operação pressionando enter ou voltar ao menu principal digitando 0. Assim podem ser feitas várias inserções, remoções ou buscas em sequência.
No caso da visualização da opção 2, será exibido um registro de cada vez, e quando o usuário pressionar enter o próximo na sequência será mostrado.

## Decisões do projeto
	O grupo decidiu realizar o projeto em C++ para que fosse possível fazer uso de programação orientada a objetos, deixando o código mais organizado e modular. Os pilares do funcionamento do programa são a classe Arquivo para realizar operações nos arquivos dos bancos de dados e Registro que contém todos os dados referentes a um único registro.

### Classes
#### Registro
	Contém todos os campos referentes a um registro no banco de dados. É primariamente uma classe auxiliar com propósito de transferir todos os dados de um registro de uma vez só para as operações da classe arquivo. 
O método print() definido no Registro é essencial e é usado frequentemente para que o usuário possa visualizar o conteúdo do registro que está sendo pesquisado ou ver todos os dados do banco.
#### Arquivo
	Classe virtual que representa o caminho para um arquivo de banco de dados e seu respectivo arquivo índice. Esta possui métodos virtuais para operações principais da manipulação de arquivos que são implementados em suas filhas.
##### ArquivoFIX
	Classe filha de Arquivo que representa o armazenamento dos dados em campos de tamanho fixo, assim possui atributos únicos referentes ao byte offset e implementa os métodos de busca, inserção e remoção levando o tamanho fixo em conta.
##### ArquivoVAR
	Classe filha de Arquivo que representa o armazenamento dos dados em campos de tamanho variável, assim possui atributos únicos referentes aos caracteres separadores e implementa os métodos de busca, inserção e remoção levando o tamanho variável em conta.
	A busca sequencial não foi implementada, e a leitura de registros reaproveitados por remoção lógica incompleta. Ambas essas falhas decorrem da falta de tempo que planejamos para a implementação do arquivo variável.
