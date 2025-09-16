#include <stdio.h>
#include<ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <Windows.h>
#include <string.h>
#define MAX 101
#define TEL 21
#define CPF 20
#define SEN 11
#define FE 10
#define VERMELHO "\033[1;31m"
#define VERDE "\033[1;32m"
#define AZUL "\033[34m"
#define RESET "\033[0;0m"
//Acho que vou fazer uma locadora de filmes.
//precisa ter cadastro de cliente também.
//acho que to maluco

//Para remover filmes e clientes acabei usando realloc, ai meio que perdeu o sentido ter o campo status nas structs. 

typedef struct Cliente{
    int id;
    bool status;
    char nome[MAX];
    char telefone[TEL];
    char cpf[CPF];
    char endereco[MAX];
    int chave;

} TCliente;

typedef struct Filme {
    int id;
    bool status;
    char faixaEtaria[FE];
    char nome[MAX];
    char categoria[MAX];
    int quantidade;
    float preco;

} TFilme;
void toLowerCase(char *str) { 
	int i; 
	for (i = 0; str[i] != '\0'; i++) { 
		str[i] = tolower((unsigned char) str[i]); 
	} 
}

void cortaFinal(char *s){
    if (!s) return;
    size_t len = strlen(s);
    if (len > 0 && s[len-1] == '\n') s[len-1] = '\0';
}

//--------------------------Clientes-------------------------------------------------//
int imprimeMenuClientes(){
    system("cls");
    int op;

    printf(AZUL"--Menu Clientes--"RESET);
    printf("\n\n1-Cadastrar cliente");
    printf("\n2-Pesquisar cadastro");
    printf("\n3-Exibir lista de cadastros");
    printf("\n4-Atualizar cadastro");
    printf("\n5-Remover cadastro");
    printf("\n6-Sair");
    printf("\n\nOpção: ");
    scanf("%d", &op);
    getchar();

    return op;
}

void cadastraCliente(TCliente *cliente, int pos){
    int i;
    system("cls");
    cliente[pos].status = true;
    cliente[pos].id = pos;

    cliente[pos].chave = 0;
    printf(AZUL"--Cadastro Cliente--\n\n"RESET);

    printf("Nome: ");
    fgets(cliente[pos].nome, MAX-1, stdin);
    cortaFinal(cliente[pos].nome);

    printf("\nTelefone: ");
    fgets(cliente[pos].telefone, TEL-1, stdin);
    cortaFinal(cliente[pos].telefone);

    printf("\nCPF: ");
    fgets(cliente[pos].cpf, CPF-1, stdin);
    cortaFinal(cliente[pos].cpf);

    printf("\nEndereco: ");
    fgets(cliente[pos].endereco, MAX-1, stdin);
    cortaFinal(cliente[pos].endereco);

    //A condição de '\0' significa chegar ao fim do cpf
    for(i = 0; cliente[pos].cpf[i] != '\0'; i++){
            if(cliente[pos].cpf[i] >= '0' && cliente[pos].cpf[i] <= '9'){
                cliente[pos].chave += (cliente[pos].cpf[i] - '0'); // conversão marota
            }
    }

    printf(VERDE"\n\nCadastro realizado com sucesso!"RESET);
    Sleep(500);

}

//Deve ser pelo CPF
void atualizaCliente(TCliente *cliente, int m){
    system("cls");

    int i, op, sair, chave = 0;
    char resposta[CPF];
    bool encontrou = false;

    printf(AZUL"\n--Atualizar dados do Clinete--"RESET"\n\nDigite o CPF do cliente: ");
    fgets(resposta, CPF - 1, stdin);
    cortaFinal(resposta);

    for(i = 0; resposta[i]!= '\0'; i++){
            if(resposta[i] >= '0' && resposta[i] <= '9'){
                chave += (resposta[i] - '0'); // conversão marota
            }
    }

    for(i = 0; i < m; i++){
        if(chave == cliente[i].chave && cliente[i].status){
            printf(VERDE"\n\nCadastro encontrado!"RESET);
            encontrou = true;
            break;
        }
    }

    if(!encontrou){
        printf(VERMELHO"\n\nCadastro do cliente não foi encontrado!"RESET);
        return;
    }
    Sleep(500);
    system("cls");

    op = 0;

    do{
       printf("Alterar: \n1-Nome\n2-CPF\n3-Telefone\n4-Endereço\n\nOpção: ");
       scanf("%d", &op);
       getchar();

       switch(op){

        case 1:
            printf("\nNome: ");
            fgets(cliente[i].nome, MAX-1, stdin);
            cortaFinal(cliente[i].nome);
            break;

        case 2:
            printf("\nCPF (apenas números): ");
            fgets(cliente[i].cpf, CPF-1, stdin);
            cortaFinal(cliente[i].cpf);
            break;

        case 3:
            printf("\nTelefone: ");
            fgets(cliente[i].telefone, TEL-1, stdin);
            cortaFinal(cliente[i].telefone);
            break;

        case 4:
            printf("\nEndereço: ");
            fgets(cliente[i].endereco, MAX-1, stdin);
            cortaFinal(cliente[i].endereco);
            break;

        default:
            printf("\nOpção inválida!");
            Sleep(500);
            break;
       }

       printf("\n\nDeseja alterar outro campo? (1-Sim/2-Não)\nOpção: ");
       scanf("%d", &sair);
       getchar();

       Sleep(500);
       system("cls");

    } while (sair != 2);

    Sleep(500);
}

