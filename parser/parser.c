/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:30:11 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/02 20:37:47 by dbislimi         ###   ########.fr       */
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
	i = 0;
	while (cmd[i])
	{
		printf("cmd[%d]:%s\n", i, cmd[i]);
		++i;
	}
	return (cmd);
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

static t_parser	*new_node_parser(t_lexer *lexer)
{
	t_parser	*new;
	t_lexer		*redirection;
	
	redirection = find_redirection(lexer);
	if (redirection && redirection->next == NULL)
		return (0);
	new = malloc(sizeof(t_parser));
	if (!new)
		return (0);
	new->redirections = redirection;
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

static void	add_node_parser(t_parser **lst, t_parser *newnode)
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
	// t_parser	*prev;
	t_parser	*parser;
	int	cmds;

	// prev = NULL;
	parser = NULL;
	cmds = count_pipes(lexer) + 1;
	while (cmds--)
	{
		add_node_parser(&parser, new_node_parser(lexer));
		if (cmds == 0)
			break ;
		while (lexer->token != PIPE)
			lexer = lexer->next;
		lexer = lexer->next;
	}
}
