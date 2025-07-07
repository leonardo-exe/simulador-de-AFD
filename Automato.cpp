#include "Automato.h"

Estado::Estado(int elemento)
{
	this->ehfinal = false;
	this->saidas = nullptr;
	this->elemento = elemento;
}
Estado::~Estado()
{
	Saida* atual = this->saidas;
	Saida* proximoNo = nullptr;
	while (atual != nullptr)
	{
		proximoNo = atual->prox;
		delete atual;
		atual = proximoNo;
	}
	this->saidas = nullptr;
}
void Estado::pushSaida(char saida, int destino)
{
	Saida* novo = new Saida;
	novo->destino = destino;
	novo->saida = saida;
	novo->prox = nullptr;

	if (this->saidas == nullptr)
	{
		this->saidas = novo;
		return;
	}

	Saida* atual = this->saidas;
	while (atual->prox != nullptr) atual = atual->prox;
	atual->prox = novo;
}
void Estado::final()
{
	this->ehfinal = true;
}
bool Estado::transicaoValida(const Estado& other, char caracter) const
{
	Saida* aux = this->saidas;
	while (aux != nullptr)
		if (aux->destino == other.elemento && aux->saida == caracter)
			return true;
		else
			aux = aux->prox;
	return false;
}
void Estado::imprimeSaidas() const
{
	Saida* atual = this->saidas;
	while (atual != nullptr)
	{
		std::cout << "(" << this->getElemento() << ", " << atual->saida << " = " << "q" << std::to_string(atual->destino) << ")" << std::endl;
		atual = atual->prox;
	}
}
Estado::Estado(const Estado& other) : ehfinal(other.ehfinal), elemento(other.elemento), saidas(nullptr)
{
	Saida* atual = other.saidas;
	while (atual != nullptr) {
		this->pushSaida(atual->saida, atual->destino);
		atual = atual->prox;
	}
}
void Estado::operator=(const Estado& other)
{
	this->ehfinal = other.ehfinal;
	this->elemento = other.elemento;
	this->saidas = nullptr;

	Saida* atual = other.saidas;
	while (atual != nullptr)
	{
		this->pushSaida(atual->saida, atual->destino);
		atual = atual->prox;
	}
}
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
Automato::~Automato()
{
	std::cout << "Memoria liberada" << std::endl;
}
//função auxiliar para verificar se as transições de u estado tem destinos válidos
static bool existeDestino(const Estado& estado, int max)
{
	Saida* atual = estado.getSaida();
	while (atual != NULL)
	{
		if (atual->destino >= max)
			return false;
		atual = atual->prox;
	}
	return true;
}
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
	int size = estados.size();
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
bool Automato::operator>>(std::string palavra) const
{
	Estado atual = this->estados[0];
	if (palavra == "@")
		return atual.getFinal() ? true : false;
	for (int i = 0; i < palavra.length(); i++)
	{
		if (saidaExiste(atual, palavra[i]))
		{
			Saida* saida = atual.getSaida();
			while (saida != nullptr)
			{
				if (saida->saida == palavra[i]) 
				{
					std::cout << atual.getElemento() << " " << palavra[i] << "-> " << this->estados[saida->destino].getElemento() << std::endl;
					atual = this->estados[saida->destino];
					break;
				}
				saida = saida->prox;
			}
		}
		else
		{
			std::cout << atual.getElemento() << " " << palavra[i] << "->" << " X" << std::endl;
			return false;
		}
	}
	if (!atual.getFinal())
		std::cout << atual.getElemento() << " nao eh estado final" << std::endl;
	return atual.getFinal() ? true : false;
}
void Automato::validaAlfabeto(std::string alfabeto) const
{
	std::for_each(alfabeto.begin(), alfabeto.end(), [](char c) {
		if (!(c >= 'a' && c <= 'z') && !(c >= '0' && c <= '9'))
			throw std::runtime_error("o alfabeto deve possuir apenas letras minusculas e digitos");
		});
}