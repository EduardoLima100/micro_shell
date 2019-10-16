# micro_shell

O objetivo deste trabalho é implementar um micro shell para sistemas Linux chamado msh.

Os comandos desenvolvimentos:

- lista ou dir:
Chama o comando listar (/bin/ls). Pode ter um argumento com o nome do diretório.

- historico:
Mostra o histórico dos últimos dez comandos.

- mostra:
Mostra o conteúdo de um arquivo com o programa cat (/bin/cat). Recebe como argumento o nome do arquivo.

- espera ou pausa:
Tem como argumento o tempo em segundos que deve esperar antes de continuar.

- tempo ou agora:
Mostra data e hora usando o comando date.

- imprime:
Apenas imprime na tela o conteúdo do argumento, semelhante ao comando echo.

- executa:
Recebe como argumento o programa a ser executado.

- sair:
Termina o programa com a função exit().
