/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:03:16 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/15 16:47:07 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	rm_from_lexer(t_lexer **lexer, int index)
{
	t_lexer	*node;
	t_lexer	*prev;
	t_lexer	*next;

	node = *lexer;
	while (node && node->index != index)
		node = node->next;
	if (!node)
		return ;
	prev = node->prev;
	next = node->next;
	if (prev == NULL)
	{
		free(node);
		node = NULL;
		*lexer = next;
		if (next)
			(*lexer)->prev = NULL;
		return ;
	}
	node->prev->next = next;
	if (node->next)
		node->next->prev = prev;
	free(node);
	node = NULL;
}

void	add_new_redirection(t_lexer *to_add, t_lexer **lexer,
		t_parser_utils *utils)
{
	t_lexer	*newnode;
	int		i1;
	int		i2;

	newnode = new_node_lexer(to_add->next->content, to_add->token, 0);
	// if (!newnode)
	// 	ft_error();
	add_node_lexer(&utils->redirections, newnode);
	i1 = to_add->index;
	i2 = to_add->next->index;
	rm_from_lexer(lexer, i1);
	rm_from_lexer(lexer, i2);
	++utils->nb_of_redirections;
}

void	token_error(t_lexer *problem, t_parser_utils *utils)
{
	char	*error;

	if (!problem)
		error = ft_strdup("`newline'");
	else
	{
		if (problem->token == INPUT)
			error = ft_strdup("`<'");
		else if (problem->token == OUTPUT)
			error = ft_strdup("`>'");
		else if (problem->token == HEREDOC)
			error = ft_strdup("`<<'");
		else if (problem->token == APPENDOUTPUT)
			error = ft_strdup("`>>'");
		else
			error = ft_strdup("`|'");
	}
	printf("%s %s\n", SYNTAX_ERROR, error);
	free(error);
	free_lexer(&utils->lexer);
	free_parser(&utils->parser);
}

void	detach_redirections(t_lexer **lexer, t_parser_utils *utils)
{
	t_lexer	*to_remove;

	to_remove = *lexer;
	while (to_remove && to_remove->token == 0)
		to_remove = to_remove->next;
	if (!to_remove || to_remove->token == PIPE)
		return ;
	if (!to_remove->next || to_remove->next->token)
	{
		token_error(to_remove->next, utils);
		return ;
	}
	add_new_redirection(to_remove, lexer, utils);
	detach_redirections(lexer, utils);
}
