#ifndef __Trablho_1__CRUD_Arquivo__
#define __Trablho_1__CRUD_Arquivo__

#include <iostream>
using namespace std;
#include <fstream>
using namespace std;

#include <string>
using namespace std;
//#include <unistd.h>

class CRUD_Arquivo {

public:
    /*
     * Cria um novo arquivo, apaga os dados caso tenha algum
     * nome: nome do arquivo a ser criado
     */
    void Novo_Arquivo(string nome){
        ofstream arquivo;
        try {
            arquivo.open(nome, ios::trunc);
//            cout << "Arquivo Criado: " << nome << endl;
            
        } catch (std::fstream::failure e) {
            cout << "ERRO! Impossivel Abrir o arquivo" << endl;
        }
        arquivo.close();
    }
    
    /*
     * Abre um arquivo para leitura e escrita
     * nome: nome do arquivo a ser criado
     * return: um arquivo aberto
     */
    void abre_Arquivo(string nome,fstream *arquivo){
        
        try {
            arquivo->open(nome);
//            cout << "Arquivo aberto para leitura e escrita: " << nome << endl;
        } catch (std::fstream::failure e) {
            cout << "ERRO! Impossivel Abrir o arquivo" << endl;
        }
        
//        return arquivo;
    }

    /*
     * Escreve um registro no fim do arquivo
     * nome: nome do arquivo que receberá novo registro
     * registro: registros que será escrito
     */
    void escreve_Fim(string nome, string registro){
        fstream arquivo;
        
        this->abre_Arquivo(nome, &arquivo);
        this->set_fim(&arquivo, false);
        arquivo << registro;
        arquivo.close();
    }
    
    /*
     * Escreve um registro no fim do arquivo
     * arquivo: arquivo que receberá novo registro
     * registro: registros que será escrito
     */
    void escreve(fstream *arquivo, string registro){
        *arquivo << registro;
//        cout << "Salvando " + registro + "\n";
        arquivo->close();
    }
    
    /*
     * posiciona o seek para o fim do arquivo
     * arquivo: arquivo que terá o seek posicionado no fim
     * leitura: define se posicionará o seek em modo leitura ou não 
     */
    void set_fim(fstream *arq, bool leitura){
        if(leitura == true){
            arq->seekp(0,arq->end);
        }
        else{
            arq->seekg(0,arq->end);
        }
    }
    
    /*
     * positiona o seek para o inicio do arquivo
     * arquivo: arquivo que terá o seek posicionado no inicio
     * leitura: define se posicionará o seek em modo leitura ou não
     */
    void set_inicio(fstream *arq, bool leitura){
        if(leitura == true){
            arq->seekp(0,arq->beg);
        }
        else{
            arq->seekg(0,arq->beg);
        }
    }
    
    /*
     * positiona o seek em determinado lugar do arquivo
     * arquivo: arquivo que terá o seek posicionado na posicao indicada
     * leitura: define se posicionará o seek em modo leitura ou não
     * pos: posicao que o seek apontará
     */
    void set_posicao(fstream *arquivo, bool leitura,int pos){
        if(leitura == true){
            arquivo->seekp(pos);
        }
        else{
            arquivo->seekg(pos);
        }
    }
    
    /*
     * verifica se um determinado arquivo esta vazio
     * nome: nome do arquivo que será verificado
     * return: true se estiver vazio, e false caso contrário
     */
    bool estaVazio (string nome){
        bool vazio = true;
        long int tamanho = 0;
        
        tamanho = tamanhoAquivo(nome);
        
        if (tamanho <= 0) {
            vazio = true;
//            cout << "ta vazio mano\n";
        }
        else{
            vazio = false;
//            cout << "Nao ta vazio mano\n";
        }
        
        return vazio;
    }
    
    
    /*
     * verifica o tamanho de um determinado arquivo
     * nome: nome do arquivo que será verificado
     * return: o tamanho do arquivo
     */
    long int tamanhoAquivo(string nome){
        fstream arquivo;
        long int tamanho = 0;
        
        this->abre_Arquivo(nome, &arquivo);
        
        this->set_fim(&arquivo, false);
        tamanho = arquivo.tellg(); //tamanho do incio até o fim, conta caracteres
//        cout << "Arquivo Com tamanho :" << tamanho << " bytes \n";
        
        arquivo.close();
        
        return tamanho;
    }
};

#endif /* defined(__Trablho_1__CRUD_Arquivo__) */
