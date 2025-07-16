#include "Automato.h"
#include <memory>
#include <iostream>
#define endl "\n"

int main()
{
	//possui blocos try catch para controle de erros
	try 
	{
		//interface
		std::cout << "----SIMULADOR DE AFD----" << endl;
		std::cout << "0-Encerrar programa\n1-Carregar arquivo .txt\n2-Definir automato manualmente\n";
		int i = leBuffer(0, 2);
		if (!i)
			return 0;
		if (i == 1)
		{
			std::cout << "Digite o nome do arquivo texto" << endl;
			std::string nome;
			std::cin >> nome;
			//usando std::unique_ptr pois ele desaloca a memoria caso existam excessoes
			std::unique_ptr<Automato> automato(carregaArq(nome));
			try
			{
				automato->linguagemRegular();
				std::cout << "Digite uma palavra para ser testada pelo automato, -1 para encerrar o programa ou -2 para imprimir o automato (obs: string vazia representada com @)" << endl;
				//ficara lendo palavras enquanto o usuario nao digite -1
				while (1)
				{
					std::string palavra;
					std::cin >> palavra;
					if (palavra[0] == '-' && palavra[1] == '1')
						break;
					if (palavra[0] == '-' && palavra[1] == '2')
					{
						automato->imprime();
						continue;
					}
					if (*automato >> palavra)
						std::cout << "-----Aceita-----" << endl;
					else
						std::cout << "-----Rejeita----" << endl;
				} 
			}
			catch (std::runtime_error& erro)
			{
				std::cout << erro.what() << endl;
				return 1;
			}
		}
		//caso queira definir manualmente
		if (i == 2)
		{
			std::cout << "Digite uma string sem espacos que representa o alfabeto, todo char serah valido na linguagem" << endl;
			std::string alfabeto;
			std::cin >> alfabeto;
			std::cout << "Digite a quantidade de estados do automato" << endl;
			int i;
			std::cin >> i;
			Automato automato(alfabeto, i);
			for (int j = 0; j < i; j++)
			{
				std::cout << "Defina transicoes para q" << j << " e digite -1 para encerrar" << endl;
				Estado novo(j);
				while (1)
				{
					std::cout << "Destino da transicao:" << endl;
					int destino;
					std::cin >> destino;
					char saida;
					if (destino == -1)
						break;
					std::cout << "Caractere lido na transicao" << endl;
					std::cin >> saida;
					novo.pushSaida(saida, destino);
				}
				std::cout << novo.getElemento() << " eh final? (S/N)" << endl;
				char final;
				std::cin >> final;
				if (final == 'S' || final == 's')
					novo.final();
				automato.defineEstado(novo, j);
			}
			automato.linguagemRegular();
			std::cout << "Digite uma palavra para ser testada pelo automato, -1 para encerrar o programa ou -2 para imprimir o automato (obs: string vazia representada com @)" << endl;
			while (1)
			{
				std::string palavra;
				std::cin >> palavra;
				if (palavra[0] == '-' && palavra[1] == '1')
					break;
				if (palavra[0] == '-' && palavra[1] == '2')
				{
					automato.imprime();
					continue;
				}
				if (automato >> palavra)
					std::cout << "-----Aceita-----" << endl;
				else
					std::cout << "-----Rejeita----" << endl;
			}
		}
	}
	catch (std::runtime_error& erro)
	{
		std::cout << erro.what() << endl;
		return 1;
	}
	return 0;
}