/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:18:21 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/14 11:25:56 by dbislimi         ###   ########.fr       */
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


char	**build_command(t_lexer *lexer)
{
	char	**cmd;
	int		i;
	int		len;

	i = -1;
	if (!lexer)
		return (NULL);
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

// void	detach_from_lexer(t_lexer **lexer)
// {
// 	t_lexer	*temp;
	
// 	if ((*lexer)->next == NULL)
// 	{
// 		*lexer = (*lexer)->prev;
// 		return ;
// 	}
// 	if ((*lexer)->prev != NULL)
// 		(*lexer)->prev->next = (*lexer)->next->next;
// 	else
// 		temp = (*lexer)->next->next;
// 	(*lexer)->next->prev = (*lexer)->prev;
// 	(*lexer)->prev = NULL;
// 	(*lexer)->next->next = NULL;
// 	*lexer = temp;
// }

// t_lexer	*find_redirection(t_lexer **lexer)
// {
// 	t_lexer	*redirection;
	
// 	while ((*lexer) && (*lexer)->token != PIPE)
// 	{
// 		if ((*lexer)->token == OUTPUT || (*lexer)->token == APPENDOUTPUT)
// 		{
// 			redirection = *lexer;
// 			detach_from_lexer(lexer);
// 			return (redirection);
// 		}
// 		(*lexer) = (*lexer)->next;
// 	}
// 	return (NULL);
// }
