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
	void abre_Arquivo(fstream *arquivo){
        CRUD_Arquivo::abre_Arquivo("Registros.txt", arquivo);
    }

	/* Seta os valores nos campos de acordo com o separador
		qtdeSeparador		= numero de separador encontrados (quando acha '#' volta pra '0')
		ORDEM separadores:	(0->ID; 1->Excluido; 2->Nome; 3->Telefone; 4->Email)
		registro			= valor a ser armazenado
	*/
	void _set(int *qtdeSeparador, string *registro){
		switch (*qtdeSeparador){
		case 0:	this->id = *registro;		break;
		case 1:	this->excluido = *registro;	break;
		case 2:	this->nome = *registro;		break;
		case 3:	this->telefone = *registro;	break;
		case 4:	this->email = *registro;	break;
		default:break;
		}
		*registro = "";
		*qtdeSeparador += 1;
	}

	/* Exibe o registro na tela */
	void getResgistro(){
		cout << "\n\nID : " << this->id << endl;
		cout << "Excluido : " << this->excluido << endl;
		cout << "NOME : " << this->nome << endl;
		cout << "TELEFONE : " << this->telefone << endl;
		cout << "EMAIL : " << this->email << endl;
	}

	/* Verifica se o registro foi excluido */
	int registroExcluido(){
		if(toupper(this->excluido[0]) == toupper('s')){
			return 1;
		} else {
			return 0;
		}
	}

	/* Imprime o registro se o mesmo nao foi excluido */
	void imprimeResgistro(int *exibir, int *qtdeSeparador){
		if(*exibir == 1){
			if(this->registroExcluido() == 0){
				this->getResgistro();
			} else {
				cout << "\n\nHavia (mais) um registro que correspodia a busca, porem o mesmo foi excluido!" << endl;
			}
		}
		*exibir = 0;
		*qtdeSeparador = 0;
	}

	/**/    
	int buscaSecundaria (int campo, string dados){
		fstream arquivo;
		char caracter;
		string registro;

		int qtdeSeparador = 0;	//Conta os separadores para separar os campos.
		int cont = 0;			//Percorrera o dado passado pra busca.
		int encontrei = 0;		//Encontrou o registro.
		int nenhum = 0;			//Nenhum registro corresponde.
		
		this->abre_Arquivo(&arquivo);
		if (arquivo.is_open()){
			this->set_posicao(&arquivo,true, 0);

			//Vamos percorrer o arquivo um caracater por vez.
			do{
				caracter = arquivo.get();
				switch (caracter){
					case '*':												//Ignora os lixos.
						do{
							caracter = arquivo.get();
						} while (caracter != '#');
						break;
					case '|':												//Seta os valores do registro.
						this->_set(&qtdeSeparador, &registro);
						break;
					case '#':
						this->_set(&qtdeSeparador, &registro);				//Seta os valores do registro.
						this->imprimeResgistro(&encontrei, &qtdeSeparador);	//Verifica se pode e imprime.
						break;
					default:
						registro += caracter;
						break;
				}

				//Verifica qual campo sera comparado e se o valor ainda nao foi encontrado
				if(qtdeSeparador == campo && encontrei == 0){
					//Compara os valores em MAIUSCULO.
					if(toupper(caracter) ==  toupper(dados[cont])){
						cont++;
						if(cont == 5){//Se a comparacao chegar aqui o campo foi encontrado.
							encontrei = 1;
							nenhum = 1;
							cont = 0; //Zerado para buscar em mais registros.
						}
					} else {
						cont = 0; //Zero fara que ele encontre no meio dos campos.
						encontrei = 0;
					}
				}
			}while (caracter != EOF);
		}

		arquivo.close();
		if(nenhum == 0){
			cout << "\n\nNao ha qualquer registro que correspoda a busca!" << endl;
		}
		return 0;
	}

	/* Busca atraves do campo nome */
	void buscaNome(string nome){
		this->buscaSecundaria(2, nome);
	}

	/* Busca atraves do campo telefone */
	void buscaTelefone(string telefone){
		this->buscaSecundaria(3, telefone);
	}

	/* Busca atraves do campo email */
	void buscaEmail(string email){
		this->buscaSecundaria(4, email);
	}
};

#endif /* defined(__Trablho_1__CRUD_Arquivo__) */
