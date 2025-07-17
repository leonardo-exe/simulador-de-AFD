DESENVOLVEDOR 
Leonardo Picagevicz, 2025. 
SIMULADOR DE AUTÔMATO FINITO DETERMINÍSTICO 
Este programa, desenvolvido em c++ e documentado no formato doxygen, 
simula o comportamento de um AFD, pode receber um autômato de um arquivo 
texto ou através de inputs no promt, pode receber palavras e testá-las no 
autômato. 
FUNCIONALIDADES 
 O usuário escolhe no início do programa se quer carregar um autômato 
de um arquivo .txt no modelo que será definido ou se prefere definir 
manualmente. 
 O programa gera a gramática regular que gera o autômato. 
 O programa recebe, por meio de inputs, strings para serem testadas 
pelo AFD, imprime todas as transições realizadas e se a string é válida 
na linguagem ou não. 
EXIGÊNCIAS 
Cada autômato possui: um alfabeto com no mínimo uma letra e com caracteres 
entre [a-b | 0-9], no mínimo um estado com no mínimo uma transição, pelo 
menos um estado final.  
FORMATO DO ARQUIVO TEXTO 
alfabeto = { <caractere>, ...} 
estados = { q<estado>, ...} 
finais = { q<estado>, ...} 
Depois, segue-se a quantidade de transições necessárias: 
(q<estado>, <caractere>) = q<estado_destino> 
ESTRUTURA DO PROJETO 
Arquivos: 
 main.c: contém a função principal com a “interface” do programa. 
 Automato.h: contém a declaração das funções e estruturas utilizadas, 
bem como a documentação no formato doxygen. 
 Automato.c: contém todos os métodos da classe Automato. 
 functions.c: contém funções genéricas, como a que carrega o .txt. 
COMPILAÇÃO 
É necessário um compilador C (preferencialmente o GCC) 
No terminal, navegue até a pasta dos arquivos fonte e digite: 
g++ main.c Automato.c functions.c -o main.exe  
Execute com: 
.\main.exe 
DOCUMENTAÇÃO 
Gera um html com a documentação das classes e funções, siga esses passos. 
1- Instale o doxygen. 
2- Crie um arquivo Doxyfile na pasta do programa, o configure como 
desejar. 
3- Execute o arquivo Doxyfile e execute o arquivo index.html gerado.
