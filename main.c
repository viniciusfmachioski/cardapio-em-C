#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define TAMANHO 25;
int posicaoindice = 0;
int posicaoindicepedido = 0;
struct estrutura_cardapio
{
    int codigoitem;
    char nomeitem[40];
    char descricao[255];
    float valoritem;
};

struct estrutura_cardapio cardapio[20];

struct estrutura_pedido
{
    int codigoitem;
    int quantidade;
    char nomeitem[40];
    float valoritem;
    float valortotalitem;
};

struct estrutura_pedido pedido[10];

void realizarpedido()
{


    int opcpedido;
    int posicaoindicepedido;
    while(opcpedido!=9)
    {
        printf("\n------------------------------------");
        printf("\n| Realizar Pedido                  |");
        printf("\n------------------------------------");
        printf("\n(1) Visualizar Cardapio ");
        printf("\n(2) Adicionar Item ao Pedido");
        printf("\n(3) Visualizar Pedido");
        printf("\n(4) Mostrar Total");
        printf("\n(9) Sair");
        printf("\n\nEscolha uma Opção: ");
        fflush(stdin);
        scanf("%d",&opcpedido);
        switch(opcpedido)
        {
            case 1:
                listarcardapio();
                break;
            case 2:
                insereitempedido(posicaoindicepedido);
                posicaoindicepedido++;
                break;
            case 3:
                listarpedido();
//                visualizapedido();
                break;
            case 4:
                calculartotal();
                break;
        }
    }

}

void insereitempedido(int indice)
{
    float valoraux;
    char decisao;
    int codigoitempedido;
    char nomeitemaux[40];
    float valoritemaux;
    int quantidade;

    printf("\nCódigo do Item: ");
//    setbuf(stdin, 0);
    fflush(stdin);
    scanf("%d",&codigoitempedido);
    int retornobusca;
    retornobusca = buscaritem(codigoitempedido);
    if(retornobusca >= 0)
    {
        printf("\n------------------------------------");
        printf("\n| Item Encontrado no cardapio      |");
        printf("\n------------------------------------");

        printf("\n> Nome do Item: %-25s\n> Descrição do Item: %-40s",cardapio[retornobusca].nomeitem, cardapio[retornobusca].descricao);
        printf("\n------------------------------------");
        printf("\nDeseja inserir Item (s ou n): ");
        fflush(stdin);
        scanf("%c",&decisao);
        printf("------------------------------------");
        if((decisao =='s') || (decisao == 'S'))
        {
            pedido[posicaoindicepedido].codigoitem = codigoitempedido;
            pedido[posicaoindicepedido].valoritem = cardapio[retornobusca].valoritem;
            strcpy(pedido[posicaoindicepedido].nomeitem,cardapio[retornobusca].nomeitem);
        }
        else if ((decisao =='n') || (decisao == 'N'))
        {
            printf("\nProduto não Inserido!");
            return;
        }
        else
        {
            printf("\nOpção Inválida!");
            return;
        }

        //pedido[0].nomeitem = nomeitemaux;


    }
    else
    {
        printf("\n------------------------------------");
        printf("\n| Item Não Encontrado no cardapio  |");
        printf("\n------------------------------------");
        return;

    }
    printf("\n\n> Quantidade do Item: ");
    scanf("%d",&pedido[posicaoindicepedido].quantidade);
    pedido[posicaoindicepedido].valortotalitem = (float) pedido[posicaoindicepedido].valoritem*pedido[posicaoindicepedido].quantidade;
    posicaoindicepedido++;


}

void listarpedido()
{
    int i;
    printf("--------------------------------------------------------------------------------------------------------------\n| Código Item\t| Nome Item                                 | Valor Item\t| Quantidade\t| Total Item |\n--------------------------------------------------------------------------------------------------------------");

    for(i=0;i<10;i++)
    {
        printf("\n|%12d \t| %-40s  | %05.2f     \t|\t%5d\t| R$%-09.2f|",pedido[i].codigoitem,pedido[i].nomeitem,pedido[i].valoritem,pedido[i].quantidade,pedido[i].valortotalitem);
        printf("\n--------------------------------------------------------------------------------------------------------------");
    }
    printf("\n");
}

void calculartotal()
{
    float total;
    total = 0;
    int i;
    for(i=0;i<10;i++)
    {
        total = total + pedido[i].valortotalitem;
    }
    printf("\n------------------------------------");
    printf("\n| Total do Pedido: R$%6.2f        | ",total);
    printf("\n------------------------------------\n");
    return;

}

int buscaritem(int codigoitem)
{
    int encontrou = -1;
    char *nomeaux;

    int j=0;
    for(j=0;j<25;j++)
    {
        if(codigoitem == cardapio[j].codigoitem)
        {
            encontrou = j;
            return(j);
        }
    }
    return(encontrou);
}

