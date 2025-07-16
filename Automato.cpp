#include "Automato.h"
#include <iostream>
#include <algorithm>

/// inicializando variaveis
Estado::Estado(int elemento)
{
	this->ehfinal = false;
	this->elemento = elemento;
}
/// metodo da classe std::vector se responsabiliza de adicionar ao vetor
void Estado::pushSaida(char saida, int destino)
{
	this->saidas.push_back({ saida, destino });
}
/// apenas define como verdadeira a variavel ehfinal
void Estado::final()
{
	this->ehfinal = true;
}
/// percorre todo o vetor de saidas buscando uma saida que tenha como destino o parametro other, lendo o parametro caracter
bool Estado::transicaoValida(const Estado& other, char caracter) const
{
	for (int i = 0; i < this->saidas.size(); i++)
		if (this->saidas[i].destino == other.elemento && this->saidas[i].saida == caracter)
			return true;
	return false;
}
/// percorre o vetor de saidas do estado, enquanto imprime seus dados no formato "(q<estado>, <caractere>) = q<destino>"
void Estado::imprimeSaidas() const
{
	for (int i = 0; i < this->saidas.size(); i++)
	{
		std::cout << "(" << this->getElemento() << ", " << saidas[i].saida << " = " << "q" << std::to_string(saidas[i].destino) << ")" << std::endl;
	}
}
/// ja inicializa com as variaveis do paramentro other
Estado::Estado(const Estado& other) : ehfinal(other.ehfinal), elemento(other.elemento), saidas(other.saidas)
{}
/// apenas atribui para this as variaveis do parametro other
void Estado::operator=(const Estado& other)
{
	this->ehfinal = other.ehfinal;
	this->elemento = other.elemento;
	this->saidas = other.saidas;

}
/// constroi o objeto desde que a string alfabeto seja valida, cria a quantidade nEstados de elementos no vetor 
Automato::Automato(std::string alfabeto, int nEstados)
{
	validaAlfabeto(alfabeto);
	this->alfabeto = alfabeto;
	this->nEstados = nEstados;
	for (int i = 0; i < nEstados; i++)
	{
		Estado aux(i);
		estados.push_back(aux);
	}
}
/// nao realiza nada, apenas para fins de controle
Automato::~Automato()
{
	std::cout << "Memoria liberada" << std::endl;
}
//função auxiliar para verificar se as transições de um estado tem destinos válidos
static bool existeDestino(const Estado& estado, int max)
{
	for (int i = 0; i < estado.getSaida().size(); i++)
	{
		if (estado.getSaida()[i].destino >= max)
			return false;
	}
	return true;
}
/// desde que as condicoes estejam corretas, adiciona no vetor o estado novo, utiliza o metodo push_back de std::vector
void Automato::defineEstado(const Estado& novo, int estado)
{
	if (!existeNoAlfabeto(novo, this->alfabeto))
		throw std::runtime_error("todos os caracteres de transicao devem existir no alfabeto da linguagem");
	if (!existeDestino(novo, nEstados))
		throw std::runtime_error("tentou definir uma transicao para um estado nao existente no automato");
	this->estados[estado] = novo;
	if (this->estados[estado].getFinal())
		this->finais.push_back(novo);
}
/**
 * imprime as informacoes do automato no formato:
 * alfabeto={q<estado>,...}
 * estados={q<estado>,...}
 * finais={q<estado>,...}
 * (q<estado>, <caractere>) = q<estado_destino>
 */
