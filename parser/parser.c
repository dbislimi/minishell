/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:30:11 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/01 16:42:06 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**build_command(t_lexer *lexer)
{
	
}
void	detach_from_lexer(t_lexer *lexer)
{
	lexer->prev->next = lexer->next->next;
	lexer->next->next->prev = lexer->prev;
	lexer->prev = NULL;
	lexer->next->next = NULL;
}

t_lexer	*find_redirection(t_lexer *lexer)
{
	while (lexer->token != PIPE)
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

static t_parser	*new_node_lexer(t_lexer *lexer, int i)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		return (0);
	new->redirections = find_redirection(lexer);
	new->str = build_command(lexer);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static t_parser	*last_node(t_parser *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}

static void	add_node_lexer(t_parser **lst, t_parser *newnode)
{
	t_parser	*last;

	if (*lst)
	{
		last = last_node(*lst);
		last->next = newnode;
		newnode->prev = last;
	}
	else
		*lst = newnode;
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

void	parser(t_lexer *lexer)
{
	t_parser	*prev;
	t_parser	*parser;
	int	cmds;

	prev = NULL;
	cmds = count_pipes(lexer) + 1;
	while (cmds--)
	{
		add_node_parser(parser, new_node_parser(lexer));
	}
}
