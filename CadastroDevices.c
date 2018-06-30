#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>

#define CADASTRO "cadastro.dat"


//struct para a data
struct data
	{
		char dia[2];
		char mes[2];
		char ano[4];
	};


//struct para o cadastro do ponteiro
typedef struct  device
	{
		char tipo[30];
		int numero;
		float t_tela;
		float valor_pago;
		struct data entrada;
		int registro;
	
	} dispositivo;

struct dispositivo *ponteiro;


// funcoes
void abertura();
void menu (*ponteiro);
void cadastrar (device *ponteiro, int n);
void listar (device *ponteiro, int n);
void apagar_todos ();
void pesquisar (device *ponteiro, n);
void editar_registro (device *ponteiro, n);



//ponteiro para arquivo de forma global, pois é util ao longo do programa
FILE *fp;



// funcao de abertura
void abertura() {
	printf("\n \n \n ");
	printf("Bem vindo ao programa de cadastro!!\n");
	printf("\n \n \n \n");

}

//cadastra o produto e salva no arquivo
void cadastrar(struct ponteiro, int n) {
	fp = fopen(CADASTRO, "a+");
	int i;
	if(fp==0) {
		printf("Erro na abertura do arquivo \n");
		exit(1);
	} else {
		ponteiro = (struct dispositivo *)malloc(n * sizeof(struct dispositivo)); //aloca o tamanho do ponteiro da struct
		for(i=0;i<n;i++) {
			printf("Digite o tipo do produto \n");
			scanf("%s", ponteiro->tipo);
			printf("Digite o numero de serie do produto \n");
			scanf("%d", &ponteiro->numero);
			printf("Digite o tamanho da tela em polegadas \n");
			scanf("%f", &ponteiro->t_tela);
			printf("Digite o valor pago em R$ \n");
			scanf("%.2f", &ponteiro->valor_pago);
			printf("Digite o dia mes e ano de entrada separados por espaco ex:'22 10 1998' \n");
			scanf("%s %s %s", ponteiro->entrada.dia, ponteiro->entrada.mes, ponteiro->entrada.ano);
			printf("Digite o codigo de cadastro do produto \n");
			scanf("%d", &codigo->registro);
			fwrite(&ponteiro, sizeof(struct dispositivo), n, fp); //grava os valores digitados em blocos no arquivo

			ponteiro++; //incrementa o ponteiro para a proxima posicao de memoria

		}


	}
	fclose(fp); //fecha o ponteiro para o arquivo
}

void listar(struct ponteiro, int n) {
	int i;
	fp = fopen(CADASTRO, "r");
	if(fp==0) {
		printf("Erro na abertura do arquivo \n");
		exit(1);

	} else {
		for(i=0;feof(fp)== 0;i++) {
			fread(&ponteiro, sizeof(struct dispositivo), 1, fp); //lendo o arquivo por blocos
			printf("Tipo: %s \n", ponteiro->tipo);
			printf("S/N: %d \n", ponteiro->numero);
			printf("Tamanho da Tela: %1.f \n", ponteiro->t_tela);
			printf("Valor Pago: R$%2.f \n", ponteiro->valor_pago);
			printf("Data de Entrada: %s/%s/%s", ponteiro->entrada.dia, ponteiro->entrada.mes, ponteiro->entrada.ano);
			printf("Regitro no: %d", ponteiro->registro);
			ponteiro++;


		}
	}
	fclose(fp);
}

//funcao que apaga o arquivo
void apagar_todos() {
	fp = fopen(CADASTRO, "r+");
	int conf;
	if(fp==0) {
		printf("Erro na abertura do arquivo \n");

	} else {
		fclose(fp);
		sleep(10);
		conf = remove(CADASTRO);
		if(conf) {
			printf("Arquivo apagado com sucesso \n");
		} else {
			printf("Não foi possível apagar o arquivo \n");
		}
	}
}struct

