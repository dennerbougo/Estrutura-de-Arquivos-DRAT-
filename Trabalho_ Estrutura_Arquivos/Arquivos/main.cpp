#include <iostream>
using namespace std;

//" //para windows
 // pra qualquer sistema diferente do windows

#ifdef _WIN32 || ifdef _WIN64
#include "Modelo\Menu.h
#else
#include "Modelo/Menu.h"
#endif

int main(int argc, const char * argv[]){
    int acao;
    Menu menu;
    
    do {
        menu.menu_Principal();
        acao = menu.seleciona_Acao();
        
        switch (acao) {
            case 0:
                cout << "\n Bye Bye :D\n";
                break;
                
            case 1:
                menu.Novo_ArquivoRegistro();
                break;
            case 2:
                menu.Novo_Registro();
                break;
            case 3:
                menu.controleMenuI();
                break;
            case 4:
                menu.controleMenuS();
                break;
            case 5:
				menu.Remove_Registro();
				menu.PressionarBotao();
				break;
			case 6:
				menu.LimparTela();
				menu.Imprime_Espacos_Excluidos();
				menu.PressionarBotao();
				break;
            default:
                cout << "\n Opcao invalida, Sorry :D";
                break;
            }
    }while (acao != 0);
    
    return 0;
}
