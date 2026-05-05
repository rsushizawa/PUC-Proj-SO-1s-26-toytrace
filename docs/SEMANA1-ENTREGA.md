### Informações de cada código fonte localizado em /src

#### main.c (inicio do fluxo de execução):

- trace_observer: é a função de callback. Ela é chamada para fazer os logs dos eventos de syscall e juntar os pares de entrada e saida.

#### cli.c (biblioteca da interface de usuário):

- find_separator: acha o index do separador "--"
- print_usage: imprime o use da ferramenta com "--help"
- parse_args: função que engloba as função de cli

#### trace_runtime.c (biblioteca de funções para controle da execução dos dois processos)

- TODO SEMANA 2:
  1. launch_trace
  - faz o fork: o filho executa o programa requisitado e o pai aguarda interrupções de syscall e faz callback.
  2. wait_for_initial_stop
  - o pai espera o filho dar wait para então configurar o ptrace.

- TODO SEMANA 3:
  1. configure_trace_options
  - o pai configura o ptrace.
  2. resume_until_next_syscall
  - retoma para a execução do filho.
  3. wait_for_syscall_stop
  - o pai espera até uma interrupção de entrada/saida de syscall.
- TODO SEMANA 4:
  1. fill_event_from_regs
  - ler o registrador 0x80 para argumentos(entrada) ou retorno(saída) de uma syscall do ptrace.
  2. trace_program
  - função controladora do fluxo de execução do programa. executar o fill_event_from_regs e callback.

#### student/formatter.c

- student_debug_raw_event
  - utilizado para debug das syscalls interceptadas quando o programa está em estado --raw-events.
- student_format_event (TODO SEMANA 5)
  - formatação das syscalls já pareadas para saída do programa.

#### student/pairer.c:

- student_pair_syscall (TODO SEMANA 2)
  - pareia a entrada e saída de uma syscall.

#### trace_helpers.c:

- read_child_string

#### Perguntas

Onde o programa começa?

- main

Onde o processo alvo é criado?

- launch_tracee no trace_runtime

Onde o runtime chama o callback?

- trace_observer na main

Quais são os arquivos que o grupo deve modificar?

- trace_runtime.c
- formatter.c
- pairer.c

Qual TODO aparece primeiro no scaffolding?

- TODO Semana 2 launch_tracee

Qual a princícpal dúvida tecnica do grupo?

- Como o Ptrace interrompe processo durante a syscall
- Para que é utilizada a função read_child_string?

#### Fluxo de Execução do Programa

![Diagram](Proj_SO_Toytrace_dark.svg#gh-dark-mode-only)
![Diagram](Proj_SO_Toytrace_light.svg#gh-light-mode-only)
