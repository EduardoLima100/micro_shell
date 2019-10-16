#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0

int main(int argc, char** argv)
{
    pid_t pid;         // PID do processo
    bool msh = true, app = false;  // Flag utilizada para sair do msh
    char *args[2];     // argumentos do comando
    //char entrada[40];  // salva os caracteres lidos do terminal
    char prog_dest[30]; //usado para colocar o endereço dos aplicativos do Ubuntu

    char comando[20], argumento[20];

    while(msh){
        printf("msh>");
        
        scanf("%s%s", comando, argumento);

        //fgets(entrada, 40, stdin);

        //comando = strtok(entrada, " \n");
        //argumento = strtok(NULL, "e \n");

        //printf("\n%s\n", argumento);
        //comando = strtok(entrada," ,-");
        //argumento = strtok(NULL, " ,-");
        //lixo = strtok(NULL, " ,-");

        //printf ("%s\n",argumento);
        if(strcmp(comando, "lista") == 0){
            args[0] = "/bin/ls";
            args[1] = NULL;
        }
        else if(strcmp(comando, "mostra") == 0){
            args[0] = "/bin/cat";
            args[1] = argumento;
            //printf("\n%s\n", argumento);
        }
        else if(strcmp(comando, "espera") == 0){
            args[0] = "/bin/sleep";
            args[1] = argumento;
        }
        else if(strcmp(comando, "tempo") == 0){
            args[0] = "/bin/date";
            args[1] = NULL;
        }
        else if(strcmp(comando, "imprime") == 0){
            args[0] = "/bin/echo";
            args[1] = argumento;
        }
        else if(strcmp(comando, "executa") == 0){
            app = true;                     //flag usada para selecionar o execlp
            strcpy(prog_dest,"/usr/bin/");  //endereço dos aplicativos Ubuntu
            strcat(prog_dest,argumento);    //concatena o nome do aplicativo com o endereco

            args[0] = prog_dest;            //args[0] recebe "/usr/bin/aplicativo_chamado"
            //args[0] = "/usr/bin/firefox";
            args[1] = NULL;
        }
        else if(strcmp(comando, "sair") == 0){
            msh = false;
            args[0] = "/bin/exit";
            args[1] = NULL;
        }
        else{
            printf("%s: comando nao encontrado\n", comando);
            args[0] = NULL;
            args[1] = NULL;
        }
        args[2] = NULL;
        pid = fork();
        switch(pid)
        {
            case -1:
                printf("Erro!\n");
                exit(EXIT_FAILURE);
            case 0:
                // Sou o filho
                if(app){
                    app = false;
                    execlp(args[0], args, NULL);          //Utilizado apenas para abrir aplicativos
                }
                else{
                    execve(args[0], args, NULL);    //Utilizado para as outras funcoes
                }
                break;
            default:
                // Eu sou pai: espera o filho
                wait(NULL);
                break;
        }
    }
//*/
  return 0;
}
