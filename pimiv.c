#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_USERS 100
#define MAX_COMPANIES 100

typedef struct {
    char username[50];
    char password[50]; // Senha criptografada
} User;

typedef struct {
    char name[100];
    char cnpj[20];
    char email[100];
    char address[200];
    char phone[15];
    char openingDate[11];
    float monthlyWaste[12]; // Quantidade de resíduos tratados por mês
    float monthlyCosts[12]; // Custos mensais

} Company;

User users[MAX_USERS];
Company companies[MAX_COMPANIES];
int userCount = 0, companyCount = 0;

// Função para criptografar senha (simples)
void encryptPassword(char *password) {
    for (int i = 0; password[i] != '\0'; i++) {
        password[i] += 3; // Criptografia simples: deslocamento de caracteres
    }
}

// Função para descriptografar senha
void decryptPassword(char *password) {
    for (int i = 0; password[i] != '\0'; i++) {
        password[i] -= 3; // Reversão do deslocamento
    }
}

// Função para cadastro de usuário
void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("Limite de usuários alcançado!\n");
        return;
    }

    User newUser;
    printf("Digite o nome de usuário: ");
    scanf(" %49s", newUser.username);
    printf("Digite a senha: ");
    scanf(" %49s", newUser.password);
    encryptPassword(newUser.password);

    users[userCount++] = newUser;
    printf("Usuário cadastrado com sucesso!\n");
}

// Função para login de usuário
int login() {
    char username[50], password[50];
    printf("Digite o nome de usuário: ");
    scanf(" %49s", username);
    printf("Digite a senha: ");
    scanf(" %49s", password);
    encryptPassword(password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login realizado com sucesso!\n");
            return 1;
        }
    }
    printf("Usuário ou senha inválidos!\n");
    return 0;
}

// Função para cadastro de empresa
void registerCompany() {
    if (companyCount >= MAX_COMPANIES) {
        printf("Limite de empresas alcançado!\n");
        return;
    }

    Company newCompany;
    printf("Digite o nome da empresa: ");
    scanf(" %99[^\n]", newCompany.name);
    printf("Digite o CNPJ: ");
    scanf(" %19s", newCompany.cnpj);
    printf("Digite o e-mail: ");
    scanf(" %99s", newCompany.email);
    printf("Digite o endereço: ");
    scanf(" %199[^\n]", newCompany.address);
    printf("Digite o telefone: ");
    scanf(" %14s", newCompany.phone);
    printf("Digite a data de abertura (DD/MM/AAAA): ");
    scanf(" %10s", newCompany.openingDate);

    memset(newCompany.monthlyWaste, 0, sizeof(newCompany.monthlyWaste));
    memset(newCompany.monthlyCosts, 0, sizeof(newCompany.monthlyCosts));

    companies[companyCount++] = newCompany;
    printf("Empresa cadastrada com sucesso!\n");
}

// Atualizar resíduos e custos
void updateWasteAndCosts() {
    char cnpj[20];
    printf("Digite o CNPJ da empresa: ");
    scanf(" %19s", cnpj);

    for (int i = 0; i < companyCount; i++) {
        if (strcmp(companies[i].cnpj, cnpj) == 0) {
            int month;
            printf("Digite o número do mês (1-12): ");
            scanf("%d", &month);

            if (month < 1 || month > 12) {
                printf("Mês inválido!\n");
                return;
            }

            printf("Digite a quantidade de resíduos tratados (toneladas): ");
            scanf("%f", &companies[i].monthlyWaste[month - 1]);

            printf("Digite o custo estimado (R$): ");
            scanf("%f", &companies[i].monthlyCosts[month - 1]);

            printf("Atualização realizada com sucesso!\n");
            return;
        }
    }
    printf("Empresa não encontrada!\n");
}

