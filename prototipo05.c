#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

typedef struct login                         
{
    char username[30];
    char password[20];
   
}User;

typedef struct address
{
    char address1[30];
    int number;
    char address2[30];
    char city[30];
    char state[30];
    char CEP[30];

}Address;

typedef struct client
{
    char patientName[30];
    char patientEmail[50];
    char patientCPF[12];
    char patientPhone[30];
    Address patient;
    int bDay,bMonth,bYear;
    char diagnosticDate[12];
}Patient ;

void flush_in() {                  /* essa função deve limpar o buffer */
    int ch;
    do
    {
        ch = fgetc(stdin); 

    } while (ch != EOF && ch != '\n');
}


int checkId (User nameId){
    int validate;
        if(strcmp(nameId.username,"Admin")==0 && strcmp(nameId.password,"Admin")==0){       //strcmp compara as duas strings
           printf("\nOlá %s \n",nameId.username);   
           system("clear");
           patientRegister();
            validate=1;         
       }else {
        printf("Erro! Nome ou senha inválido.");
            validate=0;       
       } 
    return validate;
}

void saveRetister(char* comorbidity){
     Patient p;

     
        FILE *storage;
        storage = fopen("Cadastro_de_pacientes.txt","a");

        if (storage == NULL) 
            {   
              printf("Error! Could not open file\n"); 
              exit(-1); 
            } 

        fprintf(storage,"%s\n",p.patientName); //grava o texto em um arquivo txt     
        fprintf(storage,"%s\n",p.patientCPF);
        fprintf(storage,"%s\n",p.patientEmail);
        fprintf(storage,"%s\n",p.patientPhone);
        fprintf(storage,"%d/%d/%d\n",p.bDay,p.bMonth,p.bYear);
        fprintf(storage,"%s\n",p.diagnosticDate);
        fprintf(storage,"%s\n",p.patient.address1);
        fprintf(storage,"%s\n",p.patient.number);
        fprintf(storage,"%s\n",p.patient.address2);
        fprintf(storage,"%s\n",p.patient.city);
        fprintf(storage,"%s\n",p.patient.state);
        fprintf(storage,"%s\n",p.patient.CEP);
        fprintf(storage,"%s\n",comorbidity);

        fclose(storage);
}

void riskGroup(Patient p, int option){
    int age=0,year=0, byear=0;
    
     //função para pegar a data do sistema
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    year = local->tm_year + 1900;

    byear = p.bYear;
    for (int i = byear; i <= year; i++) // calcula a idade do paciente
    {
       age++;
    }

    if(age >= 65 || option > 0){    //a variavel comorbidity não está funcionando
        FILE *storage;
        storage = fopen("grupoDerisco.txt","a");
        fprintf(storage,"%s %d\n",p.patient.CEP,age); //grava o texto em um arquivo txt            
        fclose(storage);
    }

    return; 
}

void patientRegister(){
    Patient data;
    int nregister=0, option=0;
    char comorbidity[20];

    system("clear");
    printf("Cadastro de paciente\n\n");
    printf("Nome do paciente: ");
    fgets(data.patientName,30,stdin);
    flush_in();
    getchar();
    printf("Digite o CPF (Apenas os númeors): ");
    scanf("%s",&data.patientCPF);
    getchar();
    printf("Email: ");
    scanf("%s",&data.patientEmail);
    getchar();
    printf("Telefone: ");
    scanf("%s",&data.patientPhone);
    getchar();
    printf("Digite a data de nascimento dd/mm/aaaa: ");
    scanf("%d/%d/%d",&data.bDay,&data.bMonth,&data.bYear);
    getchar();
    printf("Data do diagnóstico (dd/mm): ");
    scanf("%s",&data.diagnosticDate);
    getchar();
    printf("Digite agora o Endereço\n");
    printf("Rua/Avenida: ");
    fgets(data.patient.address1, 50 , stdin);  
    flush_in();
    printf("Numero: ");
    scanf("%d",&data.patient.number);  
    printf("Bairro: ");
    fgets(data.patient.address2, 50 , stdin);
    flush_in();
    getchar();
    printf("Cidade: ");
    scanf("%s",&data.patient.city);
    printf("Estado: ");
    scanf("%s",&data.patient.state);
    printf("CEP: ");
    scanf("%s",&data.patient.CEP);
    flush_in();
    printf("Possui comorbidade?\nNão - 0\nDiabetes -1\nObesidade - 2\nHipertenção - 3\nOutros - 4 :");
    scanf("%d",&option);
    getchar();

    riskGroup(data,option); // Função que verifica e grava o cep e idade do paciente do Grupo de risco

        switch (option)
    {
    case 1:
        *comorbidity = "Diabetes";
        break;
    case 2:
        *comorbidity = "Obesidade";
        break;    
    case 3:
        *comorbidity = "Hipertenção";
        break;
    case 4:
        *comorbidity ="Outros";
        break;    
    default:
        break;
    }

    saveRetister(comorbidity);

    printf("\nPara novo cadastro digite 1: ");
    scanf("%d",&nregister);
    if (nregister == 1)
    {
        patientRegister();
    }
    return;
}

void main(){
    User log;
    int check=NULL, status;
    char response;

   printf("**************************************************\n");
   printf("*Cadastro de paciente diagnosticados com COVID-19*\n");
   printf("**************************************************\n");
   printf("\n\n");
 
   do
    {
        printf("Digite seu Nome de usuário: ");
        scanf("%s",&log.username);
        getchar();
        printf("Digite sua senha: ");
        scanf("%s",&log.password);
        check=checkId(log);
        if (check == 0)
        {
            printf("Deseja tentar novamente?\n 'S' para tentar de novo ou outra tecla para sair: ");
            scanf("%c",&response);
            getchar();
            //flush_in();
        }else{
           
            break;
        }
    } while (response == 's' || response == 'S');
    
}