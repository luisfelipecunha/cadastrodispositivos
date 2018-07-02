#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estrutura da data
typedef struct 
	{
		int dia;
		int mes;
		int ano;
	} data;
 
//estrutura do dispositivo 
struct device
{
		char tipo[60];
		int numero;
		float t_tela;
		float valor_pago;		
		int registro;
		data entrada;
} ;
 
 

//prototipo das funcoes
int exibirMenu(void);
void gravarDispositivo(void);
void buscarDispositivo(void);
void atualizarDispositivo(void);
void listarDispositivos(void);
void excluirDispositivo(void);
void deletartudo(void);
void flushstdin(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//funcao main 
int main(void)
{
    int opcao;
	//looping ate usuario digitar a opcao sair
    do
    {
        opcao = exibirMenu();//numero retornado da funcao exibirMenu() eh atribuida para a variavel opcao
		//swich que chama outras funcoes
        switch (opcao)
        {
        case 1:
            gravarDispositivo();
            break;
        case 2:
            buscarDispositivo();
            break;
        case 3:
            atualizarDispositivo();
            break;
        case 4:
            excluirDispositivo();
            break;
        case 5:
			listarDispositivos();
			break;
        case 6:
			deletartudo();
			break;
        case 7:
            printf("\n Encerrando...");
            break;
        default:
            printf("\n Opcao invalida!");
        }
        
    } while (opcao != 7); //so sai quando a opcao for = 6;
 
    return 0;
}
 
int exibirMenu(void)
{
    int opcao;
 
    //menu 
 
    printf("\n Cadastro Eletrônicos - email: cunha.felipe96@gmail.com \n");
    printf(" 1. Inserir Dispositivo\n");
    printf(" 2. Buscar Dispositivo\n");
    printf(" 3. Atualizar Dispositivo\n");
    printf(" 4. Excluir Dispositivo\n");
    printf(" 5. Listar Dispositivos \n");
    printf(" 6. Apagar arquivo de dados \n");
    printf(" 7. Encerrar\n\n");
    printf(" Digite a opcao desejada: ");
    scanf("%d", &opcao);
 
    return opcao; //retorna a variavel opcao para o main();
}
 
void gravarDispositivo(void)
{
    
    flushstdin();   
    struct device meudispositivo; 
    FILE *arquivo; //ponteiro para arquivo
   
 
    //system("clear"); // Se estiver usando Linux, é system("clear");
	//cadastro de novo dispositivo
    printf("\tCadastro de dispositivos - INSERIR dispositivo\n\n");
    printf(" Tipo: ");
    fflush(stdin);
    scanf("%[^\n]", meudispositivo.tipo);

    printf(" Serial number: ");
    scanf("%d", &meudispositivo.numero);
    printf(" Tamanho da tela: ");
    scanf("%f", &meudispositivo.t_tela);
    printf(" Valor pago: ");;
    scanf("%f", &meudispositivo.valor_pago);
    printf("Dia de entrada: ");
    scanf("%d", &meudispositivo.entrada.dia);
    printf("Mes de entrada: ");
    scanf("%d", &meudispositivo.entrada.mes);
    printf("Ano de entrada: ");
    scanf("%d", &meudispositivo.entrada.ano);
    printf("Numero de registro: ");
    scanf("%d", &meudispositivo.registro);
	//abrindo arquivo cadastro.dat
    arquivo = fopen("cadastro.dat", "ab");
    if (!arquivo)
    {
        arquivo = fopen("cadastro.dat", "wb");//se o arquivo nao existir cria
    }
 
    fwrite(&meudispositivo, 1, sizeof(struct device), arquivo);//gravando estrutura no arquivo
 
    fclose(arquivo);//fechando arquivo
}
//busca dispositivo no arquivo
void buscarDispositivo(void)
{
    int encontrado = 0;
    char busca[30];
	struct device meuDispositivo;
    FILE *arquivo;
	flushstdin();
	//system("clear"); // Se estiver usando Linux, é system("clear");
	//busca do dispositivo
    printf("\tCadastro de dispositivos - Buscar dispositivo\n\n");
    printf(" Nome do dispositivo: ");//dispositivo a ser buscado
    scanf("%[^\n]", busca);

    arquivo = fopen("cadastro.dat", "rb");//abrindo arquivo em modo leitura
 
    if (arquivo)
    {
        fread(&meuDispositivo, 1, sizeof(struct device), arquivo);//lendo struct do arquivo
        while (!feof(arquivo))
        {
            if (strcmp(busca, meuDispositivo.tipo) == 0) //compara a palavra buscada com o tipo do dispositivo, se for igual exibe o dispositivo achado
            {
                printf(" Tipo: %s\n", meuDispositivo.tipo);
                printf(" Serial Number: %d \n", meuDispositivo.numero);
                printf(" Tamanho da tela: %.1f \n", meuDispositivo.t_tela);
                printf(" Valor pago: R$ %.2f \n", meuDispositivo.valor_pago);
                printf(" Numero de registro: %d \n", meuDispositivo.registro);
                printf(" Data de entrada: %d/%d/%d \n", meuDispositivo.entrada.dia, meuDispositivo.entrada.mes, meuDispositivo.entrada.ano);
                
                encontrado = 1;
                break;
            }
            fread(&meuDispositivo, 1, sizeof(struct device), arquivo);
        }
 
        if (!encontrado) //se encontrado for falso entra no if
        {
            printf("\n Dispositivo nao encontrado!");
            
        }
        fclose(arquivo);//fechando arquivo
    }
    else
    {
        printf("\n Nada encontrado no arquivo!");
        
    }
}
 
void atualizarDispositivo(void)
{
    int encontrado = 0;
    char tipo[30];
    int numero, registro;
    float t_tela, valor_pago;
    struct device temporario;
    FILE *arquivoAntigo = NULL, *arquivoAtualizado = NULL; //dois arquivo para fazer a atualizacao do dispositivo
	flushstdin();
    //system("clear"); 
 
    printf("\tCadastro de Dispositivos - ATUALIZAR Dispositivo\n\n");
    printf(" Tipo do dispositivo: ");
    scanf("%[^\n]", tipo);
   
    printf("Novo Serial Number: ");
    scanf("%d", &numero);
    printf("Novo numero de registro: ");
    scanf("%d", &registro);
    printf(" Novo tamanho da tela: ");
    scanf("%f", &t_tela);
    printf("Novo valor pago: ");
    scanf("%f", &valor_pago);
    
 
    arquivoAntigo = fopen("cadastro.dat", "rb");//abrindo arquivo antigo
    if (arquivoAntigo)
    {
        arquivoAtualizado = fopen("temp.dat", "wb");//abrindo arquivo atualizado
        if (!arquivoAtualizado)
        {
            printf("\n Falha na atualizacao do dispositivo!");
            
            return;
        }
 
        fread(&temporario, 1, sizeof(struct device), arquivoAntigo);//lendo arquivo antigo na estrutura temporaria
        while (!feof(arquivoAntigo))//enquanto nao for o fim do arquivo nao para de ler
        {
            if (strcmp(temporario.tipo, tipo) == 0)//se o dispositivo a ser atualizado for igual ao tipo da estrutura substitue os dados antigos pelos atualizados 
            {
                strcpy(temporario.tipo, tipo);
                temporario.numero = numero;
                temporario.registro = registro;
                temporario.t_tela = t_tela;
                temporario.valor_pago = valor_pago;                
                encontrado = 1;
            }
            fwrite(&temporario, 1, sizeof(struct device), arquivoAtualizado);//grava o temporario no arquivo atualizado
            fread(&temporario, 1, sizeof(struct device), arquivoAntigo);//le o arquivo antigo na estrutura temporaria
        }
 
        fclose(arquivoAntigo);//fechando arquivo antigo
        fclose(arquivoAtualizado);//fechando arquivo atualizado
 
        remove("cadastro.dat");//removendo arquivo antigo
        rename("temp.dat", "cadastro.dat");//renomeando arquivo temporario(atualizado) como arquivo permanente(antigo) 
 
        if (!encontrado)
        {
            printf("\n Nao foi possivel encontrar o dispositivo...");
        }
        else
        {
            printf("\n Atualizacao realizada com sucesso!");
        }
 
        
    }
    else
    {
        printf("\n Nenhum dispositivo encontrado!");
        
    }
}
 
void excluirDispositivo(void)
{
    
    int encontrado = 0;
    char tipo[30];
    struct device d_temporario;
    FILE *arquivoAntigo = NULL, *arquivoAtualizado = NULL;
	flushstdin();
    //system("clear"); 
	//busca e exclui dispositivo solicitado
    printf("\tCadastro de dispositivo - EXCLUIR Dispositivo\n\n");
    printf(" Tipo do dispositivo: ");
    
    scanf("%[^\n]", tipo);

	
    arquivoAntigo = fopen("cadastro.dat", "rb");//abrindo arquivo antigo em modo leitura
    if (arquivoAntigo)
    {
        arquivoAtualizado = fopen("temp.dat", "wb");//abrindo arquivo temporario em modo escrita
        if (!arquivoAtualizado)
        {
            printf("\n Falha na exclusao do dispositivo!");
            fclose(arquivoAntigo);//fechando arquivo antigo
            
            return;
        }
 
        fread(&d_temporario, 1, sizeof(struct device), arquivoAntigo);//lendo arquivo antigo na estrutura d_temporario
        while (!feof(arquivoAntigo))//busca enquanto nao for o fim do arquivo
        {
            if (strcmp(d_temporario.tipo, tipo) == 0)//se dispositivo igual ao buscado
            {
                encontrado = 1;
            }
            else//senao grava a estrutura d_temporario no arquivo atualizado
            {
                fwrite(&d_temporario, 1, sizeof(struct device), arquivoAtualizado);//
            }
            fread(&d_temporario, 1, sizeof(struct device), arquivoAntigo);//abre novamente o arquivo antigo na estrutura d_temporario
        }
 
        fclose(arquivoAntigo);//fechando arquivo antigo
        fclose(arquivoAtualizado);//fechando arquivo atualizado
 
        remove("cadastro.dat");//excluindo arquivo antigo
        rename("temp.dat", "cadastro.dat");//renomeando arquivo atualizado como arquivo permanente
 
        if (!encontrado)
        {
            printf("\n Nao foi possivel encontrar o dispositivo...");
        }
        else
        {
            printf("\n Exclusao realizada com sucesso!");
        }
 
        
    }
    else
    {
        printf("\n Nenhum dispositivo encontrado!");
        
    }
}

5void listarDispositivos(void)
{
	
	struct device lista;
	flushstdin();
	FILE *fp;
	fp = fopen("cadastro.dat", "rb");//abrindo em modo leitura
	if(fp==0) {
		printf("Nao foi possivel abrir o arquivo\n");
		
	} else {
		fread(&lista, 1, sizeof(struct device), fp);//lendo arquivo na struct lista
		do {
						
			printf("Tipo: %s \n", lista.tipo);
			printf("Tamanho da Tela: %1.f pol.\n", lista.t_tela);
			printf("Valor Pago: R$%2.f \n", lista.valor_pago);
			printf("Data de Entrada: %d/%d/%d \n", lista.entrada.dia, lista.entrada.mes, lista.entrada.ano);
			printf("Regitro no: %d \n", lista.registro);
			printf("\n \n");
		} while(fscanf(fp, "%s", lista.tipo) != EOF);//le arquivo e passa para a struct enquanto nao for o fim do arquivo
		
	
	}
	fclose(fp);//fechando arquivo
}

void deletartudo(void) {
	if(remove("cadastro.dat")) {
		printf("Excluido com sucesso \n");
	} else {
		printf("Nao e possivel excluir o arquivo de dados \n");
	}



}