//Deve ser pelo CPF
void removeCliente(TCliente **cliente, int *m){
    system("cls");

    int chave = 0, i,j;
   
    char cpf[CPF];

    printf(AZUL"--Remover cliente--"RESET);
    printf("\n\nDigite o cpf do cliente: ");
    fgets(cpf, CPF-1, stdin);
    cortaFinal(cpf);

    for(i = 0; cpf[i] != '\0'; i++){

        if(cpf[i] >='0' && cpf[i] <= '9'){
            chave += (cpf[i] - '0');
        }
    }

    for(i = 0; i < *m; i++){
        if(chave == (*cliente)[i].chave && (*cliente)[i].status){
            for(j = i; j < *m - 1; j++){
            	//pega o cliente da posição que queremos remover e transformamos ele no proximo
            	//ai com cada iteração ele faz o j atual se transformar no proximo
            	//no fim vai ter dois iguais, mas o realloc m-- remove o duplicado
                (*cliente)[j] = (*cliente)[j + 1];
                (*cliente)[j].id = j;
            }
            (*m)--;
            *cliente = realloc(*cliente, (*m) * sizeof(TCliente));
            printf(VERDE"\n\nCadastro do cliente apagado com sucesso!\n\n"RESET);
            system("pause");
            return;
        }
    }

    printf(VERMELHO"\n\nCadastro não encontrado ou inativo!"RESET);
    Sleep(500);
}

void imprimeTodosCli(TCliente *cliente, int m){
    int i;
    system("cls");
    printf(AZUL"--Lista de clientes--\n\n"RESET);
    printf("\n---------------------------------------------------\n");

    for(i = 0; i < m; i++){
        if(cliente[i].status){
            printf("\nID: %d", cliente[i].id);
            printf("\nNome: %s", cliente[i].nome);
            printf("\nCPF: %s", cliente[i].cpf);
            printf("\nTelefone: %s", cliente[i].telefone);
            printf("\nEndereço: %s", cliente[i].endereco);
            printf("\n---------------------------------------------------\n");
        }
    }

    printf("\n\n");
    system("pause");
}

//Deve ser pelo CPF
void pesquisaCliente(TCliente *cliente, int m){
    system("cls");

    bool encontrou = false;
    int i, chave = 0;
    char cpf[MAX];

    printf(AZUL"--Pesquisar cliente--"RESET"\n\nDigite o CPF do cliente: ");
    fgets(cpf, MAX-1, stdin);

    for(i = 0; cpf[i] != '\0'; i++){

        if(cpf[i] >='0' && cpf[i] <= '9'){
            chave += (cpf[i] - '0');
        }
    }

    for(i = 0; i < m; i++){

        if(chave == cliente[i].chave && cliente[i].status){
            encontrou = true;
            break;
        }

    }
    if(!encontrou){
        printf(VERMELHO"Cliente não encontrado!\n\n"RESET);
        system("pause");
        return;
    }

    printf("\n\nID: %d", cliente[i].id);
    printf("\nNome: %s", cliente[i].nome);
    printf("\nCPF: %s", cliente[i].cpf);
    printf("\nTelefone: %s", cliente[i].telefone);
    printf("\nEndereço: %s", cliente[i].endereco);

    printf("\n\n");
    system("pause");
}

