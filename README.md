# mini-bash


<p align="center">
  <img src="https://github.com/mcombeau/mcombeau/blob/main/42_badges/minishelle.png" alt="Emblema do projeto Minishell 42"/>
</p>

O Mini Shell ou Mini Bash é um projeto desenvolvido em linguagem de programação C que tem como objetivo recriar algumas funcionalidades do Bash Unix-Like. Ele implementa redirecionamentos e pipes, bem como expansões de variáveis de ambiente e os comandos internos `cd`, `echo`, `env`, `exit`, `export`, `pwd` e `unset` que são algumas built-ins.

Este projeto foi desenvolvido em dupla com a [Fernanda Caetano](https://github.com/FernandaMatt)
 e foi uma experiência incrível para ambos. Aprendemos muitas coisas juntos, desde técnicas de programação até habilidades de comunicação. Discutimos bastante sobre as diferentes formas de implementar as soluções de nossos problemas e, em conjunto, encontramos as melhores soluções para o projeto.


## Uso
Clone o repositório:
``` 
git clone https://github.com/michaelrodriguess/mini-bash.git
```
Para compilar:

``` shell
cd minishell && make
```
Para executar o programa:
``` shell
./minishell
```
Um prompt aparecerá. Você pode inserir seus comandos para serem executados.

## Recursos Suportados
Minishell é um programa de shell em miniatura baseado no Bash. Minishell suporta:

* Exibição do prompt
* Histórico de comandos (setas para cima e para baixo)
* Executáveis do sistema disponíveis no ambiente (`ls `, `cat`, `grep`, etc.)
* Executáveis locais (`./minishell`)
* Comandos internos:
  * ` echo ` (e opção `-n` )
  * ` cd ` (apenas com um caminho relativo ou absoluto)
  * ` pwd ` (sem opções)
  * ` export ` (sem opções)
  * ` unset ` (sem opções)
  * ` env ` (sem opções ou argumentos)
  * ` exit ` (com número de saída, mas sem outras opções)
* Pipes ` | ` que redirecionam a saída de um comando para a entrada do próximo
* Redirecionamentos:
  * ` > ` redireciona a saída
  * ` >> ` redireciona a saída em modo de anexo
  * ` < ` redireciona a entrada
  * ` <<  DELIMITADOR` exibe um novo prompt, lê a entrada do usuário até alcançar `DELIMITADOR`, redireciona a entrada do usuário para a entrada do comando (não atualiza o histórico)
* Variáveis de ambiente (ou seja, `$USER` ou `$VAR`) que se expandem para seus valores.
  * `$?` se expande para o status de saída da última tubulação em primeiro plano executada.
* Sinais de teclado do usuário:
  * `ctrl-c` exibe uma nova linha de prompt.
  * `ctrl-d` sai do minishell
  * `ctrl-\` não faz nada
No entanto, Minishell não suporta `\`, `;`, `&&`, `||` ou wildcards.

by ``microtano`` (`microdri` | `fcaetano`)

