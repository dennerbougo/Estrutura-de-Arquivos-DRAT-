#ifndef __Trablho_1__Menu__
#define __Trablho_1__Menu__

#include <iostream>
using namespace std;
#include <string>
using namespace std;
#include <iomanip>
using namespace std;

//#include <stdlib.h>

#include "CRUD_Registro.h"
#include "Indice.h"
#include "Registro.h"
#include "Worst_Fit.h"
#include "CRUD_Sequencial.cpp"
#include <time.h>

class Menu {
protected:
//public:
    CRUD_Registro controlRegistro;
    Registro registro;
    Indice iPrimario;
    Indice iNome;
    Indice iTele;
    Indice iEmail;
    Indice controlID;
    Indice listainvert_inome;
	Indice listainvert_iemail;
	Indice listainvert_itele;
	Worst_Fit iExcluido;
    CRUD_Sequencial controlSequencial;
    clock_t end;
	clock_t start;
	double cronometro;


    
public:
    Menu(){
        this->controlRegistro.set_nome("Registros");
        this->iPrimario.set_nome("indexID");
        this->iNome.set_nome("indexNome");
        this->iTele.set_nome("indexTele");
        this->iEmail.set_nome("indexEMAIL");
        this->iExcluido.set_nome("indexEXCLUIDO"); 
		this->listainvert_inome.set_nome("listainvert_inome");
		this->listainvert_iemail.set_nome("listainvert_iemail");
		this->listainvert_itele.set_nome("listainvert_itele");
        this->controlID.set_nome("controleID");
    }
    
//Denner 18/06, 18:00

    void menu_Principal(){
		this->LimparTela();
        cout << "Acao\n "
        << "1 - Novo Arquivo de Registros\n "
        << "2 - Novo Registro\n "
        << "3 - Buscar de Registro por Indices\n "
        << "4 - Buscar Sequencial de Registro \n "
        << "5 - Remover Registro\n "
		<< "6 - Imprimir Espaços Excluidos\n "
        << "0 - sair \n : ";
    }
    
    void menu_Busca(){
        this->LimparTela();
        cout << "\n Busca:\n "
        << "1 - Por ID\n "
        << "2 - Por Nome\n "
        << "3 - Por Telefone\n "
        << "4 - Por Email\n "
        << "0 - voltar  \n : ";
    }
    
    int seleciona_Acao(){
        int acao;
        
        cin >> acao;
        cin.ignore();
        return acao;
    }
    
    void Novo_ArquivoRegistro(){
        this->controlRegistro.Novo_Arquivo();
        this->iPrimario.Novo_Arquivo();
        this->iNome.Novo_Arquivo();
        this->iEmail.Novo_Arquivo();
		this->iTele.Novo_Arquivo();
        this->iExcluido.Novo_Arquivo();
		this->listainvert_inome.Novo_Arquivo();
		this->listainvert_iemail.Novo_Arquivo();
		this->listainvert_itele.Novo_Arquivo();
        this->controlID.Novo_Arquivo();
    }

