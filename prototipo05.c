#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

typedef struct login                         
{
    char username[30];
    char password[20];
   
}User;

    char address1[30];
    int number;
    char address2[30];
    char city[30];
    char state[30];
    char CEP[30];
    char patientName[30];
    char patientEmail[50];
    char patientCPF[12];
    char patientPhone[30];
    int bDay,bMonth,bYear;
    char diagnosticDate[12];


void flush_in() {                  /* essa função deve limpar o buffer */
    int ch;
    do
    {
        ch = fgetc(stdin); 

    } while (ch != EOF && ch != '\n');
}

void saveRegister(char* comorbidity){
     

     
        FILE *storage;
        storage = fopen("Cadastro_de_pacientes.txt","a");

        if (storage == NULL) 
            {   
              printf("Error! Could not open file\n"); 
              exit(-1); 
            } 

        fprintf(storage,"Nome: %s\n",patientName); //grava o texto em um arquivo txt     
        fprintf(storage,"CPF: %s\n",patientCPF);
        fprintf(storage,"Email: %s\n",patientEmail);
        fprintf(storage,"Telefone: %s\n",patientPhone);
        fprintf(storage,"Data de Nascimento: %d/%d/%d\n",bDay,bMonth,bYear);
        fprintf(storage,"Data diagnostico: %s\n",diagnosticDate);
        fprintf(storage,"Rua/Avenida: %s n:%d Bairro:%s\n",address1,number,address2);
        fprintf(storage,"Cidade: %s Estado: %s Cep:%s\n",city,state,CEP);
        fprintf(storage,"Comorbidade:%s\n",comorbidity);
        fclose(storage);
}

void riskGroup(char*CEP, int option, int pbyear){
    int age=0,year=0, byear=0;
    
     //função para pegar a data do sistema
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    year = local->tm_year + 1900;

    byear = pbyear;
    for (int i = pbyear; i <= year; i++) // calcula a idade do paciente
    {
       age++;
    }

    if(age >= 65 || option > 0){    //a variavel comorbidity não está funcionando
        FILE *storage;
        storage = fopen("grupoDerisco.txt","a");
        fprintf(storage,"CEP:%s Idade:%d\n",CEP,age); //grava o texto em um arquivo txt            
        fclose(storage);
    }

    return; 
}

void patientRegister(){
    int nregister=0, option=0;
    char *comorbidity = malloc(sizeof(char)*20);
    system("clear");
    
    printf("Cadastro de paciente\n\n");
    printf("Nome do paciente: ");
    fgets(patientName,30,stdin);
    __fpurge(stdin); 
   
    printf("Digite o CPF (Apenas os númeors): ");
    fgets(patientCPF,12,stdin);
    __fpurge(stdin); 

    printf("Email: ");
    fgets(patientEmail,50,stdin);
    __fpurge(stdin); 

    printf("Telefone: ");
    fgets(patientPhone,30,stdin);
    
    printf("Digite a data de nascimento dd/mm/aaaa: ");
    scanf("%d/%d/%d",&bDay,&bMonth,&bYear);
    __fpurge(stdin); 

    printf("Data do diagnóstico (dd/mm): ");
    fgets(diagnosticDate,12,stdin);
    __fpurge(stdin); 

    printf("Digite agora o Endereço\n\n");

    printf("Rua/Avenida: ");
    fgets(address1, 50 , stdin);  
    __fpurge(stdin); 

    printf("Numero: ");
    scanf("%d",&number);  

    printf("Bairro: ");
    fgets(address2, 50 , stdin);
    flush_in();
    __fpurge(stdin); 

    printf("Cidade: ");
    fgets(city,30,stdin);
    __fpurge(stdin); 

    printf("Estado: ");
    fgets(state,30,stdin);
    __fpurge(stdin); 

    printf("CEP: ");
    fgets(CEP,30,stdin);
    flush_in();
    printf("Possui comorbidade?\nNão - 0\nDiabetes -1\nObesidade - 2\nHipertenção - 3\nOutros - 4 :");
    scanf("%d",&option);
    __fpurge(stdin); 

    riskGroup(CEP,option, bYear); // Função que verifica e grava o cep e idade do paciente do Grupo de risco

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

    saveRegister(comorbidity);

    printf("\nPara novo cadastro digite 1: ");
    scanf("%d",&nregister);
    __fpurge(stdin); 
    if (nregister == 1)
    {
        patientRegister();
    }
    system("clear");
}

int checkId (User nameId){
    int validate;
        if(strcmp(nameId.username,"Admin")==0 && strcmp(nameId.password,"Admin")==0){       //strcmp compara as duas strings
           printf("Login com sucesso!\nTecle ENTER para continuar");   
           flush_in();
           patientRegister();
            validate=1;         
       }else {
        printf("Erro! Nome ou senha inválido.");
            validate=0;       
       } 
    return validate;
}

void main(){
    User log;
    int check=NULL, status;
    char response;
    response = 'n';

   printf("****************************************************\n");
   printf("* Cadastro de paciente diagnosticados com COVID-19 *\n");
   printf("****************************************************\n");
   printf("\n\n");
 
   do
    {
        printf("Digite seu Nome de usuário: ");
        scanf("%s",log.username);
        
        __fpurge(stdin);
        printf("Digite sua senha: ");
        scanf("%s",log.password);
        __fpurge(stdin);
        check=checkId(log);
        if (check == 0)
        {          
            printf("Deseja tentar novamente?\n'Sim' para tentar de novo ou outra tecla para sair: ");
            response = getc(stdin);
            __fpurge(stdin);         
            
            system("clear");
        
        }else{
            
            break;
        }
    } while (response == 's' || response == 'S');
    printf(" Até a próxima!\n\n     =)\n\n\n");
}