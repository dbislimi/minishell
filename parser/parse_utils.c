/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:18:21 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/05 18:26:32 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_nodes(t_lexer *lexer)
{
	int	res;

	res = 0;
	while (lexer && lexer->token != PIPE)
	{
		++res;
		lexer = lexer->next;
	}
	return (res);
}

int	count_pipes(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer)
	{
		if (lexer->token == PIPE)
			++i;
		lexer = lexer->next;
	}
	return (i);
}

void	detach_from_lexer(t_lexer *lexer)
{
	if (lexer->next == NULL)
		return ;
	if (lexer->prev != NULL)
		lexer->prev->next = lexer->next->next;
	if (lexer->next != NULL)
		lexer->next->prev = lexer->prev;
	lexer->prev = NULL;
	lexer->next->next = NULL;
}

char	**build_command(t_lexer *lexer)
{
	char	**cmd;
	int		i;
	int		len;

	i = -1;
	len = count_nodes(lexer);
	cmd = malloc(sizeof(char *) * (len + 1));
	while (++i < len)
	{
		cmd[i] = ft_strdup(lexer->content);
		lexer = lexer->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

t_lexer	*find_redirection(t_lexer *lexer)
{
	//print_lexer(lexer);
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token == OUTPUT || lexer->token == APPENDOUTPUT)
		{
			detach_from_lexer(lexer);
			return (lexer);
		}
		lexer = lexer->next;
	}
	return (NULL);
}
