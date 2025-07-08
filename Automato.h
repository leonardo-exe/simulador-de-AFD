#ifndef AUTOMATO
#define AUTOMATO
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctype.h>
//essa struct representa uma lista encadeada que guarda todas as transições de saída
//de um determinado estado
typedef struct no
{
	//caractere lido na transição de estados
	char saida;
	//inteiro que representa o estado para onde a transição leva
	int destino;
	//ponteiro para o próximo elemento da lista 
	struct no* prox;
} Saida;
//abstração de um estado Q_n 
class Estado
{
private:
	//lista de transições de saída do estado
	Saida* saidas;
	//true caso o estado seja final e false caso contrário
	bool ehfinal;
	//numero que representa o estado Q_n, ex: Q_5
	int elemento;
public:
	//construtor que inicializa as variáveis
	Estado(int elemento);
	//construtor que faz uma copia de um estado já existente 
	Estado(const Estado& other);
	//sobrecarga do operador de atribuição, faz com que seja atribuido uma cópia profunda
	//do estado, criando uma nova lista encadeada igual a original, porém, em outro endereço
	void operator=(const Estado& other);
	//destrutor que desaloca a lista encadeada de transições
	~Estado();
	//adiciona uma transição na lista encadeada
	void pushSaida(char saida, int destino);
	//define o estado como final
	void final();
	//recebe um caractere e um estado de destino, busca se existe uma transição para esse 
	//outro estado através do caractere requerido
	bool transicaoValida(const Estado& other, char caracter) const;
	//retorna se o estado é final ou não
	bool getFinal() const { return this->ehfinal; }
	//retorna uma string que representa o elemento no formato "qn", sendo n um número inteiro
	std::string getElemento() const { return "q" + std::to_string(this->elemento); }
	//retorna o inteiro n que representa o elemento
	int getElementointeiro() const { return this->elemento; }
	//imprime todas as transições do estado 
	void imprimeSaidas() const;
	//retorna o ponteiro da cabeça da lista de transições
	Saida* getSaida() const { return saidas; }
};
//abstração de um automato finito determinístico (AFD)
class Automato
{
private:
	//quantidade de estados que o automato possui
	int nEstados;
	//string que representa o alfabeto, todos os char são caracteres de transição mo automato
	std::string alfabeto;
	//vetor de objetos Estado que contém todos os estados Q_n do automato
	std::vector<Estado> estados;
	//vetor de objetos Estado que contém apenas os estados finais do automato
	std::vector<Estado> finais;
	//método interno que valida se o alfabeto lido se encontra dentro dos limites estabelecidos [a-z] [0-9] 
	//chamado no construtor do automato
	void validaAlfabeto(std::string alfabeto) const;
public:
	//construtor que inicializa as variáveis e o vetor de estados
	Automato(std::string alfabeto, int nEstados);
	//destrutor que desaloca os vetores dinâmicos
	~Automato();
	//sobrecarga de operador que dado um automato e uma string, percorre os caracteres da string pelo automato
	//retorna um valor booleano que diz se a palavra é aceita ou não pelo automato
	bool operator>>(std::string palavra) const;
	//insere um novo estado na posição designada
	void defineEstado(const Estado& novo, int estado);
	//imprime todas as informações do automato (alfabeto, estados, estados finais e transições)
	void imprime() const;
	//imprime uma linguagem regular capaz de gerar a linguagem
	void linguagemRegular() const;
};
//função que dado um objeto Estado, verifica se existe uma transição de saída que consome o caractere passado
//pré-condição: o estado possui uma lista de transições
//pós-condição: nenhuma
//entrada: objeto Estado e um char
//retorno: valor booleano que depende se a condição é cumprida ou não
bool saidaExiste(const Estado& q, char c);
//função que dado um objeto Estado, verifica se existe no alfabeto da linguagem todos os caracteres de transição
//presentes no estado
//pré-condição: o estado possui uma lista de transições
//pós-condição: nenhuma
//entrada: objeto Estado e uma string com as letras do alfabeto
//retorno: valor booleano que depende se a condição é cumprida ou não
bool existeNoAlfabeto(const Estado& q, std::string alfabeto);
//função que abre um arquivo texto, lê os dados e carrega para um objeto Automato
//pré-condição: deve existir um arquivo texto com o exato mesmo nome do passado para a função
//pós-condição: um automato completo é alocado na memória
//entrada: string contendo o nome do arquivo texto
//retorno: endereço da área de memória onde foi alocado o objeto Automato
Automato* carregaArq(std::string nome);
//função que le e valida o buffer, evita comportamento inesperado em tempo de execução
//pré-condição: nenhuma
//pós-condição: buffer vazio
//entrada: limitação de caracteres que pode ser lido
//retorno: primeiro inteiro válido lido
int leBuffer(int floor, int ceil);
#endif