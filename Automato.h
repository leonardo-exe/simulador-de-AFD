#ifndef AUTOMATO
#define AUTOMATO
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctype.h>
//essa struct representa uma lista encadeada que guarda todas as transi��es de sa�da
//de um determinado estado
typedef struct no
{
	//caractere lido na transi��o de estados
	char saida;
	//inteiro que representa o estado para onde a transi��o leva
	int destino;
	//ponteiro para o pr�ximo elemento da lista 
	struct no* prox;
} Saida;
//abstra��o de um estado Q_n 
class Estado
{
private:
	//lista de transi��es de sa�da do estado
	Saida* saidas;
	//true caso o estado seja final e false caso contr�rio
	bool ehfinal;
	//numero que representa o estado Q_n, ex: Q_5
	int elemento;
public:
	//construtor que inicializa as vari�veis
	Estado(int elemento);
	//construtor que faz uma copia de um estado j� existente 
	Estado(const Estado& other);
	//sobrecarga do operador de atribui��o, faz com que seja atribuido uma c�pia profunda
	//do estado, criando uma nova lista encadeada igual a original, por�m, em outro endere�o
	void operator=(const Estado& other);
	//destrutor que desaloca a lista encadeada de transi��es
	~Estado();
	//adiciona uma transi��o na lista encadeada
	void pushSaida(char saida, int destino);
	//define o estado como final
	void final();
	//recebe um caractere e um estado de destino, busca se existe uma transi��o para esse 
	//outro estado atrav�s do caractere requerido
	bool transicaoValida(const Estado& other, char caracter) const;
	//retorna se o estado � final ou n�o
	bool getFinal() const { return this->ehfinal; }
	//retorna uma string que representa o elemento no formato "qn", sendo n um n�mero inteiro
	std::string getElemento() const { return "q" + std::to_string(this->elemento); }
	//retorna o inteiro n que representa o elemento
	int getElementointeiro() const { return this->elemento; }
	//imprime todas as transi��es do estado 
	void imprimeSaidas() const;
	//retorna o ponteiro da cabe�a da lista de transi��es
	Saida* getSaida() const { return saidas; }
};
//abstra��o de um automato finito determin�stico (AFD)
class Automato
{
private:
	//quantidade de estados que o automato possui
	int nEstados;
	//string que representa o alfabeto, todos os char s�o caracteres de transi��o mo automato
	std::string alfabeto;
	//vetor de objetos Estado que cont�m todos os estados Q_n do automato
	std::vector<Estado> estados;
	//vetor de objetos Estado que cont�m apenas os estados finais do automato
	std::vector<Estado> finais;
	//m�todo interno que valida se o alfabeto lido se encontra dentro dos limites estabelecidos [a-z] [0-9] 
	//chamado no construtor do automato
	void validaAlfabeto(std::string alfabeto) const;
public:
	//construtor que inicializa as vari�veis e o vetor de estados
	Automato(std::string alfabeto, int nEstados);
	//destrutor que desaloca os vetores din�micos
	~Automato();
	//sobrecarga de operador que dado um automato e uma string, percorre os caracteres da string pelo automato
	//retorna um valor booleano que diz se a palavra � aceita ou n�o pelo automato
	bool operator>>(std::string palavra) const;
	//insere um novo estado na posi��o designada
	void defineEstado(const Estado& novo, int estado);
	//imprime todas as informa��es do automato (alfabeto, estados, estados finais e transi��es)
	void imprime() const;
	//imprime uma linguagem regular capaz de gerar a linguagem
	void linguagemRegular() const;
};
//fun��o que dado um objeto Estado, verifica se existe uma transi��o de sa�da que consome o caractere passado
//pr�-condi��o: o estado possui uma lista de transi��es
//p�s-condi��o: nenhuma
//entrada: objeto Estado e um char
//retorno: valor booleano que depende se a condi��o � cumprida ou n�o
bool saidaExiste(const Estado& q, char c);
//fun��o que dado um objeto Estado, verifica se existe no alfabeto da linguagem todos os caracteres de transi��o
//presentes no estado
//pr�-condi��o: o estado possui uma lista de transi��es
//p�s-condi��o: nenhuma
//entrada: objeto Estado e uma string com as letras do alfabeto
//retorno: valor booleano que depende se a condi��o � cumprida ou n�o
bool existeNoAlfabeto(const Estado& q, std::string alfabeto);
//fun��o que abre um arquivo texto, l� os dados e carrega para um objeto Automato
//pr�-condi��o: deve existir um arquivo texto com o exato mesmo nome do passado para a fun��o
//p�s-condi��o: um automato completo � alocado na mem�ria
//entrada: string contendo o nome do arquivo texto
//retorno: endere�o da �rea de mem�ria onde foi alocado o objeto Automato
Automato* carregaArq(std::string nome);
//fun��o que le e valida o buffer, evita comportamento inesperado em tempo de execu��o
//pr�-condi��o: nenhuma
//p�s-condi��o: buffer vazio
//entrada: limita��o de caracteres que pode ser lido
//retorno: primeiro inteiro v�lido lido
int leBuffer(int floor, int ceil);
#endif