void pesquisar(struct ponteiro, n) {
	int codigo;
	do {
		printf("Digite o codigo do ponteiro que deseja pesquisar ou '0' para sair da pesquisa \n");
		scanf("%d", &codigo); //codigo a ser comparado com a estrutura no arquivo
		if(codigo==0) {
			break;
		} else {
			fp = fopen(CADASTRO, "r"); //abertura do arquivo em modo leitura
			fseek(fp,0,SEEK_SET); //posicionando a leitura pelo inicio do arquivo
			if(fp==NULL){
				printf("Erro!! Não é possível abrir o arquivo \n");
			} else {
				do {
					if(fread(&ponteiro, sizeof(struct dispositivo), 1, fp)==0) {
						break;
					} 
					if(ponteiro->registro==codigo) { //se o codigo for igual o registrado mostra o ponteiro
						printf("Tipo: %s \n", ponteiro->tipo);
						printf("S/N: %d \n", ponteiro->numero);
						printf("Tamanho da Tela: %1.f \n", ponteiro->t_tela);
						printf("Valor Pago: R$%2.f \n", ponteiro->valor_pago);
						printf("Data de Entrada: %s/%s/%s", ponteiro->entrada.dia, ponteiro->entrada.mes, ponteiro->entrada.ano);
						printf("Regitro no: %d", ponteiro->registro);
						break;
					} else {
						ponteiro++; //se nao for o ponteiro passa para o proximo
					}	

				} while(1);
			fclose(fp);	

			}
		fseek(fp,0,SEEK_SET);	
			
		}
	} while(codigo!=0);

	
}

void editar_registro(struct ponteiro, n) {
	int codigo;
	char resposta;
	int posicao = 0;
	int sucesso = 0;
	do {
		printf("Digite o codigo do ponteiro que deseja alterar ou '0' para sair \n");
		scanf("%d", &codigo);
		if(codigo==0) {
			break;
		} else {
			fp = fopen(CADASTRO, "r+");
			fseek(fp, posicao, SEEK_SET);
			if(fp==NULL) {
				printf("Erro!! Não é possível abrir o arquivo \n");

			} else {
				do {
					if(fread(&ponteiro, sizeof(struct dispositivo), 1, fp)==0) {
						break;
					}
					if(ponteiro->registro==codigo) { //se o codigo for igual ao registrado mostra o registro a ser alterado
						printf("<<<<<<<<<<<<<<<Registro antigo>>>>>>>>>>>>>>");
						printf("Tipo: %s \n", ponteiro->tipo);
						printf("S/N: %d \n", ponteiro->numero);
						printf("Tamanho da Tela: %1.f \n", ponteiro->t_tela);
						printf("Valor Pago: R$%2.f \n", ponteiro->valor_pago);
						printf("Data de Entrada: %s/%s/%s", ponteiro->entrada.dia, ponteiro->entrada.mes, ponteiro->entrada.ano);
						printf("Regitro no: %d", ponteiro->registro);
						printf("Tem certeza que deseja alterar? S/N \n");
						scanf("%c", &resposta);
						if(resposta=='S') {
							printf("Digite o tipo do produto \n");
							scanf("%s", ponteiro->tipo);
							printf("Digite o numero de serie do produto \n");
							scanf("%d", &ponteiro->numero);
							printf("Digite o tamanho da tela em polegadas \n");
							scanf("%f", &ponteiro->t_tela);
							printf("Digite o valor pago em R$ \n");
							scanf("%.2f", &ponteiro->valor_pago);
							printf("Digite o dia mes e ano de entrada separados por espaco ex:'22 10 1998' \n");
							scanf("%s %s %s", ponteiro->entrada.dia, ponteiro->entrada.mes, ponteiro->entrada.ano);
							printf("Digite o codigo de cadastro do produto \n");
							scanf("%d", &ponteiro->registro);
							fseek(fp, posicao, SEEK_SET);
							sucesso = fwrite(&ponteiro, sizeof(struct dispositivo), n, fp) == sizeof(struct dispositivo);
							break;

						} else {
							ponteiro++;
						}
						posicao = posicao + sizeof(struct dispositivo);

					} while(1)
				}
			}
		}
	} while(1);
}


//funcao mostra menu
void menu(struct ponteiro)
{
	int op = 1;
	int n;
	// looping do menu que so sai quando o usuario digita '0' que eh atribuida a variavel op
	do{
		//opcoes do menu
		printf("Digite '1'para cadastrar ponteiro \n");
		printf("Digite '2' para listar ponteiros cadastrados \n");
		printf("Digite '3' para apagar um ponteiro \n");
		printf("Digite '4' para pesquisar um ponteiro \n");
		printf("Digite '5' para editar um ponteiro \n");
		printf("Digite '6' para apagar todos \n");
		printf("Digite '0'(zero) para sair \n");
		scanf("%d", &op);

		switch(op) {
			case '1': 
				n++;
				cadastrar(ponteiro, n);
				

			case '2':
				listar(ponteiro, n);

			case '3':
				apagar_um(ponteiro, n);

			case '4':
				pesquisar(ponteiro, n);

			case '5':
				editar_registro(ponteiro, n);

			case '6':
				apagar_todos();

			default:
				printf("Opção Invalida \n");

		} 

	} while(op);
}


void main() {
	
	
	
	abertura();
	//funcao menu recebe o ponteiro *ponteiro para a struct struct dispositivo
	menu(ponteiro);
}