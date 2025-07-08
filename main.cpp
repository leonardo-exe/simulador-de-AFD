#include "Automato.h"
using namespace std;

int main()
{
	try 
	{
		cout << "0-Encerrar programa\n1-Carregar arquivo .txt\n2-Definir automato manualmente\n";
		int i = leBuffer(0, 2);
		if (!i)
			return 0;
		if (i == 1)
		{
			cout << "Digite o nome do arquivo texto" << endl;
			string nome;
			cin >> nome;
			Automato* automato = carregaArq(nome);
			try
			{
				automato->linguagemRegular();
				cout << "Digite uma palavra para ser testada pelo automato ou digite -1 para encerrar o programa (obs: string vazia representada com @)" << endl;
				while (1)
				{
					string palavra;
					cin >> palavra;
					if (palavra[0] == '-' && palavra[1] == '1')
						break;
					if (*automato >> palavra)
						cout << "-----Aceita-----" << endl;
					else
						cout << "-----Rejeita----" << endl;
				} 
				delete automato;
			}
			catch (runtime_error& erro)
			{
				cout << erro.what() << endl;
				delete automato;
				return 1;
			}
		}
		if (i == 2)
		{
			cout << "Digite uma string sem espacos que representa o alfabeto, todo char serah valido na linguagem" << endl;
			string alfabeto;
			cin >> alfabeto;
			cout << "Digite a quantidade de estados do automato" << endl;
			int i = leBuffer(0, 1000);
			Automato automato(alfabeto, i);
			for (int j = 0; j < i; j++)
			{
				cout << "Defina transicoes para q" << j << " e digite -1 para encerrar" << endl;
				Estado novo(j);
				while (1)
				{
					cout << "Destino da transicao:" << endl;
					int destino = leBuffer(-1, 1000);
					char saida;
					if (destino == -1)
						break;
					cout << "Caractere lido na transicao" << endl;
					cin >> saida;
					novo.pushSaida(saida, destino);
				}
				cout << novo.getElemento() << " eh final? (S/N)" << endl;
				char final;
				cin >> final;
				if (final == 'S' || final == 's')
					novo.final();
				automato.defineEstado(novo, j);
			}
			automato.linguagemRegular();
			cout << "Digite uma palavra para ser testada pelo automato ou digite -1 para encerrar o programa (obs: string vazia representada com @)" << endl;
			while (1)
			{
				string palavra;
				cin >> palavra;
				if (palavra[0] == '-' && palavra[1] == '1')
					break;
				if (automato >> palavra)
					cout << "-----Aceita-----" << endl;
				else
					cout << "-----Rejeita----" << endl;
			}
		}
	}
	catch (runtime_error& erro)
	{
		cout << erro.what() << endl;
		return 1;
	}
	return 0;
}