
### Informações de cada código fonte localizado em /src
#### main.c:
 1. trace_observer

#### cli.c:
 1. find_separator
 2. print_usage
 3. parse_args

#### trace_runtime.c:
 1. TODO SEMANA 2:
	 1. launch_tracee
	 2. wait_for_initial_stop
 2. TODO SEMANA 3:
	 1. configure_trace_options 
	 2. resume_until_next_syscall
	 3. wait_for_syscall_stop
 3. TODO SEMANA 4:
	 1. fill_event_from_regs
	 2. trace_program

#### trace_helpers.c:
 1. read_child_string


#### student/formatter.c:
 1. student_debug_raw_event
 2. student_format_event (TODO SEMANA 5)

#### student/pairer.c:
 1. student_pair_syscall (TODO SEMANA 2)


Onde o programa começa:
- main

Onde o processo alvo é criado:
- launch_tracee no trace_runtime

Onde o runtime chama o callback:
- trace_observer na main


Os arquivos que o grupo deve modificar:
- trace_runtime.c
- formatter.c
- pairer.c

Qual TODO aparece no scaffolding:
- TODO Semana 2

Qual a dúvida tecnica: 
- Como o Ptrace interrompe processo durante a syscall