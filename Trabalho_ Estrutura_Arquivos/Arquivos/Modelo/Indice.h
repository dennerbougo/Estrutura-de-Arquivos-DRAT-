//referencia para uso da classe vector : http://www.mochima.com/tutorials/vectors.html
#ifndef Trablho_1_Indice_h
#define Trablho_1_Indice_h

#include <string>
using namespace std;
#include <vector>
using namespace std;
#include <algorithm>
using namespace std;

#include <fstream> //biblioteca para manipulacao de arquivos
using namespace std;

#include "CRUD_Arquivo.h"

class Indice : public CRUD_Arquivo {
protected:
    std::vector<string> listaIndices;
    string nome_arquivo;
    
    
public:
    /*
     * Seta o nome do arquivo de index
     * nome: nome do aquivo
     */
    void set_nome(string nome){
        this->nome_arquivo = nome;
    }
    
    /*
     * return: Nome do arquivo
     */
    string get_nome(){
        return this->nome_arquivo + ".txt";
    }
    
    /*
     * Abre o arquivo de indice
     */
    void abre_Arquivo(fstream *arquivo){
         CRUD_Arquivo::abre_Arquivo(this->get_nome(), arquivo);
    }

	// Tatiane - 19/06
	void salva_Indice(string registro){
		fstream arquivo;

		this->abre_Arquivo(&arquivo);
		if (arquivo.is_open()){
			this->set_fim(&arquivo,false);
			this->escreve(&arquivo, registro);
			arquivo.close();
		}
	}

    /*
     * Cria um novo arquivo de Index, caso exista apaga e cria novamente
     */
    void Novo_Arquivo(){

        CRUD_Arquivo::Novo_Arquivo(this->get_nome());
    }

    /*
     * Verifica se o arquivo de index está vazio
     * return: Verdadeiro se vazio, Falso caso contrário
     */
    bool estaVazio(){
        string nome;
        nome = this->get_nome();
        return CRUD_Arquivo::estaVazio(nome);
    }

	
	/*
	* Verifica se já existe indice secundário - Tatiane - 19/06
	*/
	//bool ExisteiSec(string chave_sec)
	//{
	//	int chave_prim;
	//	chave_prim = this->buscaBinaria(chave_sec);
	//	if(chave_prim > -1){
	//		return true;
	//	} else {
	//		return false;
	//	}
	//}
    
    /*
     * Insere um novo index no arquivo de index (OBS: acho interessante usar essa função só pra id primário)
     * i: id de identificação
     * p: posição do registro
     */
    void insereIndex(int i, long int p){
        fstream arquivo;
        string registro;
        string pos;
        string ID;

        pos = this->format(p, 5, '0');
        ID = this->format(i, 5, '0');
        
//        pos = std::to_string(p);
//        pos.resize(5,' ');

//        ID = setw(5) << setfill('0') << std::to_string(i);
//        ID.resize(5,' ');

        registro = ID + pos;
        //cout << "ID NOVO :" + ID + " - " + pos + "\n";
        
		this->salva_Indice(registro);

        //this->abre_Arquivo(&arquivo);
        //if (arquivo.is_open()){
        //    this->set_fim(&arquivo,false);
        //    this->escreve(&arquivo, registro);
        //    arquivo.close();
       // }
    }

	/*
	* Adiciona indice secundario - Tatiane 18/06 - 10h40
	*/
	void insereIndexSec(string i, int p, string del){
		fstream arquivo;
        string registro;
        string ID;
		
		std::transform(i.begin(), i.end(), i.begin(), ::toupper);

		ID = this->format(p, 5, '0');
		
		if(this->get_nome().compare("indexNome.txt") == 0) {
			i.resize(5,' ');
		} else {
			i.resize(8,' ');
		}
		
		registro = i + ID + del;
        
		this->salva_Indice(registro);

		//reordenar quando inserir
		this->ordenaIndice();
		this->GravaListaArquivo();
			
	}
     /*
     * Adiciona uma quantidade fixa de valores a esquerda
     */
    string format(int i, int n, char c){
        stringstream s;
        
        s << setw(n) << setfill(c) << i;
        
        return s.str();
    }
    /*
     * Adiciona uma quantidade fixa de valores a esquerda
     */
    string format(string i, int n, char c){
        stringstream s;
        
        s << setw(n) << setfill(c) << i;
        
        return s.str();
    }
    
