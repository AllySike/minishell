#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include "libft.h"
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "e-bash >"// "minishell > "

typedef struct list
{
	int num;
	int *ptr;
	struct history * next;
}				history;

void	line_parser(char *line, char *envp[]);

#endif