	void InsereISecund(string chave_sec, int idReg, string tipo)
	{
		bool existe_secund;
		//id novo da lista invertida
		int idListainvert;

		//id que ja existe com a mesma chave primaria
		int rrn_lista;
		int chave_prim_lista;

		if(tipo.compare("nome") == 0){
			idListainvert = this->listainvert_inome.geraIDLInvert();
			this->listainvert_inome.carregaIndice();
			this->listainvert_inome.InsereLista(idListainvert, idReg, -1);		
			this->listainvert_inome.GravaListaArquivo();
			
			if( this->iNome.pegaChavePrim(chave_sec) == -1){
				this->iNome.insereIndexSec(this->registro.get_nome(), idListainvert, "N");
			} else {
				rrn_lista = this->iNome.pegaChavePrim(chave_sec);
				this->listainvert_inome.carregaIndice();
				chave_prim_lista = this->listainvert_inome.buscaBinaria(rrn_lista);
				this->listainvert_inome.AtualizaProxLista(rrn_lista, chave_prim_lista, idListainvert);
				this->listainvert_inome.GravaListaArquivo();
			}
			this->listainvert_inome.limpaIndice();
			
		} else if(tipo.compare("email") == 0){
			idListainvert = this->listainvert_iemail.geraIDLInvert();
			this->listainvert_iemail.carregaIndice();
			this->listainvert_iemail.InsereLista(idListainvert, idReg, -1);		
			this->listainvert_iemail.GravaListaArquivo();
			
			if( this->iEmail.pegaChavePrim(chave_sec) == -1){
				this->iEmail.insereIndexSec(this->registro.get_email(), idListainvert, "N");
			} else {
				rrn_lista = this->iEmail.pegaChavePrim(chave_sec);
				this->listainvert_iemail.carregaIndice();
				chave_prim_lista = this->listainvert_iemail.buscaBinaria(rrn_lista);
				this->listainvert_iemail.AtualizaProxLista(rrn_lista, chave_prim_lista, idListainvert);
				this->listainvert_iemail.GravaListaArquivo();
			}
			this->listainvert_iemail.limpaIndice();
			
		} else {
			idListainvert = this->listainvert_itele.geraIDLInvert();
			this->listainvert_itele.carregaIndice();
			this->listainvert_itele.InsereLista(idListainvert, idReg, -1);		
			this->listainvert_itele.GravaListaArquivo();
			
			if( this->iTele.pegaChavePrim(chave_sec) == -1){
				this->iTele.insereIndexSec(this->registro.get_telefone(), idListainvert, "N");
			} else {
				rrn_lista = this->iTele.pegaChavePrim(chave_sec);
				this->listainvert_itele.carregaIndice();
				chave_prim_lista = this->listainvert_itele.buscaBinaria(rrn_lista);
				this->listainvert_itele.AtualizaProxLista(rrn_lista, chave_prim_lista, idListainvert);
				this->listainvert_itele.GravaListaArquivo();
			}
			this->listainvert_itele.limpaIndice();
			
		}
	}


    void Novo_Registro(){
        fstream arquivo;
        string reg;
        int idReg;
        long int pos = 0, tam_reg = 0, pos_excluida = 0;

        //pegando dados dos registros e preparando pro formato padrão do registro
        idReg = this->controlID.geraID();
        this->registro.Pega_dados(idReg);
        reg = this->registro.consolidarRegistro();
        
		pos = this->controlRegistro.tamanhoAquivo(this->controlRegistro.get_nome());

        if (this->iExcluido.estaVazio() == false){
//            pega posicao e verifica se cabe
//            e por fim salva o registro na posicao
			tam_reg = this->controlRegistro.Get_Tam_Reg(reg);
			pos_excluida = this->iExcluido.Get_Posicao_Worst_Fit(tam_reg);

			if(pos_excluida != -1){
				pos = pos_excluida;
				Controla_Worst_Fit(tam_reg, pos);
			}
		}
        this->controlRegistro.salva_registro(reg, pos);
        this->iPrimario.insereIndex(idReg, pos);
		this->InsereISecund(this->registro.get_nome(), idReg, "nome");
		this->InsereISecund(this->registro.get_email(), idReg, "email");
		this->InsereISecund(this->registro.get_telefone(), idReg, "tele");
		
        //atualiza indices
    }

	/*
	*Rearruma o Worst_Fit após utilização de um registro excluido
	*tam_reg: tamanho do registro que o usuario quer inserir
	*pos: posicao no registro onde usuario vai inserir o novo registro
	*/
	void Controla_Worst_Fit(long int tam_reg, long int pos){
		long int tam_exc = 0, tam_disp = 0, pos_disp = 0;
		string reg;
		
		reg = this->iExcluido.Get_Registro();
		tam_exc = this->iExcluido.Get_Campo1(reg);
		tam_disp = tam_exc - tam_reg;
		pos_disp = pos + tam_reg;

		this->iExcluido.carregaIndice();
		this->iExcluido.GravaListaArquivo(0);
        //		Organiza_Worst_Fit(tam_disp, pos_disp);
		if(tam_disp > 0){
			this->Organiza_Worst_Fit(tam_disp, pos_disp);
			this->controlRegistro.Marcar_Excluido(pos_disp);
		}

	}
    