    /*
     * Gera um id novo para o proximo registro
     * ID: instancia responsavel por cuidar dos indices primarios
     * return: ID gerado 
     */
    int geraID(){
        long int tam = 0;
        int idReg = 0;
        char buffer[5];
        fstream arquivo;
		string Result;          
        
        tam = this->tamanhoAquivo(this->get_nome());
        
        this->abre_Arquivo(&arquivo );
            if(arquivo.is_open()){
            if(tam > 0){
                arquivo.seekg(tam - 5);
                arquivo.read(buffer, 5);
                idReg = atoi(buffer) + 1;
            }
            else{
                idReg = 0;
            }
            Result =this->format(idReg, 5, '0');//std::to_string(idReg);
			this->set_inicio(&arquivo,false);
			this->escreve(&arquivo, Result);
			arquivo.close();
        }
        return idReg;
    }

	int geraIDLInvert(){
        long int tam = 0;
        int idReg = 0;
        char buffer[5];
        fstream arquivo;          
        
        tam = this->tamanhoAquivo(this->get_nome());
        
        this->abre_Arquivo(&arquivo );
            if(arquivo.is_open()){
            if(tam > 0){
                arquivo.seekg(tam - 15);
                arquivo.read(buffer, 5);
                idReg = atoi(buffer) + 1;
            }
            else{
                idReg = 0;
            }
        }
        return idReg;
    }

    /*
     * Limpa lista de Indices
     */
    void limpaIndice(){
        this->listaIndices.clear();
    }
    
    /*
     * Carrega Indice na Memória
     */
    void carregaIndice(){
        bool fim = false;
        char buffer[16];

        stringstream content;
        fstream arquivo;

		this->limpaIndice();


        this->abre_Arquivo(&arquivo);
        if(arquivo.is_open()){
//            content << arquivo.rdbuf();
//            arquivo.close();
          
            while(fim == false){
				if( this->get_nome().compare("indexID.txt") == 0 ){
					arquivo.read(buffer, 10);
					buffer[10] = '\0';
				}else if ( (this->get_nome().compare("indexEXCLUIDO.txt") == 0) ) {
					arquivo.read(buffer, 10);
					buffer[10] = '\0';
//                    cout << "MANOANKAOANAONAONAOANOA";
                    
				} else if ( (this->get_nome().compare("indexNome.txt") == 0) ) {
					arquivo.read(buffer, 11);
					buffer[11] = '\0';
				} else if ( (this->get_nome().compare("indexEMAIL.txt") == 0) || (this->get_nome().compare("indexTele.txt") == 0) ){
					arquivo.read(buffer, 14);
					buffer[14] = '\0';
				} else {
					arquivo.read(buffer, 15);
					buffer[15] = '\0';
				}
				if (!arquivo.eof()) {
//                  cout << ">"<< buffer << "<\n";
                    this->listaIndices.push_back(buffer);
                }
                else{
                    fim = true;
                }
            }
			arquivo.close();
        }
    }
    
    /*
     * Ordena o vetor de indices em ordem crescente
     */
	 struct {
        bool operator()(string a, string b)
        {   
            return (a.compare(b) < 0);
        }   
    } customLess;

    void ordenaIndice(){
        this->carregaIndice();
		if( (this->get_nome().compare("indexNome.txt") == 0) || (this->get_nome().compare("indexEMAIL.txt") == 0) ){
			std::sort(listaIndices.begin(), listaIndices.end(), customLess);
		} else {
			sort(listaIndices.begin(), listaIndices.end());
		}

//        for (int i = 0; i < this->listaIndices.size(); i++) {
//            cout << ">" << this->listaIndices[i] << "<\n";
//        }
    }
    
