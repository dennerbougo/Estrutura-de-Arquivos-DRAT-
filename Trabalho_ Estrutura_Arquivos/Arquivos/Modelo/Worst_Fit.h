#ifndef Trablho_1_Worst_Fit_h
#define Trablho_1_Worst_Fit_h

#include <string>
using namespace std;
#include <vector>
using namespace std;
#include <algorithm>
using namespace std;

#include <fstream> //biblioteca para manipulacao de arquivos
using namespace std;

#include "CRUD_Arquivo.h"
#include "Indice.h"

class Worst_Fit : public Indice {
protected:
    
    
public:
	void ordenaIndice(){
//        this->carregaIndice();
        
/*        for (int i = 0; i < this->listaIndices.size(); i++) {
            cout << "-->" << this->listaIndices[i] << "<\n";
        }
*/        
        sort(listaIndices.begin(), listaIndices.end());
        reverse(listaIndices.begin(), listaIndices.end()); //inverte o vetor, acho que será ultil no worst fit
/*        for (int i = 0; i < this->listaIndices.size(); i++) {
            cout << "**>" << this->listaIndices[i] << "<\n";
        }
*/
	}

	/*
	 *Pega o Primeiro registro do arquivo (10 chars)
	 *return: string contendo os 10 primeiros chars do registro
	 */
	string Get_Registro(){
		char registro[10];
		fstream arquivo;
        
        this->abre_Arquivo(&arquivo);
        if (arquivo.is_open()){
			arquivo.read(registro, 10);
//			registro[10] = '\0';
		}
		arquivo.close();
		return(registro);
	}

	/*
	 *Função que verifica se o registro cabe no espaco excluido e retorna a posicao correta para add o registro
	 *tam_reg: tamanho do registro que se quer adicionar
	 *return: Posicao ideal para se adicionar o registro. Caso seja '-1', nao tem espaco disponivel.
	 */
	long int Get_Posicao_Worst_Fit(long int tam_reg){
		long int tam_excluido = 0, posicao = -1;
		string reg_excluido;

		reg_excluido = this->Get_Registro();
		tam_excluido = this->Get_Campo1(reg_excluido);

		if(tam_reg <= tam_excluido){
			posicao = this->Get_Campo2(reg_excluido);
		}
		return(posicao);
	}

	/*
	 *Função que pega o tamanho restante do espaco excluido, subtraindo pelo tam do registro q o usuario vai inserir
	 *tam_reg: tamanho do registro que se quer adicionar
	 *tam_disp: tamanho disponivel restante do espaco excluido
	 */
	long int Get_tam_disp(long int tam_reg){
		long int tam_disp = 0;
		string reg_excluido;

		reg_excluido = this->Get_Registro();
		tam_disp = this->Get_Campo1(reg_excluido);
		tam_disp -= tam_reg;
		return(tam_disp);
	}

	/*
	 *Função que recalcula a posicao excluida
	 *tam_reg: tamanho do registro que se quer adicionar
	 *pos_disp: posicao livre para adicionar outros registros
	 */
	long int Get_pos_disp(long int tam_reg){
		long int pos_disp = 0;
		string reg_excluido;

		reg_excluido = this->Get_Registro();
		pos_disp = this->Get_Campo2(reg_excluido);
		pos_disp += tam_reg;
		return(pos_disp);
	}

};

#endif