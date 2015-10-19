# Identificação

* Página do repositório do trabalho ([link GitHub](https://github.com/jlucaslc/teaching/edit/master/2015.1-IAC-trabalho-pratico)) 

* Discente 1
	* Nome: José Lucas Leite Calheiros
	* Matrícula: 15111947
* Discente 2
	* Nome: Eduarda Tatiane Caetano Chagas
	* Matrícula: 15111882

# Discussão 

* Para compreender o funcionamento de um processo (programa em execução) no Sistema Operacional, utilizando a linguagem de programação C, foi desenvolvido o programa main.c . Por meio da chamada de sistema fork, tal programa foi capaz de criar um novo processo (processo filho) e anatomizar o consumo de memória e da cpu que este gera.
* Após o programa main.c ser chamado no prompt de comando é necessário fornecer umas das duas opções possíveis: “cpu” ou “cpu-mem”. Este por sua vez, independente da opção escolhida, realizará uma chamada fork, que é possível graças as bibliotecas <sys/types.h> e <unistd.h>, e o Sistema Operacional devolverá um número, o pid, que é um identificador de processos, como podemos ver abaixo:
	* pid=fork( );
* A partir deste número realizamos uma verificação de qual processo estará em execução no momento,  visto que este terá um comportamento especial: no processo filho, terá valor igual a 0; e no processo pai, terá o pid (identificação) do processo filho. 
* Entretanto caso ocorra um erro no procedimento de geração de um novo processo, o pid retornará um valor negativo,  e o programa através da função perror especificará que ocorreu um erro e acabará a sua execução,  como podemos verificar no fragmento de código abaixo:
	* If(pid<0){
	* perror (“Erro”);
	* exit (-1);
	* }
* Os tipos de erros mais comuns são memória insuficiente e chamada não suportada pelo kernel.



## Utilização intensa da UCP

* Caso a opção desejada seja “cpu”, o processo filho gerará um loop infinito com o objetivo de utilizar intensamente a unidade de processamento,  visto que esta concentrará todos os seus recursos enquanto este ciclo “eterno” estiver sendo executado. O motivo de utilizar tal método advém do fato a cpu não saber diferenciar um loop infinito de um cálculo complexo que requer inúmeras interações. 
	* If (strcmp (argv [1]=”cpu”)==0)
	* for ( ; ; ){ }
* Enquanto o processo filho ficará encarregado de usar ao máximo a cpu, o processo pai atualizará a cada segundo o consumo que este está produzindo tanto no processador, quanto na memória,  representada pela sigla sz. Este controlará o tempo através da função sleep, que retardará o processo genitor por 1 segundo, sendo assim controlada tal atualização. 
* Tais dados são apresentados pelo comando ps -p <PID> -o %cpu,sz do Linux que foi formatado pela função sprintf, presente na biblioteca <stdio.h>, e armazenado na matriz de caracteres str, que é usada como argumento na função system, que se encontra declarada no ficheiro <stdlib.h>,  e chama o comando já formatado.
* Após 10 segundos o processo gerador matará o seu filho por meio da função kill, como podemos visualizar a seguir:
	* for (i=0; i <10; i++){
	* sleep ( 1 );
	* sprintf (str, “ps -p %d -o %%cpu, sz”, pid);
	* system (srt);
	* }
	* kill (pid,SIGKILL);
* A função kill tem como finalidade enviar um sinal de término a outro processo, desde que seja conhecido o seu pid (identificação). Esta pode enviar dois tipos de sinais: SIGTERM, que realiza um pedido para o processo terminar e SIGKILL, que força o processo a terminar, sendo este último utilizado no código de main.c.
* No gráfico abaixo podemos verificar o consumo (em porcentagem) da cpu e da memória (em Kilobytes) em função do tempo num experimento realizado:

![Grafico CPU](http://www.watermark-images.com/UploadedImages/452rxdt.jpg "Grafico CPU")
![Grafico Memoria](http://www.watermark-images.com/UploadedImages/slr1tcq.jpg "Grafico Memoria")

* Como observado o consumo da memória não será alterado, apenas o da cpu.

## Utilização intensa da UCP e memória

* Entretanto se a opção desejada for “cpu-mem”, o processo filho não só explorará exaustivamente a cpu, como também a memória. Como já descrito anteriormente,  tal processo utilizará um loop infinito para consumir os recursos do processador. No entanto, para também consumir memória,  tal processo utilizará a função de alocação dinâmica de C, chamada malloc.
* Malloc receberá como parâmetro a quantidade de bytes a ser alocado,  neste caso 100.000 a cada ciclo do loop. Desse modo a cada segundo o programa conseguirá consumir exaustivamente a memória.
	* else if (strcmp (argv [1], “cpu-mem”)==0)
	* for ( ; ; ) { malloc (100000); }
* Assim como na primeira opção, o processo pai exibirá a cada segundo o consumo da cpu e da memória,  representados respectivamente pelas siglas %cpu e sz. A função sprintf também formatará a entrada, que sera chamada através da função system. E após passados 10 segundos este forçará o término do outro por meio da chamada a função kill. Terminando assim a execução do programa.
* Como segue graficamente, se faz visível o aumento considerável do consumo da cpu e da memória, que ao longo do processo devido as suas altas taxas provocou um travamento (segundos 8, 9 10) e consequentemente  queda no desempenho da cpu:

![Grafico CPU](http://www.watermark-images.com/UploadedImages/pwh34hw.jpg "Grafico CPU")
![Grafico Memoria](http://www.watermark-images.com/UploadedImages/xqbhncd.jpg "Grafico Memoria")

* Portanto o programa main.c , fazendo uso de funções da linguagem C e de chamadas ao sistema UNIX, consegue gerir um processo do Sistema Operacional,  mensurando o consumo que este produz na cpu e na memória.  Realizando assim seu objetivo principal, compreender o consumo dos recursos do computador pelos processos.

* Programa testado em uma Maquina Virtual Ubuntu 14.04.3 LTS 64 bits utilizando 2048 de RAM.