void executaMenuCliente(int op, int *m, TCliente **cliente){

    switch(op){

        case 1:

            (*m)++;
            if(*m == 1){
                *cliente = (TCliente *) malloc(sizeof(TCliente));
            } else {
                *cliente = (TCliente *) realloc(*cliente, *m * sizeof(TCliente));
            }
            if(*cliente == NULL){
                printf("Erro em alocação de memmória\n");
                exit(1);
            }
            cadastraCliente(*cliente, *m-1);
            break;

        case 2:
            if(*m == 0){
               printf(VERMELHO"\n\nNão há cadastro de clientes!"RESET);
               Sleep(500);

               break;
           }
            pesquisaCliente(*cliente, *m);
            break;

        case 3:

            if(*m == 0){
                printf(VERMELHO"\n\nNão há cadastro de clientes!"RESET);
                Sleep(500);
                break;
            }
            imprimeTodosCli(*cliente, *m);
            break;

        case 4:

            if(*m == 0){
                printf(VERMELHO"\n\nNão há cadastro de clientes!"RESET);
                Sleep(500);
                break;
            }
            atualizaCliente(*cliente, *m);
            break;

        case 5:

            if(*m > 0){
                removeCliente(cliente, m);
                Sleep(500);
                break;
            }
            printf(VERMELHO"\n\nNão há cadastro de clientes!"RESET);
            Sleep(500);
            break;

        case 6:
            printf(VERDE"\n\nRetornando ao menu principal!"RESET);
            Sleep(500);
            break;

        default:
            printf(VERMELHO"\n\nOpção inválida!"RESET);
            Sleep(500);
            break;
    }
}

void menuClientes(int *m, TCliente **cliente){
    int op;
    do{
        op = imprimeMenuClientes();
        executaMenuCliente(op,m,cliente);
    } while (op!=6);
}

//--------------------------Filmes-------------------------------------------------//

int imprimeMenuFilmes(){
    system("cls");
    int op;

    printf(AZUL"--Menu Filmes--\n\n"RESET);
    printf("1-Cadastrar filme");
    printf("\n2-Pesquisar filme");
    printf("\n3-Exibir lista de filmes");
    printf("\n4-Atualizar filme");
    printf("\n5-Remover filme");
    printf("\n6-Alugar filme");
    printf("\n7-Sair");
    printf("\n\nOpção: ");
    scanf("%d", &op);
    getchar();

    Sleep(500);
    return op;
}

void cadastraFilme(TFilme *filme, int pos){
    system("cls");
    filme[pos].id = pos;
    filme[pos].status = true;

    printf(AZUL"--Cadastrar filme--"RESET"\n\nNome do filme: ");
    fgets(filme[pos].nome, MAX - 1, stdin);
    cortaFinal(filme[pos].nome);

    printf("\nCategoria do filme: ");
    fgets(filme[pos].categoria, MAX-1, stdin);

    printf("\nFaixa Etária: ");
    fgets(filme[pos].faixaEtaria, FE-1, stdin);

    printf("\nPreço: ");
    scanf("%f", &filme[pos].preco);
    getchar();

    printf("\nQuantidade disponível: ");
    scanf("%d", &filme[pos].quantidade);
    getchar();

    printf(VERDE"\n\nCadastro realizado com sucesso!"RESET);
    Sleep(500);

}

void imprimeTodos(TFilme *filme, int n){
    system("cls");
    printf(AZUL"--Lista de filmes--\n\n"RESET);
    int i;

    printf("\n---------------------------------------------------\n");
    for(i = 0; i < n; i++){
        Sleep(500);
        if(filme[i].status){
            printf("ID: %d\n", filme[i].id);
            printf("\nNome: %s", filme[i].nome);
            printf("\nCategoria:  %s", filme[i].categoria);
            printf("\nFaixa Etária: %s", filme[i].faixaEtaria);
            printf("\nPreço: %.2f\n", filme[i].preco);
            printf("\nQuantidade disponível: %d", filme[i].quantidade);
            printf("\n---------------------------------------------------\n");
            }
    }
    printf("\n\n");
    system("pause");

}

