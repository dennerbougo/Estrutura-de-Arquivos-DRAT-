#ifndef __Estruturas_de_Arquivos___Trabalho_1__colecao_registro__
#define __Estruturas_de_Arquivos___Trabalho_1__colecao_registro__

#include <iostream>
using namespace std;

#include <string>
using namespace std;

#include <fstream> 
using namespace std;

#include <sstream>

#include "CRUD_Arquivo.h"
#include "Registro.h"

class CRUD_Registro : public CRUD_Arquivo{
protected:
    string nome_arquivo;
    
public:
    /*
     * Seta o nome do arquivo de registro
     * nome: nome do aquivo
     */
    void set_nome(string nome){
        this->nome_arquivo = nome;
    }
    
    /*
     * return: o nome do arquivo de registros
     */
    string get_nome(){
        return this->nome_arquivo + ".txt";
    }
    
    /*
     * Cria um novo arquivo de registros, caso o arquivo exista e tenha dados, esses serão apagados
     */
    void Novo_Arquivo(){
        string header;
        ifstream arquivo;
        header = "ID|Excluido|Nome|Telefone|Email#"; //esse header tem 32 bytes
        CRUD_Arquivo::Novo_Arquivo(this->get_nome());

        this->salva_registro(header);
    }
    
    /*
     * Abre o arquivo de registro, tanto para leitura quanto para escrita
     * return: o arquivo aberto
     */
    void abre_Arquivo(fstream *arquivo){
//        cout <<"\n hey mano, abriu o registro";
        CRUD_Arquivo::abre_Arquivo(this->get_nome(), arquivo);
    }
    
    /*
     * Salva o registro em determinada posicao do arquivo
     * reg: conteudo a ser salvo no arquivo de registros
     */
    void salva_registro(string reg){
        fstream arquivo;
        
        this->abre_Arquivo(&arquivo);
        if (arquivo.is_open()){
            this->set_fim(&arquivo,false);
            this->escreve(&arquivo, reg);
            arquivo.close();
        }
    }
    
    /*
     * Salva o registro em determinada posicao do arquivo
     * registro: conteudo a ser salvo no arquivo de registros
     * pos: posicao que o arquivo sera salvo
     */
    void salva_registro(string reg, int pos){
        fstream arquivo;
        
        this->abre_Arquivo(&arquivo);
        if (arquivo.is_open()){
            this->set_posicao(&arquivo,false, pos);
            this->escreve(&arquivo, reg);
            arquivo.close();
        }
    }

	/*
     * Função que altera o campo de excluido de 'N' para 'S'
	 * registro: o registro que será excluido
     * pos: posicao do registro que terá o campo alterado
     */
	void Remove_Registro(string registro, int pos){
		char c;
		int cont = 0;

		do{
			c = registro[cont];
			cont++;
		}while(c != '|');

		registro[cont] = 'S';
		salva_registro(registro,pos);
	}
	
	/*
     * Função que retorna uma string, contendo um registro inteiro
     * pos: a posição inicial do registro.
     */
	string Get_Registro(int pos){
		string registro;
		char c;
		fstream arquivo;
        
        this->abre_Arquivo(&arquivo);
        if (arquivo.is_open()){
			this->set_posicao(&arquivo,true, pos);
			do{
				c = arquivo.get();
				registro += c;
			}while (c != '#');
		}
		arquivo.close();
		
		return(registro);
	}


	int Get_Tam_Reg(string reg){
		return (reg.size());
	}

    string carregaRegistro(int pos){
        std::stringstream buffer;
        string campo;
        string reg;
        int cont;
        
        buffer.str(this->Get_Registro(pos));
        for (cont = 0; cont < 5; cont++) {
            getline(buffer, campo, '|');
            switch (cont) {
                case 0://id
                    cout << "ID : ";
                    cout << campo << endl;
                    break;
                case 1://excluido
                    cout << "Excluido : ";
                    cout << campo << endl;
                    break;
                case 2://nome
                    cout << "NOME : ";
                    cout << campo << endl;
                    break;
                case 3://telefone
                    cout << "TELEFONE : ";
                    cout << campo << endl;
                    break;
                case 4://email
                    cout << "EMAIL : ";
                    campo.replace(campo.size()-1,1,"");
                    cout << campo << endl;
                    break;
                    
                default:
                    break;
            }
        }

        
        
    }
    
    /*
     *
     */
    string buscaSequencial(string b){
        bool fim = false;
        bool achei = false;
        char buffer;
        string registro;
        fstream arquivo;
        
        this->abre_Arquivo(&arquivo);
        this->set_posicao(&arquivo, true, 32);
    
        if(arquivo.is_open()){
            while(fim == false){
                if (!arquivo.eof()) {
                    registro.clear();
                    
                    do{
                        buffer = arquivo.get();
                        registro += buffer;
                    }while (buffer != '#' && !arquivo.eof());
                    
                    if (atoi(b.c_str()) == atoi(registro.substr(0,5).c_str())) {
                        fim = true;
                        achei = true;
                    }
                }
                else{
                    fim = true;
                }
            }
			arquivo.close();
        }
        
        if(achei == true && (registro[6] == 'N')){
            return registro;
        }
        else{
            cout << "Arquivo nao encontrado";
            return "*";
        }
    }

	void Marcar_Excluido(long int pos){
		fstream arquivo;
		
		this->abre_Arquivo(&arquivo);
		if(arquivo.is_open()){
			this->set_posicao(&arquivo,false,pos);
			this->escreve(&arquivo,"*");
		}
		arquivo.close();
	}

};
#endif /* defined(__Estruturas_de_Arquivos___Trabalho_1__colecao_registro__) */
