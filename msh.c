
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>

int msh_lista(char **args);		//ls
int msh_mostra(char **args);	//cat
int msh_espera(char **args);	//sleep()
int msh_tempo(char **args);		//date
int msh_imprime(char **args);	//echo
int msh_executa(char **args);	
int msh_sair(char **args);		//exit

char *funcoes_str[] = {
	"lista",
	"dir",
	"mostra",
	"espera",
	"pausa",
	"tempo",
	"agora",
	"imprime",
	"executa",
	"sair"
};

int (*funcoes_end[])(char **) = {
	&msh_lista,
	&msh_lista,
	&msh_mostra,
	&msh_espera,
	&msh_espera,
	&msh_tempo,
	&msh_tempo,
	&msh_imprime,
	&msh_executa,
	&msh_sair
};

int funcoes_num() {
  return sizeof(funcoes_str) / sizeof(char *);
}

int msh_lista(char** args)
{
	pid_t pid;

	args[0] = "ls";

	pid = fork();
	switch(pid)
  	{
    case -1:
      exit(EXIT_FAILURE);
    case 0:
      execvp(args[0], args);
      break;
    default:
      wait(NULL);
      break;
  	}
	
	return 1;
}

int msh_mostra(char** args)
{
	pid_t pid;

	args[0] = "cat";

	pid = fork();
	switch(pid)
  	{
    case -1:
      exit(EXIT_FAILURE);
    case 0:
      execvp(args[0], args);
      break;
    default:
      wait(NULL);
      break;
  	}
	
	return 1;
}

int msh_espera(char** args)
{
	pid_t pid;

	args[0] = "sleep";

	pid = fork();
	switch(pid)
  	{
    case -1:
      exit(EXIT_FAILURE);
    case 0:
      execvp(args[0], args);
      break;
    default:
      wait(NULL);
      break;
  	}
	
	return 1;
}

int msh_tempo(char** args)
{
	pid_t pid;

	args[0] = "date";

	pid = fork();
	switch(pid)
  	{
    case -1:
      exit(EXIT_FAILURE);
    case 0:
      execvp(args[0], args);
      break;
    default:
      wait(NULL);
      break;
  	}
	
	return 1;
}

int msh_imprime(char** args)
{
	pid_t pid;

	args[0] = "echo";

	pid = fork();
	switch(pid)
  	{
    case -1:
      exit(EXIT_FAILURE);
    case 0:
      execvp(args[0], args);
      break;
    default:
      wait(NULL);
      break;
  	}
	
	return 1;
}

int msh_executa(char** args)
{
	pid_t pid;
	char *comando;
	comando = malloc(sizeof(args[1])+2*sizeof(char));


	strcat(comando,"./");
	
	strcat(comando, args[1]);

	pid = fork();
	switch(pid)
  	{
    case -1:
      exit(EXIT_FAILURE);
    case 0:
      execvp(comando, args);
      break;
    default:
      wait(NULL);
      break;
  	}
	
	return 1;
}

int msh_sair(char **args)
{
	return 0;
}

int executar(char **args)
{
	int i;

	if(args[0] == NULL)
	{
		return 1;
	}

	for(i = 0; i < funcoes_num(); i++)
	{
		if(strcmp(args[0], funcoes_str[i]) == 0)
		{
			return (*funcoes_end[i])(args);
		}
	}
}

#define RL_BUFSIZE 1024
char * ler_linha(void)
{
  int bufsize = RL_BUFSIZE;
  int posicao = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "msh: erro de alocação\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    c = getchar();

    if (c == EOF) {
      exit(EXIT_SUCCESS);
    } else if (c == '\n') {
      buffer[posicao] = '\0';
      return buffer;
    } else {
      buffer[posicao] = c;
    }
    posicao++;

    // If we have exceeded the buffer, reallocate.
    if (posicao >= bufsize) {
      bufsize += RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "msh: erro de alocação\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"
char **separa_liha(char *linha)
{
	int bufsize = TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if(!tokens)
	{
		fprintf(stderr, "msh: erro de alocação\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(linha, TOK_DELIM);
	while(token != NULL)
	{
		tokens[position] = token;
		position++;

		if(position >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if(!tokens)
			{
				fprintf(stderr, "msh: erro de alocação\n");
				exit(EXIT_FAILURE);
			}
		}

		token  = strtok(NULL, TOK_DELIM);
	}

	tokens[position] = NULL;
	return tokens;
}

void repeticao(void)
{
	char *linha;
	char **args;
	int status;

	do
	{
		printf("msh> ");
		linha = ler_linha();
		args = separa_liha(linha);
		status = executar(args);

		free(linha);
		free(args);
	}while(status);
}

int main(int argc, char **argv)
{
	repeticao();

	return EXIT_SUCCESS;
}