#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "aluno.h"
#define TAM 20
#define ERRO 0
#define SUCESSO 1



int validar_data_nascimento(int dia, int mes, int ano) {
  // verifica se o ano é válido (entre 1900 e o ano atual)
  if (ano < 1900 || ano > 2024) {
    return ERRO;
  }

  // verifica se o mes é válido (entre 1 e 12)
  if (mes < 1 || mes > 12) {
    return ERRO;
  }

  // verifica se o dia é válido com base no mês
  int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) { // ano bissexto
    diasNoMes[1] = 29;
  }
  if (dia < 1 || dia > diasNoMes[mes - 1]) {
    return ERRO;
  }

  return SUCESSO;
}

int listarAluno(struct Aluno *atual) {
    printf("\nLista de alunos:");

    if(atual == NULL){
        printf("\nLista Vazia!");
        return ERRO;
    }

    while (atual != NULL) { // Corrige a condição de parada
        printf("\n Nome: %s", atual->nome);
        printf(" | Matricula: %d", atual->matricula);
        atual = atual->prox;
    }
    return SUCESSO;
}

void menuAluno(struct Aluno **listaAluno){

    int sairAluno = 1;
    int opcao = 1;

    while(sairAluno){

        printf("\n\n Menu aluno \n\n");
        printf("0 - Voltar\n");
        printf("1 - Cadastrar aluno\n");
        printf("2 - Atualizar aluno\n");
        printf("3 - Excluir aluno\n");
        printf("4 - Listar alunos\n");
        printf("5 - Listar alunos por categoria\n");
        printf("\nInsira uma opcao: ");
        scanf("%d", &opcao);
        system("clear");

        switch(opcao){
            case 0:
                sairAluno = 0;
                printf("Voltando...\n");
                break;
            case 1:
                if(inserirAluno(listaAluno)) printf("Aluno adicionado com sucesso\n");
                break;
            case 2:
                atualizarAluno(listaAluno);
                break;
            case 3:
                removerAluno(listaAluno);
                break;
            case 4:
                listarAluno(*listaAluno);
                break;
            case 5:
                relatorioAluno(*listaAluno);
                break;
            default:
                printf("\nOpcao invalida!");
                break;
        }
    }

}


int relatorioAluno(struct Aluno *temp){

    int cont = 0;

    struct Aluno *aux = temp;


    int opcao;

    printf("\n\n Relatorios \n\n");
    printf("0 - Voltar\n");
    printf("1 - Listar alunos por sexo\n");
    printf("2 - Listar alunos por nome (ordem alfabetica)\n");
    printf("3 - Listar alunos por data de nascimento\n");
    printf("4 - Listar alunos matriculados em menos de 3 disciplinas\n");
    printf("5 - Listar alunos detalhadamente");
    printf("\nInsira uma opcao: ");
    scanf("%d", &opcao);
    system("clear");

    switch(opcao){
        case 0:
            printf("\nVoltando...");
            break;
        case 1:
            if(temp == NULL){
                printf("\nLista Vazia!");
                return ERRO;
            }
            printf("\n1 - Masculino");
            printf("\n2 - Feminino");
            printf("\nQual sexo deseja filtrar: ");
            scanf("%d", &opcao);
            if(opcao == 1){
                printf("Alunos do sexo masculino: ");
                while(temp != NULL){
                    if(temp->sexo == 'M' || temp->sexo == 'm') printf("\n%s", temp->nome);
                    temp = temp->prox; 
                }
            }else if(opcao == 2){
                printf("Alunos do sexo feminino: ");
                while(temp != NULL){
                    if(temp->sexo == 'F' || temp->sexo == 'f') printf("\n%s", temp->nome);
                    temp = temp->prox; 
                }
            }else{
                printf("\nInsira uma opcao valida!");
                return ERRO;
            }
            break;
        case 2:
            if(temp == NULL){
                printf("\nLista Vazia!");
                return ERRO;
            }

            while (temp != NULL) { //verifica a quantidade de alunos cadastrados
                cont++;
                temp = temp->prox;
            }

            char **aluno = (char**) malloc(cont * sizeof(char*)); // alocando matriz de strings
            for(int i = 0; i < cont; i++){
                aluno[i] = (char*) malloc(TAM * sizeof(char));
            }

            for(int i = 0; i < cont; i++){
                strcpy(aluno[i], aux->nome);
                aux = aux->prox;
            }

            char saux[TAM];

            for(int i = 0; i < cont; i++){
                for(int j = i + 1; j < cont; j++){
                    if(strcmp(aluno[i], aluno[j]) > 0){
                        strcpy(saux, aluno[i]);
                        strcpy(aluno[i], aluno[j]);
                        strcpy(aluno[j], saux);
                    }
                }
            }

            for(int i = 0; i < cont; i++){
                printf("\n%s", aluno[i]);
            }

            for (int i = 0; i < cont; i++) {
                free(aluno[i]); // libera cada string individualmente
            }
            free(aluno);
            break;
        case 3:
            if(temp == NULL){
                printf("\nLista Vazia!");
                return ERRO;
            }

            while (temp != NULL) { //verifica a quantidade de alunos cadastrados e calcula a idade em dias
                temp->diasIdade = temp->anoNascimento * 365.3 + temp->mesNascimento * 30 + temp->diaNascimento;
                cont++;
                temp = temp->prox;
            }
            
            int *idade = (int*) malloc(cont * sizeof(int));
            char **alunos = (char**) malloc(cont * sizeof(char*)); // alocando matriz de strings

            for (int i = 0; i < cont; i++) {
                alunos[i] = (char*) malloc(TAM * sizeof(char));
            }
            
            for(int i = 0; i < cont; i++){
                idade[i] = aux->diasIdade;
                strcpy(alunos[i], aux->nome);
                aux = aux->prox;
            }

            int iaux;
            char naux[TAM];

            for(int i = 0; i < cont; i++){
                for(int j = i + 1; j < cont; j++){
                    if(idade[j] > idade[i]){
                        iaux = idade[j];
                        idade[j] = idade[i];
                        idade[i] = iaux;
                        strcpy(naux, alunos[j]);
                        strcpy(alunos[j], alunos[i]);
                        strcpy(alunos[i], naux);
                    }
                }
                printf("\nAluno: %s", alunos[i]);
            }
            for (int i = 0; i < cont; i++) {
                free(alunos[i]); // libera cada string individualmente
            }
            free(alunos);
            free(idade);
            break;
        case 4:
            printf("\nAlunos cadastrados em menos de 3 disciplinas: ");
            while(temp != NULL){
                if(temp->disciplinasCadastradas < 3) printf("\nAluno: %s | Disciplinas: %d", temp->nome, temp->disciplinasCadastradas);
                temp = temp->prox; 
            }
            break;
        case 5:
            if(temp == NULL){
                printf("\nLista Vazia!");
                return ERRO;
            }

            while (temp != NULL) { // Corrige a condição de parada
                printf("\n Nome: %s", temp->nome);
                printf(" | Matricula: %d", temp->matricula);
                printf(" | Sexo: %c", temp->sexo);
                printf(" | CPF: %s", temp->cpf);
                printf(" | Data de nascimento: %d/%d/%d", temp->diaNascimento, temp->mesNascimento, temp->anoNascimento);
                printf(" | Disciplinas cadastradas: %d", temp->disciplinasCadastradas);
                temp = temp->prox;
            }
            break;
        default:
            break;
    }


    return SUCESSO;
}



