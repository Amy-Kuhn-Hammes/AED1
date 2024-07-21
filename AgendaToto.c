#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void **pBuffer;

/*
===========================================================
resize()

Usa realloc para extender a memoria alocada para o pBuffer
==========================================================
*/
void resize() {
    //adiciona espaço para mais 10 pessoas, para que assim não precise 
    // ser feito realloc para toda pessoa adicionada
    pBuffer[2] += 30;
    pBuffer = realloc(pBuffer, sizeof(void*)* (int) pBuffer[2]);
}

/*
=================================================
push()

Insere um registro na agenda em ordem alfabetica
=================================================
*/
void push() {
    //checa se tem espaço alocado, se não, aloca mais
    if(pBuffer[3] +3>= pBuffer[2]) {
        resize();
    }
    printf("Nome: ");
    scanf("\n%[^\n]s", &pBuffer[0]);
    pBuffer[4] = 6;
    // Buscas pos para inserir
    while(1) {
        if(pBuffer[4] >= pBuffer[3] || strcmp(&pBuffer[(int)pBuffer[4]], &pBuffer[0]) > 0) {
            //copia os outros registros para frente
            memcpy(&pBuffer[((int)pBuffer[4])+3], &pBuffer[((int)pBuffer[4])],sizeof(void *)*(int)pBuffer[3]-(6+(int)pBuffer[4]+3));
            pBuffer[(int)pBuffer[4]] = pBuffer[0];
            break;
        }
        pBuffer[4]+=3;
    }
    
    printf("Idade: ");
    scanf("%d", &pBuffer[(int)pBuffer[4]+1]);
    printf("Email: ");
    scanf("%s", &pBuffer[(int)pBuffer[4]+2]);
    pBuffer[1]++;
    pBuffer[3]+=3;
}

/*
==================================
findAll()

Monstra na tela todos os registros
==================================
*/
void findAll() {
    printf("Aqui está todos os %d registros salvos na agenda: \n\n", pBuffer[1]);
    for( pBuffer[4] = 0; pBuffer[4] < pBuffer[1]; pBuffer[4]++ ) {
        printf("Nome: %s\nIdade: %d\nEmail: %s\n\n", &pBuffer[6+(int)pBuffer[4]*3], pBuffer[6+(int)pBuffer[4]*3+1],&pBuffer[6+(int)pBuffer[4]*3+2]);
    }
}

/*
=================================================
findByPos

Mostra na tela um registro pela posição na agenda
=================================================
*/
void findByPos() {
    if( pBuffer[1] == 0 ) {
        printf("A lista está vazia\n");
        return 0;
    }
    do {
        printf("Digite a posição da pessoa: ");
        scanf("%d", &pBuffer[4]);
    } while( pBuffer[4]<0 || pBuffer[4]>=pBuffer[1] );
    printf("Nome: %s\nIdade: %d\nEmail: %s\n\n", &pBuffer[6+(int)pBuffer[4]*3], pBuffer[6+(int)pBuffer[4]*3+1],&pBuffer[6+(int)pBuffer[4]*3+2]);
}

/*
====================================
findByNome

Mostra na tela um registro pelo nome
====================================
*/
void findByNome() {
    if(pBuffer[1] == 0) {
        printf("A lista está vazia\n");
        return 0;
    }
    printf("Digite o nome da pessoa:\n");
    scanf("%s", &pBuffer[0]);
    for(pBuffer[4] = 0; pBuffer[4] < pBuffer[1]; pBuffer[4]++) {
        if(strcmp(&pBuffer[6+(int)pBuffer[4]*3], &pBuffer[0]) == 0) {
            printf("Posição: %d\nNome: %s\nIdade: %d\nEmail: %s\n\n", pBuffer[4], &pBuffer[6+(int)pBuffer[4]*3], pBuffer[6+(int)pBuffer[4]*3+1],&pBuffer[6+(int)pBuffer[4]*3+2]);
            return pBuffer[4];
        }
    }
    printf("Pessoa chamada %s não consta na lista\n", &pBuffer[0]);
}


/*
=============================
Pop()

Remove um item de uma posição
=============================
*/
void pop() {
    if(pBuffer[1] == 0) {
        printf("A lista está vazia\n");
        return 0;
    }
    printf("Qual posição deseja remover?\n");
    scanf("%d", &pBuffer[5]);
    //remove na frente da fila e armaza apos o final da fila
    for(pBuffer[4] = 0; pBuffer[4] < pBuffer[5];pBuffer[4]++) {
        if((int)pBuffer[3]+(int)pBuffer[4]*3 < (int)pBuffer[2]) {
            resize();
        }
        memcpy(&pBuffer[(int)pBuffer[3]+(int)pBuffer[4]*3],&pBuffer[6],sizeof(void *) * 3);
        memcpy(&pBuffer[6], &pBuffer[8], sizeof(void *) * 3 * (int)pBuffer[1]);
    }
    //remove o ser a removido
    memcpy(&pBuffer[6], &pBuffer[8], sizeof(void *) * 3 * (int)pBuffer[1]);
    //remove do armazenamento e reinsere no lugar
    for(pBuffer[4] = 0; pBuffer[4] < pBuffer[5];pBuffer[4]++) {
        memcpy(&pBuffer[8], &pBuffer[6], sizeof(void *) * 3 * (int)pBuffer[1]);
        memcpy(&pBuffer[6], &pBuffer[(int)pBuffer[3]+((int)pBuffer[5]-1 - (int)pBuffer[4])*3],sizeof(void *) * 3);
    }

    //move a memoria para frente
    //memcpy(&pBuffer[6+((int)pBuffer[4]*3)], &pBuffer[6+((int)pBuffer[4]*3)+3],sizeof(void *)*(int)pBuffer[3]-(6+(int)pBuffer[4]+3));
    pBuffer[1]--;
    pBuffer[3]-=3;
}

int main() {
    //as 6 primeiras pocições são alocadas para variaveis, o resto é a agenda
    //operation, len, size, tail, i, aux, pessoas
    pBuffer = (void **) malloc(sizeof(void*)*36);
    pBuffer[1] = 0;
    pBuffer[2] = 36;
    pBuffer[3] = 6; 
    pBuffer[5] = NULL;
    do {
        printf("\nDigite operação:\n1- Adicionar Pessoa (Nome, Idade, email)\n2- Remover Pessoa\n3- Buscar Pessoa\n4- Listar todos\n5- Sair\n");
        scanf("%d", &pBuffer[0]);
    
        switch ( (int) pBuffer[0] ) {
        case(1):
            push();
            break;
        case(2):
            pop();
            break;
        case(3):
            printf("Deseja buscar por posição(1) ou por nome(2)?\n");
            do {
                scanf("%d", &pBuffer[5]);
            } while(pBuffer[5] != 1 && pBuffer[5] != 2);
            if( pBuffer[5] == 1 ) {
                findByPos();
            } else {
                findByNome();
            }
            break;
        case(4):
            findAll();
            break;
        case(5):
            break;
        default:
            printf("Digite um valor de entrada valido\n");
            break;
        }
    }while( (int)pBuffer[0] != 5 );
    free( pBuffer );
    return 1;
}