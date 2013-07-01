#ifndef __Estruturas_de_Arquivos___Trabalho_1__colecao_sequencial__
#define __Estruturas_de_Arquivos___Trabalho_1__colecao_sequencial__
#include <iostream>
using namespace std;
#include <fstream>
using namespace std;

#include <string>
using namespace std;
//#include <unistd.h>

#include "CRUD_Arquivo.h"

class CRUD_Sequencial : public CRUD_Arquivo  {

protected:
	string id;
	string nome;
	string excluido;
	string telefone;
	string email;

public:

	/* Abre o arquivo */
	void abre_Arquivo(fstream *arquivo);

	/* Seta os valores nos campos de acordo com o separador
		qtdeSeparador		= numero de separador encontrados (quando acha '#' volta pra '0')
		ORDEM separadores:	(0->ID; 1->Excluido; 2->Nome; 3->Telefone; 4->Email)
		registro			= valor a ser armazenado
	*/
	void _set(int *qtdeSeparador, string *registro);

	/* Exibe o registro na tela */
	void getResgistro();

	/* Verifica se o registro foi excluido */
	int registroExcluido();

	/* Imprime o registro se o mesmo nao foi excluido */
	void imprimeResgistro(int *exibir, int *qtdeSeparador);

	/* Funcao generica que faz a magica! */
	int buscaSecundaria (int campo, string dados);

	/* Busca atraves do campo nome */
	void buscaNome(string nome);

	/* Busca atraves do campo telefone */
	void buscaTelefone(string telefone);

	/* Busca atraves do campo email */
	void buscaEmail(string email);
};

#endif /* defined(__Trablho_1__CRUD_Arquivo__) */
