#ifndef AUTOMATO
#define AUTOMATO
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <string>
/// @brief guarda uma transicao de saida de um determinado estado 
struct Saida
{
	/// @brief caractere lido na transicao de estados 
	char saida;
	/// @brief inteiro que representa o estado para onde a transicao leva 
	int destino;
};
/// @brief abstracao de um estado Q_n 
class Estado
{
private:
	/// @brief objeto vetor da classe std::vector que contem as transicoes de saida do estado 
	std::vector<Saida> saidas;
	/// @brief true caso o estado seja final e false caso contrario 
	bool ehfinal;
	/// @brief numero que representa o estado Q_n, ex: Q_5
	int elemento;
public:
	/**
	 * @brief construtor que inicializa as variaveis
	 * @param elemento inteiro que representa o estado, como 3 para "q3"
	 */
	Estado(int elemento);
	/**
	 * @brief construtor que faz uma copia de um estado ja existente 
	 * @param other segundo objeto estado que sera copiado para o atual
	 */
	Estado(const Estado& other);
	/**
	 * @brief sobrecarga do operador de atribuicao, faz com que seja atribuido uma copia do estado
	 * @param other segundo objeto estado que sera atribuido para o atual
	 */
	void operator=(const Estado& other);
	/**
	 * @brief adiciona uma transicao no vetor de saidas
	 * @param saida caractere de transicao
	 * @param destino destino da transicao
	 */
	void pushSaida(char saida, int destino);
	/// @brief define o estado como final
	void final();
	/**
	 * @brief busca se existe uma transicao para esse outro estado atraves do caractere requerido
	 * @param other estado destino da transicao
	 * @param caracter caractere lido na transicao
	 * @return valor booleano que diz se a transicao eh valida ou nao
	 */
	bool transicaoValida(const Estado& other, char caracter) const;
	/// @return se o estado eh final ou nao
	bool getFinal() const { return this->ehfinal; }
	/// @return uma string que representa o elemento no formato "qn", sendo n um numero inteiro
	std::string getElemento() const { return "q" + std::to_string(this->elemento); }
	/// @return o inteiro n que representa o elemento
	int getElementointeiro() const { return this->elemento; }
	/// @brief imprime todas as transicoes do estado 
	void imprimeSaidas() const;
	/// @return referencia do vetor de saidas
	const std::vector<Saida>& getSaida() const { return saidas; }
};
/// @brief abstracao de um automato finito deterministico (AFD)
class Automato
{
private:
	/// @brief quantidade de estados que o automato possui
	int nEstados;
	/// @brief string que representa o alfabeto, todos os char sao caracteres de transicao mo automato
	std::string alfabeto;
	/// @brief objeto vetor da classe std::vector, contem objetos Estado que contem todos os estados Q_n do automato
	std::vector<Estado> estados;
	/// @brief objeto vetor da classe std::vector, contem apenas os estados finais do automato
	std::vector<Estado> finais;
	/// @brief metodo interno que valida se o alfabeto lido se encontra dentro dos limites estabelecidos [a-z] [0-9], chamado no construtor do automato
	void validaAlfabeto(std::string alfabeto) const; //throw
public:
	/**
	 * @brief construtor que inicializa as variaveis e o vetor de estados
	 * @param alfabeto string contendo apenas caracteres pertencentes ao alfabeto
	 * @param nEstados inteiro que possui o numero de estados
	 */
	Automato(std::string alfabeto, int nEstados);
	/// @brief destrutor que desaloca os vetores dinamicos
	~Automato();
	/**
	 * @brief sobrecarga de operador que dado um automato e uma string, percorre os caracteres da string pelo automato
	 * @param palavra string a ser validada pelo automato
	 * @return valor booleano que diz se a palavra eh aceita ou nao pelo automato
	 */
	bool operator>>(std::string palavra) const;
	/**
	 * @brief insere um novo estado na posicao designada
	 * @param novo objeto Estado que sera adicionado
	 * @param estado inteiro que representa o estado
	 * @throw std::runtime_error caso queira inserir uma transicao com caractere que nao existe no alfabeto
	 * @throw std::runtime_error caso queira definir uma transicao para um estado nao existente
	 */
	void defineEstado(const Estado& novo, int estado); 
	/// @brief imprime todas as informacoes do automato (alfabeto, estados, estados finais e transicoes)
	void imprime() const;
	/// @brief imprime uma linguagem regular gerada pelo automato
	void linguagemRegular() const;
};
/**
 * @brief funcao que dado um objeto Estado, verifica se existe uma transicao de saida que consome o caractere passado
 * @pre o estado possui uma lista de transicoes
 * @param q objeto Estado e ser analisado
 * @param c char que sera buscado
 * @return valor booleano que retorna se a condicao eh cumprida ou nao
 */
bool saidaExiste(const Estado& q, char c);
/**
 * @brief funcao que dado um objeto Estado, verifica se existe no alfabeto da linguagem todos os caracteres de transicao
 * @pre o estado possui uma lista de transicoes
 * @param q objeto Estado a ser analisado
 * @param alfabeto string que contem apenas caracteres validos no alfabeto da linguagem
 * @return valor booleano que retorna se a condicao eh cumprida ou nao 
 */
bool existeNoAlfabeto(const Estado& q, std::string alfabeto);
/**
 * @brief funcao que abre um arquivo texto, le os dados e carrega para um objeto Automato
 * @pre deve existir um arquivo texto com o exato mesmo nome do passado para a funcao
 * @post um automato completo eh alocado na memoria
 * @param nome nome do arquivo texto
 * @return endereco da area de memoria onde foi alocado o objeto Automato
 * @throw std::runtime_error lancado quando nao conseguir abrir o arquivo
 */
Automato* carregaArq(std::string nome); 
/**
 * @brief funcao que le e valida o buffer, evita comportamento inesperado em tempo de execucao
 * @post buffer vazio
 * @param floor limite inferior do intervalo de numeros que podem ser lidos
 * @param ceil limite superio do intervalo de numeros que podem ser lidos 
 * @return primeiro inteiro valido lido
 */
int leBuffer(int floor, int ceil);
/// @author Leonardo Picagevicz
#endif