void pesquisaFilme(TFilme *filme,int *n){
    system("cls");
    bool encontrado = false;
    int i;
    char resposta[MAX];
    char nomeMin[MAX];

    printf(AZUL"--Pesquisar filme--"RESET"\n\nDigite o nome do filme: ");
    fgets(resposta, MAX-1, stdin);
    cortaFinal(resposta);
    //To fazendo essa fuleragem pq quero comparar o nome do filme como condição na pesquisa
    //MAS não quero que seja "case sensitive" pro usuario poder digitar o nome do jeito que quiser
    toLowerCase(resposta);


    for(i = 0; i < *n; i++){

        strcpy(nomeMin, filme[i].nome);
		toLowerCase(nomeMin);
        if((strcmp(resposta, nomeMin) == 0) &&filme[i].status == true){

            encontrado = true;
            break;
        }
    }

    if(!encontrado){
        printf(VERMELHO"\nFilme não encontrado!\n\n"RESET);
        system("pause");
        return;
    }
    printf("\n\nID: %d", filme[i].id);
    printf("\nNome: %s", filme[i].nome);
    printf("\nCategoria:  %s", filme[i].categoria);
    printf("\nFaixa Etária: %s", filme[i].faixaEtaria);
    printf("\nPreço: %.2f", filme[i].preco);
    printf("\nQuantidade disponível: %d\n\n", filme[i].quantidade);

    system("pause");
}

void removerFilme(TFilme **filme, int *n){
    system("cls");
    int id, i;

    printf(AZUL"--Remover filme--"RESET"\n\nDigite o ID do filme: ");
    scanf("%d", &id);
    getchar();

    if(id < 0 || id >= *n){
        printf(VERMELHO"\n\nID inválido!"RESET);
        Sleep(500);
        return;
    }
    
    for(i = id; i < *n - 1; i++){
        (*filme)[i] = (*filme)[i+1];
        (*filme)[i].id = i;
    }

    (*n)--;
    (*filme) = realloc(*filme, (*n) * sizeof(TFilme));    

    printf(VERDE"\nCadastro de filme apagado!"RESET);
    Sleep(500);

}

void atualizaFilme(TFilme *filme, int n){
    system("cls");
    int id, op,sair;

    printf(AZUL"\n--Atualizar filme--"RESET"\n\nDigite o ID do filme: ");
    scanf("%d", &id);
    getchar();

    if(id < 0 || id >=n || !filme[id].status){
        printf(VERMELHO"\n\nID inválido!"RESET);
        atualizaFilme(filme,n);
        return;
    }
    Sleep(500);
    system("cls");

    do{
        printf("\nAlterar: \n1-Nome\n2-Categoria\n3-Faixa Etária\n4-Preço\n5-Quantidade disponível\nOpção: \n");
        scanf(" %d", &op);
        getchar();

        switch(op){

            case 1:
                printf("Nome: ");
                fgets(filme[id].nome, MAX-1, stdin);
                printf(VERDE"\n\nNome alterado com sucesso!"RESET);
                break;

            case 2:
                printf("Categoria: ");
                fgets(filme[id].categoria, MAX - 1, stdin);
                printf(VERDE"\n\nCategoria alterada com sucesso!"RESET);
                break;

            case 3:
                printf("Faixa etária: ");
                fgets(filme[id].faixaEtaria, 5, stdin);
                printf(VERDE"\n\nFaixa etária alterada com sucesso!"RESET);
                break;

            case 4:
                printf("Preço: ");
                scanf("%f", &filme[id].preco);
                getchar();
                printf(VERDE"\n\nPreço alterado com sucesso!"RESET);
                break;

            case 5:
                printf("Quantidade disponível: ");
                scanf("%d", &filme[id].quantidade);
                printf(VERDE"\n\nQuantidade alterada com sucesso!"RESET);
                getchar();
                break;
        }
            printf("\n\nDeseja alterar outro campo? (1-Sim/2-Não)\nOpção: ");
            scanf("%d", &sair);
            getchar();
            system("cls");

    } while(sair != 2);
    Sleep(500);
}