void insereitem(int indice)
{
    float valoraux;
    printf("\n-----------------------------\nIncluir Item\n-----------------------------");
    printf("\nCódigo do Item: ");
    fflush(stdin);
    scanf("%d",&cardapio[indice].codigoitem);

    printf("\nNome do Item: ");
    fflush(stdin);
    gets(cardapio[indice].nomeitem);

    printf("\nDescrição do Item: ");
    fflush(stdin);
    gets(cardapio[indice].descricao);

    printf("\nValor do Item: ");
    fflush(stdin);
    scanf("%f",&cardapio[indice].valoritem);


    if(cardapio[indice].codigoitem != ' '){
    printf("\n-------Item digitado-------");
    printf("\nCódigo do Item: %d",cardapio[indice].codigoitem);
    printf("\nNome do Item: %s",cardapio[indice].nomeitem);
    printf("\nDescrição do Item: %s",cardapio[indice].descricao);
    printf("\nValor do Item: R$%5.2f\n",cardapio[indice].valoritem);
    }

}

listarcardapio()
{
    int i;
    printf("   ---------------------------------------------------------------------------------------\n   |  Código do Item \t| Nome do Item                                \t| Valor do Item  |\n   ---------------------------------------------------------------------------------------");
    for(i=0; i<25; i++)
    {
        printf("\n%-2d |  %14d\t| %-40s  \t| R$%5.2f\t |",i+1,cardapio[i].codigoitem, cardapio[i].nomeitem, cardapio[i].valoritem);
    }
    printf("\n   ---------------------------------------------------------------------------------------\n");

}

void gravarcardapio()
{
    FILE *in;
    in = fopen("cardapio.txt","w");
    int i;
    if(in == NULL)
    {
        printf("Problema na Gravação do Arquivo");
        return;
    }
    for(i=0;i<posicaoindice;i++)
    {
        if(cardapio[i].codigoitem == 0)
        {
        }
        else
        {
            fwrite(&cardapio[i],1,sizeof(cardapio[i]),in);
        }
    }
    fclose(in);
}

void removeritem()
{
    int item,i;
    printf("\nQual é o Código do Item que você quer Remover?: ");
    scanf("%d",&item);
    for(i=0;i<25;i++)
    {
        if(cardapio[i].codigoitem == item)
        {
            printf("Foi localizado o Item a ser Removido. O número do Indice que ele está inserido é: %d", i+1);
            cardapio[i].codigoitem = 0;
            cardapio[i].valoritem = 0;
            strcpy(cardapio[i].descricao,"");
            strcpy(cardapio[i].nomeitem, "");
            return;
        }
    }

}

void inicializarestrutura()
{
    int i;

    for(i=0;i<25;i++)
    {
        cardapio[i].codigoitem = 0;
        cardapio[i].valoritem = 0;
        strcpy(cardapio[i].descricao,"");
        strcpy(cardapio[i].nomeitem,"");
    }
    posicaoindice = 0;
    return;
}

void lercardapio()
{
    FILE *in;
    int ret = 0;
    char linha[102];
    char linhaant[102];
    char codigoitemaux[12];
    char valoritemaux[12];
    in = fopen("cardapio.txt", "r+");
    int i;
    i=0;
    if(in == NULL)
    {
        printf("Problema na Leitura do Arquivo!");
        return;
    }
    inicializarestrutura();
    while(ret != EOF)
    {
        ret = fread(&cardapio[i],sizeof(cardapio[1]),1,in);

        printf("\n%dº Item",i+1);
        printf("\n%12d",cardapio[i].codigoitem);
        printf("\n%-40s",cardapio[i].nomeitem);
        printf("\n%-100s",cardapio[i].descricao);
        printf("\n%5.2f\n",cardapio[i].valoritem);

        if(cardapio[i].codigoitem == 0)
        {
            break;
        }

        i = i + 1;
        //printf("\nPressione uma tecla para continuar");
        //getch();
    }
    posicaoindice = i;
    printf("\nPosição Indice: %d", posicaoindice);
    fclose(in);
}

int main(void){

    int indice=0;
    setlocale(LC_ALL, "Portuguese");
    int opcao;

    while(opcao != 9){
        printf("\n-----------------------------\nOpções...\n-----------------------------\n");
        printf("\n(1) Incluir Item");
        printf("\n(2) Remover Item");
        printf("\n(3) Listar Cardápio");
        printf("\n(4) Gravar Cardápio no Arquivo");
        printf("\n(5) Ler o Arquivo do Cardápio");
        printf("\n(6) Realizar Pedido");
        printf("\n(9) Sair");

        printf("\n\nDigite a opção escolhida: ");
        fflush(stdin);
        scanf("%d",&opcao);
        fflush(stdin);

        if(opcao == 1 || opcao == 2 || opcao == 3 || opcao == 4 || opcao == 5 || opcao == 6 || opcao == 9)
        {
            switch(opcao){
            case 1:
                insereitem(posicaoindice);
                posicaoindice++;
                break;
            case 2:
                removeritem(0);
                break;
            case 3:
                listarcardapio();
                break;
            case 4:
                gravarcardapio();
                break;
            case 5:
                lercardapio();
                break;
            case 6:
                realizarpedido();
                break;
            }
        }
        else
        {
            printf("\nOpção Inválida!");
        }

    }
}
