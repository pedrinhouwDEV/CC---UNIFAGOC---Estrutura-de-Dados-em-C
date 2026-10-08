#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produto{
    int codigo;
    char nome[50];
    float preco;
    struct Produto* esquerda;
    struct Produto* direita;
} Produto;

Produto* criarNo(int codigo, char nome[50], float preco){
    Produto* novoNo = (Produto*)malloc(sizeof(Produto));
    if(novoNo == NULL){
        printf("Erro de alocacao de memoria");
        return NULL;
    }
    strcpy(novoNo->nome, nome);
    novoNo->codigo = codigo;
    novoNo->preco = preco;
    novoNo->direita = NULL;
    novoNo->esquerda = NULL;
    return novoNo;
}

Produto* inserirProduto(Produto* raiz, int codigo, char nome[50], float preco){
    if(raiz == NULL){
        return criarNo(codigo, nome, preco);
    }
    if(codigo < raiz->codigo){
        raiz->esquerda = inserirProduto(raiz->esquerda, codigo, nome, preco);
    }else if(codigo > raiz->codigo){
        raiz->direita = inserirProduto(raiz->direita, codigo, nome, preco);
    }else{
        printf("Numero ja existe!\n");
    }
    return raiz;
}

void liberarArvore(Produto* raiz){
    if(raiz != NULL){
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

Produto* buscarProduto(Produto* raiz, int codigo){
    if(raiz == NULL){
        return NULL;
    }
    if(raiz->codigo == codigo){
        return raiz;
    }
    if(codigo < raiz->codigo){
        return buscarProduto(raiz->esquerda, codigo);
    }else{
        return buscarProduto(raiz->direita, codigo);
    }
}

void exibirOrdem(Produto* raiz){
    if(raiz != NULL){
        exibirOrdem(raiz->esquerda);
        printf("\nCodigo do produto: %d |", raiz->codigo);
        printf("\nNome do produto: %s |", raiz->nome);
        printf("\nPreco do produto: %.2f |", raiz->preco);
        exibirOrdem(raiz->direita);
    }
}

Produto* EncontrarMaisCaro(Produto* raiz){
    if(raiz == NULL){
        return NULL;
    }
    Produto* maior = raiz;
    Produto* esquerda = EncontrarMaisCaro(raiz->esquerda);
    Produto* direita = EncontrarMaisCaro(raiz->direita);

    if(esquerda != NULL && esquerda->preco > maior->preco){
        maior = esquerda;
    }
    if(direita != NULL && direita->preco > maior->preco){
        maior = direita;
    }
    return maior;
}

Produto* EncontrarMaisBarato(Produto* raiz){
    if(raiz == NULL){
        return NULL;
    }
    Produto* menor = raiz;
    Produto* esquerda = EncontrarMaisBarato(raiz->esquerda);
    Produto* direita = EncontrarMaisBarato(raiz->direita);
    if(esquerda != NULL && esquerda->preco < menor->preco){
        menor = esquerda;
    }
    if(direita != NULL && direita->preco < menor->preco){
        menor = direita;
    }
    return menor;
}

int main(){
    Produto* raiz = NULL;
    int opcao;
    int code;
    int numBusca;
    char nomeD[50];
    float preco;
    do{
        printf("\n----------------------\n");
        printf("ESCOLHA UMA OPCAO: \n");
        printf("1 - Inserir Produto\n");
        printf("2 - Buscar Produto\n");
        printf("3 - Exibir em ordem\n");
        printf("4 - Encontrar mais caro\n");
        printf("5 - Encontrar mais barato\n");
        printf("6 - Sair\n");
        printf("----------------------\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("Insira o codigo do produto: \n");
                scanf("%d", &code);
                getchar();
                printf("Insira o nome do produto: \n");
                fgets(nomeD, 50, stdin);
                nomeD[strcspn(nomeD, "\n")] = '\0';
                printf("Insira o preco do produto: \n");
                scanf("%f", &preco);
                getchar();
                raiz = inserirProduto(raiz, code, nomeD, preco);
                break;
            case 2:
                printf("Insira o codigo do produto que gostaria de buscar: ");
                scanf("%d", &numBusca);
                Produto* Encontrado = buscarProduto(raiz, numBusca);
                if(Encontrado != NULL){
                    printf("Produto encontrado: %d | %s | %.2f | \n", Encontrado->codigo, Encontrado->nome, Encontrado->preco);
                }else{
                    printf("\nValor %d nao encontrado", numBusca);
                }
                break;
            case 3:
                exibirOrdem(raiz);
                break;
            case 4:
                if(raiz == NULL){
                    printf("Lista vazia!\n");
                }else{
                    Produto* maisCaro = EncontrarMaisCaro(raiz);
                    printf("Produto mais caro: %d %s %.2f", maisCaro->codigo, maisCaro->nome, maisCaro->preco);
                }
                break;
            case 5:
                if(raiz == NULL){
                    printf("Lista vazia!\n");
                }else{
                    Produto* MaisBarato = EncontrarMaisBarato(raiz);
                    printf("Produto mais barato: %d %s %.2f", MaisBarato->codigo, MaisBarato->nome, MaisBarato->preco);
                }
                break;
            case 6:
                printf("Saindo...\n");
                liberarArvore(raiz);
                break;
        }
    }while(opcao != 6);
}