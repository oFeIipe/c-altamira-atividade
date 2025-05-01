#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


typedef struct{
	char crm[10];
	char nome[100];
}Medico;

typedef struct{
	char cpf[20];
	char nome[100];
}Paciente;

typedef struct{
    Paciente paciente;
    Medico medico_responsavel;
    char motivo[200];
    char data[20];
    char avaliacao_medica[100];
}Consulta;

void salvar_paciente(Paciente paciente){
	FILE *file = fopen("pacientes.txt", "a");
	
	if(file == NULL) return;
	
	char texto[300];
	
	sprintf(texto, "Nome: %s\nCPF: %s\n\n", paciente.nome, paciente.cpf);
	
	fprintf(file, "%s", texto);
	
	fclose(file);
}

void salvar_medico(Medico medico){
	FILE *file = fopen("medicos.txt", "a");
	
	if(file == NULL) return;
	
	char texto[300];
	
	sprintf(texto, "Nome: %s\nCRM: %s\n\n", medico.nome, medico.crm);
	
	fprintf(file, "%s", texto);
	
	fclose(file);
}

void salvar_consulta(Consulta consulta){
	FILE *file = fopen("consultas.txt", "a");
	
	if(file == NULL) return;
	
	char texto[800];
	
	sprintf(texto, "Nome Paciente: %s\nCPF: %s\nNome Medico: %s\nCRM %s\nMotivo consulta: %s\nData: %s\nAvaliacao medica %s\n\n", consulta.paciente.nome, consulta.paciente.cpf,
	consulta.medico_responsavel.nome, consulta.medico_responsavel.crm, consulta.motivo, consulta.data, consulta.avaliacao_medica);
	
	fprintf(file, "%s", texto);
	
	fclose(file);
}

Paciente cadastrar_paciente(){
	Paciente paciente;
	char opcao;

	printf("Digite o nome do paciente: ");
	fgets(paciente.nome, sizeof(paciente.nome), stdin);
	paciente.nome[strcspn(paciente.nome, "\n")] = '\0';
	
	printf("Digite o CPF do paciente: ");
	fgets(paciente.cpf, sizeof(paciente.cpf), stdin);
	paciente.cpf[strcspn(paciente.cpf, "\n")] = '\0';
	
	printf("Digite 1 para salvar o paciente nos arquivos: ");
	scanf("%c", &opcao);

	if(opcao == '1') salvar_paciente(paciente);

    return paciente;
}

Medico cadastrar_medico(){
	Medico medico;
	char opcao;

	printf("Digite o nome do medico: ");
	fgets(medico.nome, sizeof(medico.nome), stdin);
	medico.nome[strcspn(medico.nome, "\n")] = '\0';
	
	printf("Digite o CRM do medico: ");
	fgets(medico.crm, sizeof(medico.crm), stdin);
	medico.crm[strcspn(medico.crm, "\n")] = '\0';
	
	printf("Digite 1 para salvar o medico nos arquivos: ");
	scanf("%s", &opcao);

	if(opcao == '1') salvar_medico(medico);

    return medico;
}

void agendar_consulta(){
	Consulta consulta;
	Medico medico = cadastrar_medico();
	Paciente paciente = cadastrar_paciente();
	
	
	consulta.paciente = paciente;
	consulta.medico_responsavel = medico;
	
	printf("Digite o motivo da consulta: ");
	fgets(consulta.motivo, sizeof(consulta.motivo), stdin);
	consulta.motivo[strcspn(consulta.motivo, "\n")] = '\0';
	
	printf("Digite a data da consulta no formato 'dd/mm/yyyy': ");
	fgets(consulta.data, sizeof(consulta.data), stdin);
	consulta.data[strcspn(consulta.data, "\n")] = '\0';
	
	printf("Digite a avaliacao medica final: ");
	fgets(consulta.avaliacao_medica, sizeof(consulta.avaliacao_medica), stdin);
	consulta.avaliacao_medica[strcspn(consulta.avaliacao_medica, "\n")] = '\0';
	
	salvar_consulta(consulta);
}

void listar_dados(char *nome){
	FILE *file = fopen(nome, "r");
	
	if(file == NULL){
		printf("ERRO AO ABRIR ARQUIVO\n");
		return;
	}
	
	char linha[800];
	
	while (fgets(linha, sizeof(linha), file) != NULL) {
    printf("%s", linha); 
    }
    
	fclose(file);
    puts("");
}

void print_menu(){
	puts("-------------------------");
	puts("Opcao 1: Cadastrar Paciente");
	puts("Opcao 2: Cadastrar Medico");
	puts("Opcao 3: Agendar Consulta");
	puts("Opcao 4: Listar Pacientes");
	puts("Opcao 5: Listar Medicos");
	puts("Opcao 6: Listar Consultas");
	puts("Opcao 7: Sair");
	puts("-------------------------\n");
}

void menu(){
	char opcao;
	
	print_menu();
	opcao = getch();
	
	switch(opcao){
		case '1':
			cadastrar_paciente();
			break;
		case '2':
			cadastrar_medico();
			break;
		case '3':
			agendar_consulta();
			break;
		case '4':
			listar_dados("pacientes.txt");
			break;
		case '5':
			listar_dados("medicos.txt");
			break;	
		case '6':
			listar_dados("consultas.txt");
			break;				
		case '7':
			return;			
	}
	menu();
}

int main(){
	
	menu();
	
	return 0;
}
