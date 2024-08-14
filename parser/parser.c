/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:30:11 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/14 14:12:15 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	(*is_builtin(char **cmd))(t_env *env, struct s_parser *parser)
{
	if (cmd == NULL)
		return ((void *)0);
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (my_echo);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (my_cd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (my_pwd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (my_export);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (my_unset);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (my_env);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (my_exit);
	return ((void *)0);
}

static t_parser	*new_node_parser(t_lexer *lexer, t_parser_utils utils)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		return (0);
	new->redirections = utils.redirections;
	new->nb_of_redirections = utils.nb_of_redirections;
	new->cmd = build_command(lexer);
	new->builtin = is_builtin(new->cmd);
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

void	rm_from_lexer(t_lexer **lexer, int index)
{
	t_lexer	*node;
	t_lexer	*prev;
	t_lexer *next;

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

void	add_new_redirection(t_lexer *to_add, t_lexer **lexer, t_parser_utils *utils)
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
		else
			error = ft_strdup("`>>'");
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
		token_error(to_remove->next, utils);
	add_new_redirection(to_remove, lexer, utils);
	detach_redirections(lexer, utils);
}

void	parser_init(t_parser **parser, t_lexer **lexer, t_parser_utils *utils)
{
	t_lexer			*lxr;
	bool		i;
	int		cmds;

	i = 0;
	lxr = *lexer;
	cmds = count_pipes(lxr) + 1;
	while (cmds--)
	{
		utils->redirections = NULL;
		utils->nb_of_redirections = 0;
		detach_redirections(&lxr, utils);
		if (!i)
			*lexer = lxr;
		add_node_parser(parser, new_node_parser(lxr, *utils));
		if (cmds == 0)
			break ;
		while (lxr->token != PIPE)
			lxr = lxr->next;
		lxr = lxr->next;
		i = 1;
	}
	free_lexer(lexer);
}