void Automato::imprime() const
{
	std::cout << "Alfabeto = {";
	for (int i = 0; i < alfabeto.length(); i++)
	{
		if (i == alfabeto.length() - 1)
			std::cout << alfabeto[i];
		else
			std::cout << alfabeto[i] << ",";
	}
	std::cout << "}" << std::endl;
	std::cout << "Estados = {";
	size_t size = estados.size();
	for (int i = 0; i < size; i++)
	{
		if (i == size - 1)
			std::cout << estados[i].getElemento();
		else
			std::cout << estados[i].getElemento() << ",";
	}
	std::cout << "}" << std::endl;
	std::cout << "Estados finais = {";
	for (int i = 0; i < finais.size(); i++)
	{
		if (i == finais.size() - 1)
			std::cout << finais[i].getElemento();
		else
			std::cout << finais[i].getElemento() << ",";
	}
	std::cout << "}" << std::endl;
	std::for_each(estados.begin(), estados.end(), [](Estado atual)
		{
			atual.imprimeSaidas();
		});
}
//"corta" a string antes do indice passado
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
/**
 * percorre a string palavra, ao mesmo tempo que percorre o vetor de estados e o vetor de saidas dentro de cada estado,
 * ao encontrar uma transicao valida do estado atual utilizando o caractere da iteracao atual da string, o estado atual passa
 * a ser o destino da transicao e a string entra na proxima iteracao, na primeira vez que isso nao acontecer a funcao retorna false
 * mesmo que leia a palavra inteira, se o estado em que atual se encontrar no final nao estiver marcado como final, a funcao retorna 
 * false 
 */
bool Automato::operator>>(std::string palavra) const
{
	Estado atual = this->estados[0];
	if (palavra == "@") {
		std::cout << "[" << atual.getElemento() << "]" << std::endl;
		return atual.getFinal() ? true : false;
	}
	for (int i = 0; i < palavra.length(); i++)
	{
		if (saidaExiste(atual, palavra[i]))
		{
			for (int j = 0; j < atual.getSaida().size(); j++)
			{
				if (atual.getSaida()[j].saida == palavra[i])
				{
					std::cout << "[" << atual.getElemento() << "]" << corta(palavra, i) << std::endl;
					atual = this->estados[atual.getSaida()[j].destino];
					break;
				}
			}
		}
		else
		{
			std::cout << "[" << atual.getElemento() << "]" << std::endl;
			return false;
		}
	}
	std::cout << "[" << atual.getElemento() << "]" << std::endl;
	return atual.getFinal() ? true : false;
}
/// itera sobre a string alfabeto, verificando se os caracteres se encontram dentro dos limites [a-z] e [0-9]
void Automato::validaAlfabeto(std::string alfabeto) const
{
	std::for_each(alfabeto.begin(), alfabeto.end(), [](char c) {
		if (!(c >= 'a' && c <= 'z') && !(c >= '0' && c <= '9'))
			throw std::runtime_error("o alfabeto deve possuir apenas letras minusculas e digitos");
		});
}
/**
 * o formato da linguagem sempre vai ter que:
 * q0 = 'S'
 * qN = '@' + n
 * ou seja, seguindo a tabela ASCII, cada estado vai ser representado por uma letra maiúscula,
 * a letra minuscula representa o  caractere lido e a maiuscula o destino da transicao, '@' representa
 * a string vazia, ou o final da palavra, ex:
 * S -> aA | @
 * basicamente, a funcao itera pelo vetor de estados e imprime suas transicoes no formato de gramatica regular  
 */
void Automato::linguagemRegular() const
{
	std::cout << "Linguagem gerada pelo automato:" << std::endl;
	char naoTerminais = 'A' - 1;
	char atualC = 'S';
	for (int i = 0; i < estados.size(); i++)
	{	
		char c1 = naoTerminais + estados[i].getSaida()[0].destino;
		std::cout << atualC << " -> " << estados[i].getSaida()[0].saida << (c1 == '@' ? 'S' : c1);
		for (int j = 1; j < estados[i].getSaida().size(); j++)
		{
			char c2 = naoTerminais + estados[i].getSaida()[j].destino;
			std::cout << " | " << estados[i].getSaida()[j].saida << (c2 == '@' ? 'S' : c2);
		}
		if (estados[i].getFinal())
			std::cout << " | @";
		std::cout << std::endl;
		atualC = naoTerminais + i+1;
	}
}