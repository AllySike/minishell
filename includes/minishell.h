#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include "libft.h"
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termcap.h>

# define PROMPT "e-bash >"// "minishell > "

// typedef struct list
// {
// 	int num;
// 	int *ptr;
// 	struct history * next;
// }				history;

typedef struct s_history
{
	void	*previous;
	char	*line;
	void	*next;
}				t_history;

typedef struct	s_minishell
{
	int		status;
	char	**envp;
	char    *line;
	t_history	history;
}				t_minishell;

void	line_parser(char *line, char *envp[]);

#endif
