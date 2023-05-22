#include <stdio.h>
#include <string.h>

#define MAX_PROFESSORES 4
#define MAX_DISCIPLINAS 3
#define MAX_ESTUDANTES 15
#define MAX_ESTUDANTES_POR_DISCIPLINA 10

typedef struct {
    char nome[50];
    char titulacao[20];
} Professor;

typedef struct {
    char nome[50];
    int cargaHoraria;
    Professor* responsavel;
} Disciplina;

typedef struct {
    char nome[50];
    int matricula;
    int idade;
    Disciplina* disciplina;
} Estudante;

void bubbleSort(Estudante estudantes[], int numEstudantes) {
    for (int i = 0; i < numEstudantes - 1; i++) {
        for (int j = 0; j < numEstudantes - i - 1; j++) {
            if (estudantes[j].idade < estudantes[j + 1].idade) {
                Estudante temp = estudantes[j];
                estudantes[j] = estudantes[j + 1];
                estudantes[j + 1] = temp;
            }
        }
    }
}

int le_valida_idade() {
    int idade;
    do {
        printf("Idade (entre 16 e 26): ");
        scanf("%d", &idade);
    } while (idade < 16 || idade > 26);
    return idade;
}

int main() {
    Professor professores[MAX_PROFESSORES];
    Disciplina disciplinas[MAX_DISCIPLINAS];
    Estudante estudantes[MAX_ESTUDANTES];
    int numEstudantes[MAX_DISCIPLINAS] = {0};

    printf("=== Cadastro de Professores ===\n");
    for (int i = 1; i < MAX_PROFESSORES; i++) {
        printf("Professor %d:\n", i);

        printf("Nome: ");
        scanf("%s", professores[i].nome);

        printf("Titulacao (Mestre, Doutor ou Especialista): ");
        scanf("%s", professores[i].titulacao);

        printf("\n");
    }

    printf("=== Cadastro de Disciplinas ===\n");
    for (int i = 1; i < MAX_DISCIPLINAS; i++) {
        printf("Disciplina %d:\n", i);

        printf("Nome: ");
        scanf("%s", disciplinas[i].nome);

        printf("Carga horaria: ");
        scanf("%d", &disciplinas[i].cargaHoraria);

        printf("Professor responsavel (1 a %d): ", MAX_PROFESSORES -1 );
        int professorResponsavel;
        scanf("%d", &professorResponsavel);
        disciplinas[i].responsavel = &professores[professorResponsavel];

        printf("\n");
    }

    printf("=== Cadastro de Estudantes ===\n");
    for (int i = 1; i < MAX_ESTUDANTES; i++) {
        printf("Estudante %d:\n", i );

        printf("Nome: ");
        scanf("%s", estudantes[i].nome);

        printf("Matricula: ");
        scanf("%d", &estudantes[i].matricula);

        estudantes[i].idade = le_valida_idade();

        printf("Disciplina desejada (1 a %d): ", MAX_DISCIPLINAS - 1);
        int disciplinaDesejada;
        scanf("%d", &disciplinaDesejada);
        if (numEstudantes[disciplinaDesejada] < MAX_ESTUDANTES_POR_DISCIPLINA) {
            estudantes[i].disciplina = &disciplinas[disciplinaDesejada];
            numEstudantes[disciplinaDesejada]++;
        } else {
            printf("Numero maximo de estudantes para essa disciplina atingido.\n");
        }

        printf("\n");
    }

    for (int i = 0; i < MAX_DISCIPLINAS; i++) {
        bubbleSort(estudantes, numEstudantes[i]);

        printf("=== Estudantes da Disciplina %s (ordenados por idade) ===\n", disciplinas[i].nome);
        for (int j = 0; j < numEstudantes[i]; j++) {
            printf("Nome: %s, Matricula: %d, Idade: %d\n",
                estudantes[j].nome, estudantes[j].matricula, estudantes[j].idade);
        }
        printf("\n");
    }

    return 0;
}
