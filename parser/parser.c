/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:30:11 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/10 19:08:04 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	(*is_builtin(char *cmd))(t_env *env, struct s_parser *parser)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (my_echo);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (my_cd);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (my_pwd);
	else if (ft_strcmp(cmd, "export") == 0)
		return (my_export);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (my_unset);
	else if (ft_strcmp(cmd, "env") == 0)
		return (my_env);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (my_exit);
	return ((void *)0);
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
	new->cmd = build_command(lexer);
	new->builtin = is_builtin(new->cmd[0]);
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

void	parser_init(t_parser **parser, t_lexer *lexer)
{
	int	cmds;

	cmds = count_pipes(lexer) + 1;
	while (cmds--)
	{
		if (lexer == NULL || lexer->token == PIPE)
		{
			printf("Error: unexpected token '|'\n");
			free_parser(parser);
			break ;
		}
		add_node_parser(parser, new_node_parser(lexer));
		if (cmds == 0)
			break ;
		while (lexer->token != PIPE)
			lexer = lexer->next;
		lexer = lexer->next;
	}
}
