#ifndef __Estruturas_de_Arquivos___Trabalho_1__Registro__
#define __Estruturas_de_Arquivos___Trabalho_1__Registro__

#include <iostream>
using namespace std;
#include <string>
using namespace std;


class Registro{
protected:
    string idR;
    string exluido;
    string nome;
    string telefone;
    string email;
    
public:
    /*
     * Adiciona os Dados do registro novo
     */
    void novo(string i, string n, string t, string e){
        this->idR = i;
        this->nome = n;
        this->telefone = t;
        this->email = e;
        this->exluido = "N";
    }

	string get_nome(){
	    return this->nome;
	}

	string get_telefone(){
	    return this->telefone;
	}

	string get_email(){
	    return this->email;
	}
    /*
     * Pega os Dados do registro novo
     */
    void Pega_dados(int idR){
        string nome;
        string telefone;
        string email;
        string ID;
        
        ID = this->format(idR, 5, '0');

        
        cout << "\n Nome:\n  ";
        getline(cin, nome);
        
        if(this->removeCaractere('#',&nome)){
            cout << "Nao Permitimos o uso de # no nome\n";
        }
        
        if(this->removeCaractere('|',&nome)){
            cout << "Nao Permitimos o uso de | no nome\n";
        }

		if(this->removeCaractere('*',&nome)){
            cout << "Nao Permitimos o uso de * no nome\n";
        }
        
        cout << "\n Telefone:\n  ";
        getline(cin, telefone);
        
        if(this->removeCaractere('#',&telefone)){
            cout << "Nao Permitimos o uso de # no telefone\n";
        }
        
        if(this->removeCaractere('|',&telefone)){
            cout << "Nao Permitimos o uso de | no telefone\n";
        }

		if(this->removeCaractere('*',&telefone)){
            cout << "Nao Permitimos o uso de * no nome\n";
        }
        
        cout << "\n Email:\n  ";
        getline(cin, email);
        
        if(this->removeCaractere('#',&email)){
            cout << "Nao Permitimos o uso de # no email\n";
        }
        
        if(this->removeCaractere('|',&email)){
            cout << "Nao Permitimos o uso de | no email\n";
        }

		if(this->removeCaractere('*',&email)){
            cout << "Nao Permitimos o uso de * no nome\n";
        }
        
        this->novo(ID, nome, telefone, email);
    }
    
    /*
     * Prepara o Registro para ser gravado no arquivo
     * return: o registro pronto para ser gravado
     */
    string consolidarRegistro(){
        string registro;
        
        registro = this->idR + "|";
        registro += this->exluido + "|";
        registro += this->nome + "|";
        registro += this->telefone + "|";
        registro += this->email + "#";
        
        return registro;
    }
    
    /*
     * remove caracteres de uma string
     * c: caractere a ser removido
     * s: string que será feita a busca do caractere
     * return: verdadeiro faça uma remoção, falso caso não faça
     */
    bool removeCaractere(char c, string *s){
        bool removeu = false;
        size_t pos_char;
        
        do{
            pos_char = s->find(c);
            if (pos_char != string::npos){
                s->replace(pos_char,1,"");
                //cout << "# " + *s + "\n";
                removeu = true;
            }
        }while (pos_char != string::npos);
        
        return removeu;
    }
    
    
    void exibeRegistro(string reg){
        std::stringstream buffer;
        string campo;
        size_t pos_char;
        int cont;
        
        pos_char = reg.find('*');
        if (pos_char == string::npos){
            buffer.str(reg);
            for (cont = 0; cont < 5; cont++) {
                getline(buffer, campo, '|');
                switch (cont) {
                    case 0://id
                        cout << "\nID : ";
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
    }
    
    string format(int i, int n, char c){
        stringstream s;
        s << setw(n) << setfill(c) << i;
        return s.str();
    }
    
};

#endif // defined(__Estruturas_de_Arquivos___Trabalho_1__Registro__)