int inserirAluno(struct Aluno **listaAluno){
    struct Aluno *novo;
    novo = malloc(sizeof(struct Aluno));

    //verifica se o malloc retornou NULL
    if(novo == NULL){
        printf("ERRO AO ALOCAR MEMORIA");
        exit(ERRO);
    }

    
    novo->prox = NULL;
    printf("\nDigite o nome do aluno: ");

    fflush(stdin);
    fgets(novo->nome, TAM, stdin);
    printf("\nDigite o sexo do aluno ('m' ou 'f'): ");
    scanf("%c", &novo->sexo);
    printf("\nDigite a data de nascimento do aluno no formato (ddmmaaaa): ");
    int data, dia, mes, ano;
    scanf("%d", &data);
    ano = data % 10000;
    data /= 10000;
    mes = data % 100;
    data /= 100;
    dia = data;

    novo->matricula = rand() * dia % 10000;
    printf("\nMatricula gerada: %d", novo->matricula);

    if(validar_data_nascimento(dia, mes, ano) == SUCESSO){
        novo->anoNascimento = ano;
        novo->mesNascimento = mes;
        novo->diaNascimento = dia;
    }else{
        printf("\nData invalida!");
        free(novo);
        return ERRO;
    }

    printf("\nAno nascimento: %d", novo->anoNascimento);
    printf("\nMes nascimento: %d", novo->mesNascimento);
    printf("\nDia nascimento: %d", novo->diaNascimento);

    novo->disciplinasCadastradas = 0;

    printf("\nDigite o CPF do aluno: ");
    fflush(stdin);
    fgets(novo->cpf, 12, stdin);
    if(novo->cpf[12] ==  '\n') novo->cpf[12] = '\0';

    if(validar_cpf(novo->cpf) == SUCESSO){
        printf("\nCPF validado com sucesso!\n");
    }else{
        printf("\nCPF invalido!\nErro ao cadastrar CPF\n");
        free(novo);
        return ERRO;
    }
    
    size_t ln = strlen(novo->nome);
    if(novo->nome[ln-1] ==  '\n') novo->nome[ln-1] = '\0';

    if (*listaAluno == NULL) { // se a lista estiver vazia
        *listaAluno = novo; 
    } else {
        struct Aluno *temp = *listaAluno;
        while (temp->prox != NULL) temp = temp->prox;
        temp->prox = novo;
    }

    return SUCESSO;
}