    /*
     * Dado um indice, retorna a posicao que esse indica no arquivo de resgistro
     * idR: indice que será buscado no arquivo
     * return: posicao do registro no arquivo de registro
     */
    int pegaPosicao(string idR){
        int posR = -1;
        int posI = -1;
        idR = this->format(idR, 5, '0');
        //cout<< "\nPegando pos " << idR;
        
//        cout << "Buscando " + idR + "\n";
        this->carregaIndice();
        posI = this->buscaBinaria(atoi(idR.c_str()));
        
        
        if(posI > -1){
            posR = atoi(this->listaIndices[posI].substr(5,9).c_str());
//            cout << "ACHEI: " + this->listaIndices[posI] << ". Na posicao: " << posI << endl;
        }
        else{
            cout << "Registro não encontrado\n";
        }
        this->limpaIndice();
        return posR;
    }
    
	/*
	* Buscar chave primaria do indice secundario
	*/
	 int pegaChavePrim(string chave_sec){
        int posI = -1;

		if( ((this->get_nome()).compare("indexTele.txt") == 0) || ((this->get_nome()).compare("indexEMAIL.txt") == 0) ) {
			chave_sec.resize(8,' ');
		} else {
			chave_sec.resize(5,' ');
		}
        this->carregaIndice();
		posI = this->buscaBinaria(chave_sec);
        
        
        this->limpaIndice();
		if(posI == -1){
			cout << "\nRegistro nao encontrado!" << endl;
		}
        return posI;
    }
    /*
     * Dado um indice, retorna a posicao que esse indica no arquivo de resgistro 
     * idR: indice que será buscado no arquivo
     * return: posicao do id no registro de indices
     */
    int buscaBinaria(int idR){
        int esq = 0;
        int dir = (int) this->listaIndices.size()-1;
        int meio = (esq+dir)/2;
        bool achou = false;
        int IDR = -1;
        
        while((esq <= dir) && achou == false){
            meio = (esq+dir)/2;
            
			int teste = atoi(this->listaIndices[meio].substr(0,5).c_str());

            if (atoi(this->listaIndices[meio].substr(0,5).c_str()) ==  idR){
                IDR = meio;
                achou = true;
            }
            else if (atoi(this->listaIndices[meio].substr(0,5).c_str()) < idR){
                esq = meio + 1; 
            }
            else if (atoi(this->listaIndices[meio].substr(0,5).c_str()) > idR){
                dir = meio - 1; 
            }
        }
        return IDR;
    }

	//Busca Binaria personalizada para indice sec
	 int buscaBinaria(string chave_sec){
        int esq = 0;
        int dir = (int) this->listaIndices.size()-1;
        int meio = (esq+dir)/2;
        bool achou = false;
        int IDR = -1;
		int tamCampo;

		//if( (this->get_nome()).compare("indexNome.txt") == 0 ) {
			
		if ( ((this->get_nome()).compare("indexTele.txt") == 0) || ((this->get_nome()).compare("indexEMAIL.txt") == 0) ){
			tamCampo = 8;
		} else {
			tamCampo = 5;
		}

        while((esq <= dir) && achou == false){
            meio = (esq+dir)/2;
          
			std::transform(chave_sec.begin(), chave_sec.end(), chave_sec.begin(), ::toupper);
			if ( (this->listaIndices[meio].substr(0,tamCampo)).compare(chave_sec) == 0 ){
                //IDR = meio;
                IDR = atoi(this->listaIndices[meio].substr(tamCampo,5).c_str());
				achou = true;
            }
			else if ( (this->listaIndices[meio].substr(0,tamCampo)).compare(chave_sec) < 0 ){
                esq = meio + 1; 
            }
			else if ( (this->listaIndices[meio].substr(0,tamCampo)).compare(chave_sec) > 0 ){
                dir = meio - 1; 
            }
        }
        return IDR;
    }
		
