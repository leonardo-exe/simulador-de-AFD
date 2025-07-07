#include "Automato.h"

bool saidaExiste(const Estado& q, char c)
{
	bool result = false;
	Saida* saidas = q.getSaida();
	while (saidas != nullptr)
	{
		if (saidas->saida == c)
			result = true;
		saidas = saidas->prox;
	}
	return result;
}
bool existeNoAlfabeto(const Estado& q, std::string alfabeto)
{
	Saida* saidas = q.getSaida();
	std::string letras = "";
	while (saidas != nullptr)
	{
		letras += saidas->saida;
		saidas = saidas->prox;
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
//percorre a linha do arquivo e retorna uma string com os caracteres validos
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
//conta a quantidade de estados Q_n na linha passada
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
//percorre a linha do arquivo, e insere no vetor os estados encontrados
static void final(std::string linha, std::vector<int>& finais)
{
	for (int i = 0, j = 0; i < linha.length(); i++)
		if (linha[i] == 'q' && i + 1 < linha.length())
		{
			finais.push_back(to_int(linha[i + 1]));
			j++;
		}
}
Automato* carregaArq(std::string nome)
{
	std::ifstream arquivo(nome.c_str());
	if (!arquivo.is_open())
		throw std::runtime_error("Nao foi possivel abrir o arquivo");
	std::string linhas[6];
	std::string letras;
	int nEstados;
	std::vector<int> finais;
	for (int i = 0; i < 6; i++)
	{
		if (i % 2)
			std::getline(arquivo, linhas[i]);
		else
			std::getline(arquivo, linhas[i], '=');
	}
	for (int i = 0; i < 6; i++)
	{
		if (linhas[i] == "alfabeto")
			letras = alfabeto(linhas[i + 1]);
		if (linhas[i] == "estados")
			nEstados = quantiaEstados(linhas[i + 1]);
		if (linhas[i] == "finais")
			final(linhas[i + 1], finais);
	}
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
	}
}