// Gerar relatórios
void generateReports() {
    int choice;
    printf("\nEscolha o formato para o relatório:\n");
    printf("1. TXT\n");
    printf("2. CSV\n");
    printf("3. XLS\n");
    printf("Escolha o formato (1-3): ");
    scanf("%d", &choice);

    // Caminho do arquivo
    char filePath[MAX_PATH];
    DWORD dwRet = GetCurrentDirectory(MAX_PATH, filePath);
    if (dwRet == 0) {
        perror("Erro ao obter o diretório atual");
        return;
    }

    FILE *file = NULL;
    if (choice == 1) {
        strcat(filePath, "\\relatorio_ambiental.txt"); // Caminho para TXT
        file = fopen(filePath, "w");
    } else if (choice == 2) {
        strcat(filePath, "\\relatorio_ambiental.csv"); // Caminho para CSV
        file = fopen(filePath, "w");
    } else if (choice == 3) {
        strcat(filePath, "\\relatorio_ambiental.xls"); // Caminho para XLS
        file = fopen(filePath, "wb");  // Para XLS, usamos "wb" (modo binário)
    }

    if (!file) {
        printf("Erro: Não foi possível criar o relatório no caminho: %s\n", filePath);
        return;
    }

    // Cabeçalho do arquivo dependendo do formato escolhido
    if (choice == 1) {
        fprintf(file, "Relatório de Empresas (Formato TXT)\n");
        fprintf(file, "Nome da Empresa | CNPJ | Resíduos Totais (ton) | Gasto Total (R$)\n");
    } else if (choice == 2) {
        fprintf(file, "Empresa,CNPJ,Resíduos Totais (ton),Gasto Total (R$)\n");
    } else if (choice == 3) {
        fprintf(file, "Empresa\tCNPJ\tResíduos Totais (ton)\tGasto Total (R$)\n");
    }

    // Relatório individualizado
    printf("\n=== Relatório Individualizado de Empresas ===\n");
    for (int i = 0; i < companyCount; i++) {
        float totalWaste = 0.0f, totalCosts = 0.0f;
        for (int j = 0; j < 12; j++) {
            totalWaste += companies[i].monthlyWaste[j];
            totalCosts += companies[i].monthlyCosts[j];
        }

        // Exibir os dados na tela
        printf("%s - Resíduos Totais: %.2f - Gasto Total: R$ %.2f\n", companies[i].name, totalWaste, totalCosts);

        // Escrever os dados no arquivo
        if (choice == 1) {
            fprintf(file, "%s | %s | %.2f | R$ %.2f\n", companies[i].name, companies[i].cnpj, totalWaste, totalCosts);
        } else if (choice == 2) {
            fprintf(file, "%s,%s,%.2f,%.2f\n", companies[i].name, companies[i].cnpj, totalWaste, totalCosts);
        } else if (choice == 3) {
            fprintf(file, "%s\t%s\t%.2f\t%.2f\n", companies[i].name, companies[i].cnpj, totalWaste, totalCosts);
        }
    }

    // Relatórios globais
    printf("\n=== Relatórios Globais ===\n");

    // Relatório de insumos tratados semestralmente
    printf("\nTotal de insumos tratados semestralmente:\n");
    for (int i = 0; i < companyCount; i++) {
        float totalWasteH1 = 0.0f, totalWasteH2 = 0.0f;

        for (int j = 0; j < 6; j++) {
            totalWasteH1 += companies[i].monthlyWaste[j];  // 1º semestre
        }
        for (int j = 6; j < 12; j++) {
            totalWasteH2 += companies[i].monthlyWaste[j];  // 2º semestre
        }

        printf("Empresa: %s | 1º Semestre: %.2f toneladas | 2º Semestre: %.2f toneladas\n", companies[i].name, totalWasteH1, totalWasteH2);
    }

    // Relatório de gastos mensais
    printf("\nTotal de gastos mensais:\n");
    for (int i = 0; i < companyCount; i++) {
        printf("Empresa: %s\n", companies[i].name);
        for (int j = 0; j < 12; j++) {
            printf("Mês %d: R$ %.2f\n", j + 1, companies[i].monthlyCosts[j]);
        }
    }

    // Relatório de regiões com maior volume de resíduos tratados
    printf("\nRegiões com maior volume de resíduos industriais tratados:\n");
    for (int i = 0; i < companyCount; i++) {
        printf("Empresa: %s | Região: [Falta implementar]\n", companies[i].name);
    }

    // Relatório de indústrias com menor produção no último semestre
    printf("\nIndústrias com menor produção no último semestre:\n");
    for (int i = 0; i < companyCount; i++) {
        float totalWasteH2 = 0.0f;
        for (int j = 6; j < 12; j++) {
            totalWasteH2 += companies[i].monthlyWaste[j];  // 2º semestre
        }
        printf("Empresa: %s | 2º Semestre: %.2f toneladas\n", companies[i].name, totalWasteH2);
    }

    // Aporte financeiro semestral
    printf("\nAporte financeiro semestral:\n");
    for (int i = 0; i < companyCount; i++) {
        float totalCostsH1 = 0.0f, totalCostsH2 = 0.0f;

        for (int j = 0; j < 6; j++) {
            totalCostsH1 += companies[i].monthlyCosts[j];  // 1º semestre
        }
        for (int j = 6; j < 12; j++) {
            totalCostsH2 += companies[i].monthlyCosts[j];  // 2º semestre
        }

        printf("Empresa: %s | 1º Semestre: R$ %.2f | 2º Semestre: R$ %.2f\n", companies[i].name, totalCostsH1, totalCostsH2);
    }

    fclose(file);
    printf("Relatório gerado com sucesso em '%s'!\n", filePath);
}

// Menu principal
void menu() {
    int choice;

    do {
        printf("\n=== Sistema de Gestão Ambiental ===\n");
        printf("1. Cadastro de Usuário\n");
        printf("2. Login\n");
        printf("3. Cadastro de Empresa\n");
        printf("4. Atualizar Resíduos e Custos\n");
        printf("5. Gerar Relatórios\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (login()) {
                    printf("Acesso autorizado.\n");
                } else {
                    printf("Acesso negado.\n");
                }
                break;
            case 3:
                registerCompany();
                break;
            case 4:
                updateWasteAndCosts();
                break;
            case 5:
                generateReports();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (choice != 0);
}

int main() {

    SetConsoleOutputCP(CP_UTF8);

    menu();
    return 0;
}