int removerAluno(struct Aluno **listaAluno){
    struct Aluno *temp = *listaAluno;
    char string[TAM];
    fflush(stdin);
    printf("\nDigite o nome do aluno a ser removido: ");
    fgets(string, TAM, stdin);

    //remoção do \n deixado no final da string pelo fgets
    size_t ln = strlen(string);
    if(string[ln-1] == '\n') string[ln-1] = '\0';

    if(!strcmp(temp->nome, string)){ //caso o aluno a ser removido seja o primeiro da lista
        *listaAluno = temp->prox;
        free(temp);
        return SUCESSO;
    }

    while(temp != NULL){
        struct Aluno *tempprox = temp->prox; // celula posterior a temp
        if(!strcmp(tempprox->nome, string)){
            temp->prox = tempprox->prox;
            free(tempprox);
            return SUCESSO;
        }
        temp = temp->prox;
    }
    return ERRO;
}


int atualizarAluno(struct Aluno **listaAluno){

    struct Aluno *temp = *listaAluno;
    char string[TAM];
    fflush(stdin);
    printf("\nDigite o nome do aluno para atualizar: ");
    fgets(string, TAM, stdin);

    //remoção do \n deixado no final da string pelo fgets
    size_t ln = strlen(string);
    if(string[ln-1] == '\n') string[ln-1] = '\0';

    

    while(temp != NULL){
        if(!strcmp(temp->nome, string)){

            int opcao = 1;
            while(opcao){

                printf("\nQual informacao deseja atualizar: ");
                printf("\n0 - Voltar\n");
                printf("1 - Nome\n");
                printf("2 - Sexo\n");
                printf("3 - Data Nascimento\n");
                printf("4 - CPF\n");
                printf("\nInsira uma opcao: ");
                scanf("%d", &opcao);

                system("clear");

                if(opcao >= 0 && opcao <= 4) break;
                else printf("\nDigite uma opcao valida!");
            }

            switch(opcao){
            case 1:{
                printf("\nDigite o novo nome para modificar: ");
                fflush(stdin); // limpa o buffer
                fgets(temp->nome, TAM, stdin);
                ln = strlen(temp->nome);
                if(temp->nome[ln-1] == '\n') temp->nome[ln-1] = '\0';
                printf("\nNome atualizado com sucesso");
                return SUCESSO;
                break;
            }
            case 2:{
                printf("\nDigite um novo sexo para modificar: ");
                char tsexo;
                fflush(stdin);
                scanf("%c", &tsexo);
                if(tsexo == 'm' || tsexo == 'M' || tsexo == 'f' || tsexo == 'F'){
                    temp->sexo = tsexo;
                    return SUCESSO;
                }
                else{
                    printf("\nDigite um sexo valido ('m' ou 'f')");
                    return ERRO;
                }
                break;
            }
            case 3:{
                printf("\nDigite a data de nascimento do aluno no formato (ddmmaaaa): ");
                int data, dia, mes, ano;
                scanf("%d", &data);
                ano = data % 10000;
                data /= 10000;
                mes = data % 100;
                data /= 100;
                dia = data;

                if(validar_data_nascimento(dia, mes, ano) == SUCESSO){
                    temp->anoNascimento = ano;
                    temp->mesNascimento = mes;
                    temp->diaNascimento = dia;
                }else{
                    printf("\nData invalida!");
                    return ERRO;
                }

                printf("\nAno nascimento: %d", temp->anoNascimento);
                printf("\nMes nascimento: %d", temp->mesNascimento);
                printf("\nDia nascimento: %d", temp->diaNascimento);
                return SUCESSO;
                break;
            }
            case 4:{
                printf("\nDigite o novo CPF: ");
                fflush(stdin);
                char tcpf[13];
                fgets(tcpf, 12, stdin);
                if(tcpf[12] ==  '\n') tcpf[12] = '\0';

                if(validar_cpf(tcpf) == SUCESSO){
                    printf("\nCPF validado com sucesso!\n");
                    strcpy(temp->cpf, tcpf);
                    return SUCESSO;
                }else{
                    printf("\nCPF invalido!\nErro ao cadastrar CPF\n");
                    return ERRO;
                }
                break;
            }

        }
            break;
        }
        temp = temp->prox;
    }

    printf("\nAluno nao encontrado");
    
    return ERRO;

}

int validar_cpf(char cpf[]){

    //verifica se o cpf informado tem menos de 11 digitos
    for(int i = 0; i < 11; i++){
        if(cpf[i] == '\0') return ERRO;
    }

    int icpf[11];
    int soma = 0;
    int resto1, resto2;
    int digito1, digito2;

    //conversao de tipos
    for(int i = 0; i < 11; i++){
        icpf[i] = cpf[i] - 48;
    }

    //calculo primeiro digito verificador
    for(int i = 0; i < 9; i++){
        soma += icpf[i] * (10 - i);
    }

    resto1 = soma % 11;

    if(resto1 < 2) digito1 = 0;
    else digito1 = 11 - resto1;

    //calculo segundo digito verificador
    soma = 0;
    for(int i = 0; i < 10; i++){
        soma += icpf[i] * (11 - i);
    }

    resto2 = soma % 11;
    if(resto2 < 2) digito1 = 0;
    else digito2 = 11 - resto2;

    if(icpf[9] == digito1 && icpf[10] == digito2) return SUCESSO;

    return ERRO;
}
