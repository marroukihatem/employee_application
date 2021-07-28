#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream> 
#include <iostream>

 struct S_employee
 {
    char employee_name[50];
    int employee_age;
    char employee_designation[50];
    float employee_salary;
 };

  void flush()
  {
      int c = 0;
      while((c == getchar() != '\n' && c !=EOF));
  }

 int main()
 {

  FILE *employeeFile; 
  FILE *employeeFileTemp; 
  char userCHoice; 
  char nextChoice; 
  char employemodif[50];


   struct S_employee employee;
   
    
    long int sizeofEmployeeRecord; 
    const char *filename = "EMPLOYEE.txt";
    
    employeeFile = fopen(filename,"rb+");
    
    if(employeeFile == NULL)
    {
           employeeFile = fopen(filename,"wb+");

        if(employeeFile == NULL)

        {
            printf("Active pour ouvrire %s\n",filename);
            exit(1);
        }
    }

    sizeofEmployeeRecord = sizeof(employee); 

    while(1)
    {
        printf("1.Ajouter nouveau Employee\n");
        printf("2.Modifie Employee.\n");
        printf("3.Supprimer Employee.\n");
        printf("4.Donner detaille de l'employee.\n");
        printf("5.Exite.\n");
        printf("\n==================================\n");
        fflush(stdin);  
       
        printf("Entre option de votre choix :\n"); 
        scanf("\n%c", &userCHoice);
      
        switch (userCHoice)
        {
        case '1':
        nextChoice = 'y';
        fseek(employeeFile,0,SEEK_END);

         //fprintf(employeeFile,"\n");
        //fprintf(employeeFile,"%ld",sizeofEmployeeRecord);

        while(nextChoice == 'y')
        {
         //flush();   
         printf("\n==================================\n");
         printf("ajouter employe nom :");
         scanf("%s",&employee.employee_name);
        // fgets(employee.employee_name,40,stdin);
         printf("ajouter employe age :");
         scanf("%d",&employee.employee_age);

         printf("ajouter employe designation :");
         scanf("%s",&employee.employee_designation);

         printf("ajouter employer salaire :");
         scanf("%f",&employee.employee_salary);

         //fprint(&employee,sizeofEmployeeRecord,1,employeeFile);
         
         fwrite(&employee,sizeofEmployeeRecord,1,employeeFile);

         printf(" \n le nom %s est ajouter  : ",&employee.employee_name);
         
         fflush(stdin);

         printf("\ntu peut ajoutee a autre record :(y/n)?\n");   
         scanf("\n%s",&nextChoice);
         //printf("\n==============================\n");
        }
    
            break;

        case '2': 
        nextChoice = 'y';
        while (nextChoice == 'y')
        {
          fflush(stdin);
          printf("entre le nom qui tu peut modifier :\n");
          scanf("%s",&employemodif); 

          //rewind(employeeFile); 
               fseek(employeeFile,0,SEEK_SET);
               while (fread(&employee,sizeofEmployeeRecord,1,employeeFile) == 1 ) 
                 {
                    if(strcmp(employee.employee_name,employemodif) == 0)  
                 {
                   
                   printf(" Entre le nauveau nom d'empolyee qui vous change %s :",employemodif);
                   scanf("%s",&employee.employee_name);
        
                   printf("Entre le nauveau age d'employe qui vous change  %s:",employee.employee_name);
                   scanf("%d",&employee.employee_age);

                   printf("Entre le nauveau designation d'employe qui vous change %s :",employee.employee_name);
                   scanf("%s",&employee.employee_designation);

                   printf("Entre le nauveau salaire d'employe qui vous change %s :",employee.employee_name);
                   scanf("%f",&employee.employee_salary);

                   fseek(employeeFile,-sizeofEmployeeRecord,SEEK_CUR);
                   fwrite(&employee,sizeofEmployeeRecord,1,employeeFile);
                   break;
              }
          }
          
          printf(" \n le nom %s a eté modifieé \n : ",&employemodif);

          printf("\ntu peut modifier a autre record :(y/n)?\n");
          fflush(stdin);
          scanf("\n%s",&nextChoice);

        }
            break;

        case '3':
        nextChoice = 'y';
        while (nextChoice == 'y')
        {
            printf("entre le nom qui tu peut Supprimer :\n");
            scanf("%s",&employemodif);

            employeeFileTemp = fopen("Temp.txt","wb");
            rewind(employeeFile);

            while(fread(&employee,sizeofEmployeeRecord,1,employeeFile) == 1);
            {
                if (strcmp(employee.employee_name,employemodif) !=0) 
                {
                    fwrite(&employee,sizeofEmployeeRecord,1,employeeFileTemp);
                }  
            }

             fclose(employeeFile);
             fclose(employeeFileTemp);

             remove("EMPLOYEE.txt");
             rename("Temp.txt","EMPLOYEE.txt");
             
             fopen("Temp.txt","wb+");

            printf(" \nsupprime le nom %s\n : ",&employemodif); 

            printf("\ntu peut supprimer a autre record :(y/n)?\n");
            scanf("\n%s",&nextChoice);
        }

            break;
        case '4':
            fseek(employeeFile,0,SEEK_SET); 
            while(fread(&employee,sizeofEmployeeRecord,1,employeeFile) == 1) 
            {
                printf("==================================");
                printf("\n");
                printf("Nom d'employee : %s ",employee.employee_name);
                printf("\n");
                printf("Age d'employee : %d ",employee.employee_age);
                printf("\n");
                printf("Designation d'employee : %s ",employee.employee_designation);
                printf("\n");
                printf("Salaire d'employee : %f ",employee.employee_salary);
                printf("\n");
                printf("==================================");
                printf("\n");
            }
             break;

        case '5':

             exit(0);     

        default:
            break;
        }
    }
       getchar();  
 }