	void Imprime_Lista(){
        
		string campo1 = "";
        string campo2 = "";
        
        this->carregaIndice();

		for(int cont = 0; cont < listaIndices.size(); cont++){
			campo1 = listaIndices[cont].substr(0,5);
			campo2 = listaIndices[cont].substr(5,5);
			Imprime(campo1, campo2);
		}
	}

	void Imprime(string campo1, string campo2 = ""){
		
		cout << "\t" << campo1;
		cout << "\t" << campo2 << "\n";
	}

	/*
	 *Retorna o vetor (listaIndices)
	 *return: listaIndices
	 */
	vector<string> Get_Lista(){
		return(this->listaIndices);
	}

	/*
	 *Insere um elemento diretamente no final da lista, obedecendo padrao de 5 char pra cada variavel
	 *i: primeiro campo do registro/lista
	 *p: segundo campo do registro/lista
	 */
	void InsereLista(int i, long int p){
        string registro;
        string pos;
        string ID;


		pos = this->format(p, 5, '0');
        
		ID = this->format(i, 5, '0');

		registro = ID + pos;
		        
        this->listaIndices.push_back(registro);
    }

	//Lista invertida personalizada
	void InsereLista(int i, long int p, int aponta){
        string registro;
        string pos;
        string ID;
		string apontador;


		pos = this->format(p, 5, '0');
        
		ID = this->format(i, 5, '0');

		apontador = this->format(aponta, 5, '0');

		registro = ID + pos + apontador;
        
        this->listaIndices.push_back(registro);
    }

	void AtualizaProxLista(int i, long int p, int aponta){

		string registro;
        string pos;
        string ID;
		string apontador;
		string apont2;
		bool achou = false;
		int place;
		int cont;

		pos = this->format(p, 5, '0');
        
		ID = this->format(i, 5, '0');

		apontador = this->format(aponta, 5, '0');
		
		registro = ID + pos + apontador;
		
		place = i;
		
		
		while(achou == false){
			apont2 = this->listaIndices[place].substr(10,5).c_str();
			if( apont2.compare("000-1") == 0){
				this->listaIndices[place] = registro;
				achou = true;
			} else {
				place = atoi(apont2.c_str());
				ID = this->listaIndices[place].substr(0,5);
				pos = this->listaIndices[place].substr(5,5);
				registro = ID + pos + apontador;
				achou = false;
			}
		}
	}

	int PegaProx(int chave_lista){
		this->carregaIndice();
		//string teste = this->listaIndices[chave_lista].substr(10,5);
		//int teste2 = atoi(teste.c_str());
		if( (this->listaIndices[chave_lista].substr(10,5)).compare("000-1") == 0 ){
			return -1;
		} else {
			return atoi(this->listaIndices[chave_lista].substr(10,5).c_str());
		}
	}

	/*
	 *Grava a lista em arquivo
	 *Pos_ignore: Posicao do vetor a ser ignorada ao adicionar no arquivo
	 */
	void GravaListaArquivo(int pos_ignore = -1){
        fstream arquivo;
        
		this->Novo_Arquivo();

        this->abre_Arquivo(&arquivo);
        if (arquivo.is_open()){

			for(int cont = 0; cont < this->listaIndices.size(); cont++){
				if (cont != pos_ignore){
					this->escreve_Fim(this->get_nome(),this->listaIndices[cont]);
				}
			}
			
			arquivo.close();
        }
    }

	/*
	 *Pega os primeiros 5 chars do registro
	 *return: long int contendo o valor do primeiro campo
	 */
	long int Get_Campo1(string registro){
		string tamanho;
		long int tam = 0;
		
		for(int cont = 0; cont < 5; cont++){
			tamanho = tamanho + registro[cont];
		}

		tam = atol(tamanho.c_str());
		return(tam);
	}

	/*
	 *Pega os ultimos 5 chars do registro
	 *return: long int contendo o valor do segundo campo
	 */
	long int Get_Campo2(string registro){
		string tamanho;
		long int tam = 0;
		
		for(int cont = 5; cont < 10; cont++){
			tamanho = tamanho + registro[cont];
		}

		tam = atol(tamanho.c_str());
		return(tam);
	}
    
};
#endif