	/*
	 *Chama as funções de Organização do Worst_Fit
	 *tam: tamanho do registro excluido
	 *pos: posicao do registro excluido
	 */
	void Organiza_Worst_Fit(long int tam, long int pos){
		this->iExcluido.carregaIndice();
		this->iExcluido.InsereLista(tam,pos);
		this->iExcluido.ordenaIndice();
		this->iExcluido.GravaListaArquivo();
	}

    //Menu de Busca por Indices 
    void controleMenuI(){
        int posR = 0;
		int chave_prim = 0;
		int chave_lista = 0;
        string reg;
        int acao;
        string campoBusca;
		char buffer[5], buffer2[8];
        
        do{
            this->menu_Busca();
            acao = this->seleciona_Acao();
            
            switch (acao) {
                case 0:
                    cout << "\n Voltando\n";
                    break;
                case 1:
                    campoBusca = this->pegaID();
					this->startTempo();
                    posR = this->iPrimario.pegaPosicao(campoBusca);
                    if (posR> -1){
                        reg = this->controlRegistro.Get_Registro(posR);
                        this->registro.exibeRegistro(reg);
                    }
//                    this->controlRegistro.carregaRegistro(posR);
                    break;
                case 2:
					campoBusca = this->pegaNome();
                    this->startTempo();
					chave_lista = this->iNome.pegaChavePrim(campoBusca);
					if (chave_lista > -1){
						do{
							this->listainvert_inome.carregaIndice();
							chave_prim = this->listainvert_inome.buscaBinaria(chave_lista);

//							posR = this->iPrimario.pegaPosicao(itoa(chave_prim, buffer, 10));
                            posR = this->iPrimario.pegaPosicao(to_string(chave_prim));
							if (posR> -1){
								reg = this->controlRegistro.Get_Registro(posR);
								this->registro.exibeRegistro(reg);
							}
							chave_lista = this->listainvert_inome.PegaProx(chave_lista);
						}while(chave_lista != -1);
					}
                    break;
                case 3:
					campoBusca = this->pegaTel();
                    this->startTempo();
					chave_lista = this->iTele.pegaChavePrim(campoBusca);
					if (chave_lista > -1){
						do{
							this->listainvert_itele.carregaIndice();
							chave_prim = this->listainvert_itele.buscaBinaria(chave_lista);

//							posR = this->iPrimario.pegaPosicao(itoa(chave_prim, buffer, 10));
                            posR = this->iPrimario.pegaPosicao(to_string(chave_prim));
							if (posR> -1){
								reg = this->controlRegistro.Get_Registro(posR);
								this->registro.exibeRegistro(reg);
							}
							chave_lista = this->listainvert_itele.PegaProx(chave_lista);
						}while(chave_lista != -1);
					}
                    break;
                case 4:
					campoBusca = this->pegaEmail();
                    this->startTempo();
					chave_lista = this->iEmail.pegaChavePrim(campoBusca);
					if (chave_lista > -1){
						do{
							this->listainvert_iemail.carregaIndice();
							chave_prim = this->listainvert_iemail.buscaBinaria(chave_lista);

//							posR = this->iPrimario.pegaPosicao(itoa(chave_prim, buffer, 10));
                            posR = this->iPrimario.pegaPosicao(to_string(chave_prim));
							if (posR> -1){
								reg = this->controlRegistro.Get_Registro(posR);
								this->registro.exibeRegistro(reg);
							}
							chave_lista = this->listainvert_iemail.PegaProx(chave_lista);
						}while(chave_lista != -1);
					}
                    break;
                default:
                    cout << "\n Opcao invalida, Sorry :D\n";
                    break;
            }
			this->calculoTempo();
			if (acao != 0){
				PressionarBotao();
			}
        }while (acao != 0);
    }
    
