#include "Automato.h"
#include <iostream>
#include <fstream>	
#include <algorithm>

/**
 * A funcao percorre o vetor de saidas do parametro q, 
 * retornando true quando uma saida possuir caractere igual ao parametro c 
 */
bool saidaExiste(const Estado& q, char c)
{
	bool result = false;
	for (int i = 0; i < q.getSaida().size(); i++)
	{
		if (q.getSaida()[i].saida == c)
			result = true;
	}
	return result;
}
/**
 * Percorre o vetor de saidas do parametro q e coleta todos os caracteres de transicao,
 * depois verifica se todos esses caracteres existem no alfabeto
 */
bool existeNoAlfabeto(const Estado& q, std::string alfabeto)
{
	std::string letras = "";
	for (int i = 0; i < q.getSaida().size(); i++)
	{
		letras += q.getSaida()[i].saida;
	}
	for (int i = 0; i < letras.length(); i++)
	{
		bool result = false;
		for (int j = 0; j < alfabeto.length(); j++)
		{
			if (letras[i] == alfabeto[j]) {
				result = true;
				break;
			}
		}
		if (!result)
			return result;
	}
	return true;
}
// percorre a linha do arquivo e retorna uma string com os caracteres validos, 
// ou seja, os dentro de chaves e separados por virgulas
 static std::string alfabeto(std::string linha)
{
	std::string alfab = "";
	for (int i = 0; i < linha.length(); i++)
		if (linha[i] == '{' || linha[i] == '}' || linha[i] == ',' || linha[i] == '=')
			continue;
		else
			alfab += linha[i];
	return alfab;
}
//conta a quantidade de estados da linha passada, no formato qN  
static int quantiaEstados(std::string linha)
{
	int contador = 0;
	for (int i = 0; i < linha.length(); i++)
		if (linha[i] == 'q')
			contador++;
	return contador;
}
//transforma o char de um dígito em um inteiro
static int to_int(char c)
{
	return c - '0';
}
//percorre a linha do arquivo, e insere no vetor de estados finais
static void final(std::string linha, std::vector<int>& finais)
{
	for (int i = 0, j = 0; i < linha.length(); i++)
		if (linha[i] == 'q' && i + 1 < linha.length())
		{
			finais.push_back(to_int(linha[i + 1]));
			j++;
		}
}
// "corta" a string antes do indice passado
static std::string corta(std::string str, int inicio)
{
	std::string result = "";
	for (int i = 0; i < str.length(); i++)
	{
		if (i >= inicio)
			result += str[i];
	}
	return result;
}
// Retorna o índice da primeira ocorrência de 'c' em 'str', ou -1 se não encontrado
static int indicePrimeiraOcorrencia(const std::string& str, char c)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == c)
			return i;
	}
	return -1;
}
/**
 * A funcao percorre todo o arquivo .txt, com os dados no seguinte formato
 * alfabeto={q<estado>,...}
 * estados={q<estado>,...}
 * finais={q<estado>,...}
 * (q<estado>, <caractere>) = q<estado_destino>
 * comportamento indefinido caso esteja fora desse formato,
 * depois de ler, a funcao aloca os dados em um objeto Automato
 */
Automato* carregaArq(std::string nome)
{
	std::ifstream arquivo(nome.c_str());
	if (!arquivo.is_open())
		throw std::runtime_error("Nao foi possivel abrir o arquivo");
	std::string linhas[3];
	std::string letras;
	int nEstados;
	std::vector<int> finais;
	for (int i = 0; i < 3; i++)
		std::getline(arquivo, linhas[i]);
	letras = alfabeto(corta(linhas[0], indicePrimeiraOcorrencia(linhas[0], '{')));
	nEstados = quantiaEstados(corta(linhas[1], indicePrimeiraOcorrencia(linhas[1], '{')));
	final((corta(linhas[2], indicePrimeiraOcorrencia(linhas[2], '{'))), finais);
	Automato* automato = new Automato(letras, nEstados);
	std::string linha;
	std::vector<Estado> aux;
	for (int i = 0; i < nEstados; i++)
	{
		Estado q(i);
		aux.push_back(q);
	}
	while (std::getline(arquivo, linha))
	{
		int elemento;
		char caractere;
		int destino;
		for (int i = 0; i < linha.length(); i++)
		{
			if (linha[i] == 'q')
			{
				elemento = to_int(linha[i + 1]);
			}
			if (linha[i] == ',') {
				caractere = linha[i + 1];
				break;
			}
		}
		for (int i = 0; i < linha.length(); i++)
		{
			if (linha[i] == '=')
				for (int j = i + 1; j < linha.length(); j++)
					if (linha[j] == 'q')
					{
						destino = to_int(linha[j + 1]);
						break;
					}
		}
		aux[elemento].pushSaida(caractere, destino);
	}
	std::for_each(finais.begin(), finais.end(), [&aux](int atual) {
		aux[atual].final();
		});
	std::for_each(aux.begin(), aux.end(), [automato](Estado& atual) {
		automato->defineEstado(atual, atual.getElementointeiro());
		});
	arquivo.close();
	return automato;
}
/// le tudo que esta no buffer em uma string e valida apenas o primeiro digito
int leBuffer(int floor, int ceil)
{
	std::string buffer;
	while (1)
	{
		std::cin >> buffer;
		if (buffer[0] == '-' && isdigit(buffer[1]))
		{
			int i = -to_int(buffer[1]);
			return i;
		}

		if (isdigit(buffer[0]))
		{
			int i = to_int(buffer[0]);
			if (i >= floor && i <= ceil)
				return i;
			else 
				std::cout << "Digite um valor valido\n";
		}
		else
		{
			std::cout << "Digite um valor valido\n";
		}
		std::cin.clear();
	}
}