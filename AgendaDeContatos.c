#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dia;
    int mes;
} AniversarioT;

typedef struct {
    char nome[60];
    char telefone[16];
    AniversarioT aniversario;
}ContatoT;

//Pergunta e le os dados informados pelo usuario e insere o(s) contato(s) na struct apontada pelo ponteiro contato.
void inserirContatos(int qtdContatosNovos, int qtdContatosCriados, ContatoT ** contato);
//Imprime as informacoes de todos os contatos na tela.
void buscarTodosContatos(int qtdContatosExistentes, ContatoT *contato);
//Imprime as informacoes do contato correspondente ao nome passado como parametro.
void buscarContatoPorNome(char  nome[60], int qtdContatosExistentes, ContatoT * contato);
//Imprime as informacoes do contato cujo a primeira letra corresponde a letra passada como parametro.
void buscarContatosPorLetra(char letra, int qtdContatosExistentes, ContatoT * contato);
//Imprime as informacoes do contato cujo o mes de aniversario corresponde ao mes passado como parametro.
void buscarContatosPorMes(int mes, int qtdContatosExistentes, ContatoT * contato);

int main()
{
    int opc = -1,mes,i,qtdContatosNovos= 0,qtdContatosExistentes = 0;
    char letra,nomePesquisa[50];
    ContatoT *contato;
    FILE *arq;
    /*Se o arquivo for aberto com sucesso, le e exibe a quantidade de contatos existentes
    e caso seja maior que 0 passa os contatos do arquivo para um ponteiro do tipo ContatoT.
    Senao exibe uma menssagem de erro.*/
    if((arq = fopen("arquivo.bin","rb")) != NULL ){
         fread(&qtdContatosExistentes,sizeof(int),1,arq);
         printf("Contatos existentes: %d\n", qtdContatosExistentes);
         if(qtdContatosExistentes > 0){
            contato = malloc(qtdContatosExistentes * sizeof (ContatoT));
            for(i=0; i<qtdContatosExistentes; i++){
                fread((contato+i), sizeof(ContatoT), 1, arq);
            }
         }
    } else {
        printf(".Erro na abertura do arquivo.");
        }
    fclose(arq);

    while(opc != 0){
        system("color 0F");
        printf("\n\nDigite o numero correspondente a opcao desejada e pressione enter: \n");
        printf("\n1 - Inserir contatos\n");
        printf("2 - Pesquisar um contato pelo nome\n");
        printf("3 - Listar todos os contatos\n");
        printf("4 - Listar os contatos pela letra inicial\n");
        printf("5 - Mostrar os aniversariantes de determinado mes\n");
        printf("6 - Sair\n\n");
        scanf("%d", &opc);
        switch(opc){
            case 1:
                    system("cls");
                    system("color 0c");
                    printf("Informe a quantidade de contatos a inserir\n");
                    scanf("%d", &qtdContatosNovos);
                    system("cls");
                    inserirContatos(qtdContatosNovos, qtdContatosExistentes, &contato);
                    qtdContatosExistentes += qtdContatosNovos;
					printf("Contatos existentes: %d\n", qtdContatosExistentes);
                    break;
            case 2:
                    system("cls");
                    system("color 05");
                    printf("Informe o nome que deseja pesquisar\n");
                    fflush(stdin);
                    gets(nomePesquisa);
                    system("cls");
                    buscarContatoPorNome(nomePesquisa, qtdContatosExistentes, contato);
                    break;
            case 3:
                     system("cls");
                     buscarTodosContatos(qtdContatosExistentes, contato);
                     break;
            case 4:
                     system("cls");
                     system("color 05");
                     printf("Informe a letra que deseja utilizar para a busca\n");
                     scanf(" %c", &letra);
                     system("cls");
                     buscarContatosPorLetra(letra, qtdContatosExistentes, contato);
                     break;
            case 5:
                    system("cls");
                    system("color 05");
                    printf("Informe o mes que deseja utilizar para busca\n");
                    scanf("%d", &mes);
                    system("cls");
                    buscarContatosPorMes(mes, qtdContatosExistentes, contato);
                    break;
            case 6:
                    /*Se o numero de novos contatos for maior que 0 escreve a nova quantidade de contatos e os contatos no arquivo binario.
                    Senao apenas fecha o programa.*/
                    if(qtdContatosNovos != 0){
                        if((arq = fopen("arquivo.bin","wb+")) != NULL){
                            fwrite(&qtdContatosExistentes, sizeof(int), 1,arq);
                            for(i = 0; i<qtdContatosExistentes; i++){
                                fwrite((contato+i), sizeof (ContatoT), 1, arq);
                            }
                        fclose(arq);
                        printf("\nContato(s) salvo(s) com sucesso, programa finalizado!\n\n");
                        exit(0);
                        } else {
                            printf("O programa nao pode ser finalizado pois houve erros ao salvar os dados\n ");
                        }
                    }else {
                        printf("\nNenhum contato novo foi criado, programa finalizado!\n\n");
                        exit(0);
                        }
                    break;
            default:
                    printf("Opcao invalida!\n");
                    break;
        }
    }
    return 0;
}
void inserirContatos(int qtdContatosNovos, int qtdContatosExistentes, ContatoT ** contatos){
    int qtdContatosTotal = qtdContatosNovos,i;
    ContatoT * realoc;
    if(qtdContatosExistentes >0){
        qtdContatosTotal = qtdContatosExistentes+qtdContatosNovos;
        realoc = (ContatoT*) realloc(*contatos, qtdContatosTotal * sizeof(ContatoT));
        if (contatos == NULL) {printf("ERRRRRRRROOOOOOOO");}
        for(i=qtdContatosExistentes; i<qtdContatosTotal; i++){
            system("color 05");
            printf("Informe o nome do contato:\n");
            fflush(stdin);
            gets(realoc[i].nome);
            //scanf("%s", realoc[i].nome);
            printf("Informe o telefone do contato:\n");
            scanf("%s", realoc[i].telefone);
            printf("Informe o mes de aniversario do contato:\n");
            scanf("%d", &realoc[i].aniversario.mes);
            printf("Informe o dia de aniversario do contato:\n");
            scanf("%d", &realoc[i].aniversario.dia);
            system("cls");
        }
        *contatos = realoc;
    } else {
        *contatos = (ContatoT*)malloc(qtdContatosNovos * sizeof(ContatoT));
        for (i = 0; i<qtdContatosTotal;  i++){
            system("color 05");
            printf("Informe o nome do contato:\n");
            fflush(stdin);
            gets((*contatos)[i].nome);
            //scanf( "%s", (*contatos)[i].nome);
            printf("Informe o telefone do contato:\n");
            scanf( "%s", (*contatos)[i].telefone);
            printf("Informe o mes de aniversario do contato:\n");
            scanf( "%d", &(*contatos)[i].aniversario.mes);
            printf("Informe o dia de anivarsario do contato:\n");
            scanf( "%d", &(*contatos)[i].aniversario.dia);
            system("cls");

        }
    }
}
void buscarTodosContatos(int qtdContatosExistentes, ContatoT *contato){
	int i;
	printf("\t\t\t\t\t\t  **Aniversario**\n");
	printf("\tNome do contato     --      Telefone    --  Mes  --  Dia\n\n");
	for(i =0; i<qtdContatosExistentes;i++){
		printf("   %-33s", contato[i].nome);
		printf("%-17s", contato[i].telefone);
		printf("%-9d%-2d\n\n", contato[i].aniversario.mes, contato[i].aniversario.dia);
	}
}
void buscarContatoPorNome(char nome[60],int qtdContatosExistentes, ContatoT * contatos){
	int i, cont = 0;
	system("color f9");
	for(i =0; i<qtdContatosExistentes;i++){
		if(strcmp(nome, contatos[i].nome) == 0){
            cont++;
			printf("Nome: %s\n", contatos[i].nome);
			printf("Telefone: %s\n", contatos[i].telefone);
			printf("Aniversario: mes %d dia %d\n", contatos[i].aniversario.mes,contatos[i].aniversario.dia);
			i=qtdContatosExistentes;
		}
	}
	if (cont == 0){
        printf("Este nome nao existe na agenda!\n");
	}
}
void buscarContatosPorLetra(char letra, int qtdContatosExistentes, ContatoT * contato){
    int i;
    char lt = letra;
    printf("\t\t\t\t\t\t  **Aniversario**\n");
	printf("\tNome do contato     --      Telefone    --  Mes  --  Dia\n\n");
	for(i =0; i<qtdContatosExistentes;i++){
		if(toupper(lt) == toupper(contato[i].nome[0])){
        printf("   %-33s", contato[i].nome);
		printf("%-17s", contato[i].telefone);
		printf("%-9d%-2d\n\n", contato[i].aniversario.mes, contato[i].aniversario.dia);
		}
	}
}
void buscarContatosPorMes(int mes,int qtdContatosExistentes, ContatoT * contato){
    int i;
    printf("\t\t\t\t\t\t  **Aniversario**\n");
	printf("\tNome do contato     --      Telefone    --  Mes  --  Dia\n\n");
	for(i =0; i<qtdContatosExistentes;i++){
		if(mes == (contato[i].aniversario.mes)){
            printf("   %-33s", contato[i].nome);
            printf("%-17s", contato[i].telefone);
            printf("%-9d%-2d\n\n", contato[i].aniversario.mes, contato[i].aniversario.dia);
		}
	}
}