    //Menu de Busca Sequencial
    void controleMenuS(){
        int posR = 0;
        int acao;
        string campoBusca;
        string reg;
        
        do{
            this->menu_Busca();
            acao = this->seleciona_Acao();
            switch (acao) {
                case 0:
                    cout << "\n Voltando\n";
                    break;
                case 1:
                    campoBusca = this->pegaID();
					this->startTempo();
                    reg = this->controlRegistro.buscaSequencial(campoBusca);
                    this->registro.exibeRegistro(reg);
                    break;
                case 2:
                    campoBusca = this->pegaCampo5();
					this->startTempo();
					this->controlSequencial.buscaNome(campoBusca);
                    break;
                case 3:
                    campoBusca = this->pegaCampo5();
					this->startTempo();
					this->controlSequencial.buscaTelefone(campoBusca);
                    break;
                case 4:
                    campoBusca = this->pegaCampo5();
					this->startTempo();
					this->controlSequencial.buscaEmail(campoBusca);
                    break;
                default:
                    cout << "\n Opcao invalida, Sorry :D";
                    break;
            }
			this->calculoTempo();
			if (acao != 0){
				PressionarBotao();
			}
        }while (acao != 0);
    }
    
    string pegaID(){
        string campo;
        cout << "\n Digite um id para busca:\n ";
        cin >> campo;
        cin.ignore();
        
//        campo.resize(5,' ');
        return campo;
    }

	//Campos de busca para indice secundario - Tatiane 19/06 - 00h
	string pegaNome(){
		string campo;
        cout << "\n Digite um nome para busca:\n ";
        cin >> campo;
        cin.ignore();
        
        campo.resize(5,' ');
        return campo;
	}

	string pegaTel(){
		string campo;
        cout << "\n Digite um telefone para busca:\n ";
        cin >> campo;
        cin.ignore();
        
        campo.resize(8,' ');
        return campo;
	}

	string pegaEmail(){
		string campo;
        cout << "\n Digite um e-mail para busca:\n ";
        cin >> campo;
        cin.ignore();
        
        campo.resize(8,' ');
        return campo;
	}

//Denner 18/06, 18:00
	void Remove_Registro(){
		long int pos = 0, tam = 0;
		string registro, campoBusca;
		vector<string> lista;

		campoBusca = this->pegaID();
        pos = this->iPrimario.pegaPosicao(campoBusca);
		
		if(pos>-1){
            registro = this->controlRegistro.Get_Registro(pos);
            this->controlRegistro.Remove_Registro(registro, pos);
            
            tam = this->controlRegistro.Get_Tam_Reg(registro);
            
            if (this->iExcluido.estaVazio() == true){
                this->iExcluido.insereIndex(tam, pos);
            }
            else{
                this->Organiza_Worst_Fit(tam,pos);
            }
            this->Organiza_Exclusao_IPrimario(campoBusca);

			cout << "\n Registro Removido!\n";
        }
	}

	void Organiza_Exclusao_IPrimario(string id){
		int IDR = -1;
		int pos = 0;
		
		IDR = atoi(id.c_str());
		this->iPrimario.carregaIndice();
		pos = this->iPrimario.buscaBinaria(IDR);
		this->iPrimario.GravaListaArquivo(pos);
	}

	void Imprime_Espacos_Excluidos(){
		cout << "   LISTA DE ESPACOS EXCLUIDOS\n\n";
		cout << "\tTAMANHO\tPOSICAO\n";
		this->iExcluido.Imprime_Lista();
	}
   
	void LimparTela(){
        #ifdef _WIN32 || ifdef _WIN64
		system("cls");
        #endif
	}
    
	void PressionarBotao(){
        #ifdef _WIN32 || ifdef _WIN64
		cin.ignore();
        #endif
	}
    
	string pegaCampo5(){
        string campo;

		cout << "\n Digite um valor para busca com 5 caracters:\n ";
		cin >> campo;
        cin.ignore();
        
        campo.resize(5,' ');

        return campo;
	}

	void startTempo(){
		this->start = clock();
	}

	void stopTempo(){
		this->end = clock();
	}

	void calculoTempo(){
		this->stopTempo();
		cout << "\n\n O tempo gasto na execucao foi: " << ((double) (end - start)) / CLOCKS_PER_SEC << " segundos.\n";
		this->start = NULL;
		this->end = NULL;
	}

};

#endif /* defined(__Trablho_1__Menu__) */