void alugaFilme(TFilme *filme, TCliente *cliente, int n, int m){
    system("cls");

    bool encontrou = false;
    int i, chave = 0, id;
    char cpf[CPF];

    printf(AZUL"--Alugar filme--\n\n"RESET"Entre com o cpf do cliente: ");
    fgets(cpf, CPF-1, stdin);
    cortaFinal(cpf);
    //não tive coragem de ir atrás de tabela hash pra isso
    //entao só somei cada número do cpf do cliente e chamei de chave

    for(i = 0; cpf[i] != '\0'; i++){
        if (cpf[i] >= '0' && cpf[i] <= '9'){
            chave += (cpf[i] - '0');  // conversão marota char '0'-'9' em int 0-9
        }
    }

    for(i = 0; i < m; i++){

        if(cliente[i].chave == chave){
            printf(VERDE"\n\nCliente encontrado!"RESET);
            encontrou = true;
            break;
        }
    }


    if(!encontrou){
            printf(VERMELHO"\n\nCliente não encontrado!"RESET);
            Sleep(500);
            return;
        }

    Sleep(500);
    system("cls");
    printf("--Alugar filme--\n");
    printf("\nDigite o ID do filme: ");
    scanf("%d", &id);
    getchar();

    if(id < 0 || id >=n || !filme[id].status){
        printf(VERMELHO"\n\nFilme não encontrado!"RESET);
        Sleep(500);
        return;
    }

    if(filme[id].quantidade == 0){
        printf(VERMELHO"\n\nSem estoque para esse filme!"RESET);
        Sleep(500);
        return;
    }

    filme[id].quantidade--;
    printf(VERDE"\n\nAluguel realizado com sucesso!"RESET);
    printf("\n\nNome: %s", filme[id].nome);
    printf("\nPreço: %.2f", filme[id].preco);
    printf("\nQuantidades disponíveis: %d", filme[id].quantidade);
    printf("\n\n");
    system("pause");
    return;
}

//aqui o ponteiro é duplo pq ele realmente vai acessar e mudar o conteudo daquele endereço de memória de um ponteiro que ta foi declarado fora do escopo da função, criando um ponteiro de ponteiro(**)
//no resto como não vou mudar o valor em si, apenas uso de referencia para acessar o amigo

void executaMenuFilmes(int op, int *n, int *m, TFilme **filme, TCliente *cliente){

        switch(op){

            case 1:
                (*n)++;
                if(*n == 1){
                    *filme = (TFilme *) malloc(sizeof(TFilme));
                }else{
                    *filme = (TFilme *) realloc(*filme, *n * sizeof(TFilme));
                }

                if(*filme == NULL){
                    printf("Erro em alocação de memória\n");
                    system("pause");
                    exit(1);
                }

                cadastraFilme(*filme, *n-1);


            break;

        case 2:
            if(*n == 0){
                printf(VERMELHO"\n\nNão há filmes cadastrados!"RESET);
                Sleep(500);
                break;
            }
            pesquisaFilme(*filme, n);
            break;

        case 3:

            if(*n == 0){
                printf(VERMELHO"\n\nNão há filmes cadastrados!"RESET);
                Sleep(500);
                break;
            }
            imprimeTodos(*filme, *n);
            break;

        case 4:

            if(*n == 0){
                printf(VERMELHO"\n\nNão há filmes cadastrados!"RESET);
                Sleep(500);
                break;
            }
            atualizaFilme(*filme, *n);
            break;

        case 5:

            if(*n > 0){
                removerFilme(filme,n);
                Sleep(500);
                break;
            }
            printf(VERMELHO"\n\nNão há filmes cadastrados!"RESET);
            Sleep(500);
            break;

        case 6:

            if(*n == 0){
                printf(VERMELHO"\n\nNão há filmes cadastrados!"RESET);
                Sleep(500);
                break;
            }
            alugaFilme(*filme,cliente,*n,*m);
            break;

        case 7:
            printf(VERDE"\n\nRetornando ao menu principal!"RESET);
            Sleep(500);
            break;

        default:
            printf(VERMELHO"\n\nOpção inválida!"RESET);
            Sleep(500);
            break;
        }

    }

void menuFilmes(int *n, int *m, TFilme **filme, TCliente *cliente){
    int op;
    do{
        op = imprimeMenuFilmes();
        executaMenuFilmes(op,n,m,filme,cliente);
    } while(op!=7);
}

int main (){
    setlocale(LC_ALL, "Portuguese");
    int n, m, resposta;
    n = 0;
    m = 0;

    TCliente *cliente = NULL;
    TFilme *filme = NULL;
    do{
        system("cls");
        printf(AZUL"--Menus--"RESET);
        printf("\n\n1-Menu Clientes\n2-Menu Filmes\n3-Sair\n\nOpção: ");
        scanf("%d", &resposta);
        getchar();

        switch(resposta){

            case 1:

                menuClientes(&m,&cliente);
                break;

            case 2:
                menuFilmes(&n,&m,&filme, cliente);
                break;

            case 3:
                printf(VERDE"\n\nEncerrando operações!"RESET);
                break;
            default:
                printf(VERMELHO"\n\nOpção inválida!"RESET);
                break;
        }

        Sleep(500);

    } while(resposta != 3);
	free(cliente);
	cliente = NULL;
	
	free(filme);
	filme = NULL;
    return 0;
}
