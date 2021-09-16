#include "minishell.h"

static void	redir_operator(char *str, t_processor *processor)
{
	if (processor->curr)
	{
		append_array(&processor->words_array, &processor->curr);
		processor->curr = NULL;
	}
	processor->curr = append_arg(&processor->curr, '\n');
	processor->curr = append_arg(&processor->curr, str[processor->i]);
	processor->curr = append_arg(&processor->curr, str[processor->i + 1]);
	processor->curr = append_arg(&processor->curr, '\n');
	append_array(&processor->words_array, &processor->curr);
	processor->curr = NULL;
	processor->i++;
}

static void	operators_utils(char *str, t_processor *processor)
{
	if (str[processor->i] == '>' && str[processor->i + 1] == '>')
		redir_operator(str, processor);
	else if (str[processor->i] == '\'')
		processor->sngl_qts = 1;
	else if (str[processor->i] == '\"')
		processor->dbl_qts = 1;
	else if (str[processor->i] == '\\')
	{
		processor->i++;
		processor->curr = append_arg(&processor->curr, str[processor->i]);
	}
	else if (str[processor->i] == ' ')
	{
		append_array(&processor->words_array, &processor->curr);
		processor->curr = NULL;
	}
}


static int	operators(char *str, t_processor *processor)
{
	if ((str[processor->i] == '>' && str[processor->i + 1] != '>')
		|| str[processor->i] == '<' || str[processor->i] == '|'
		|| str[processor->i] == ';')
	{
		if (processor->curr)
		{
			append_array(&processor->words_array, &processor->curr);
			processor->curr = NULL;
		}
		processor->curr = append_arg(&processor->curr, '\n');
		processor->curr = append_arg(&processor->curr, str[processor->i]);
		processor->curr = append_arg(&processor->curr, '\n');
		append_array(&processor->words_array, &processor->curr);
		processor->curr = NULL;
		return (1);
	}
	else if ((str[processor->i] == '>' && str[processor->i + 1] == '>') ||
			str[processor->i] == '\'' || str[processor->i] == '\"' ||
			str[processor->i] == '\\' || str[processor->i] == ' ')
	{
		operators_utils(str, processor);
		return (1);
	}
	return (0);
}

int	symb_handle(char *str, t_list *envp, int ret, t_processor *processor)
{
	while (str[processor->i] == ' ' && !processor->curr)
		processor->i++;
	if (operators(str, processor))
		NULL;
	else if (str[processor->i] == '$' && str[processor->i + 1] == '?')
	{
		processor->i += 2;
		processor->tmp = processor->curr;
		if (processor->curr)
			processor->curr = ft_strjoin(processor->curr, ft_itoa(ret));
		else
			processor->curr = ft_strdup(ft_itoa(ret));
		if (processor->tmp)
			free(processor->tmp);
		return (1);
	}
	else if (str[processor->i] == '$' && str[processor->i + 1])
		return (handle_dollar(str, processor, envp));
	else
		processor->curr =
				append_arg(&processor->curr, str[processor->i]);
	return (0);
}

