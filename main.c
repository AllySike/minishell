#include "includes/minishell.h"

int main(int args, char *argv[], char *envp[])
{
	char	*line;
	int		gnl;

	gnl = get_next_line(0, &line);
	while (gnl > 0)
	{
		printf("%s\n", line);
		fflush(stdout);
		free(line);
		gnl = get_next_line(0, &line);
	}
		printf("%s\n", line);
		fflush(stdout);
		free(line);
	return (0);

}
