/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:10:26 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/30 18:10:44 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	tokenize(char *content)
{
	if (ft_strlen(content) > 2)
		return (WORD);
	else if (ft_strcmp(content, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(content, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(content, "<") == 0)
		return (INPUT);
	else if (ft_strcmp(content, ">>") == 0)
		return (APPENDOUTPUT);
	else if (ft_strcmp(content, ">") == 0)
		return (OUTPUT);
	return (WORD);
}

static t_lexer	*new_node_lexer(void *content)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (0);
	new->content = NULL;
	new->token = tokenize(content);
	new->next = NULL;
	return (new);
}

static t_lexer	*last_node(t_lexer *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}

static void	add_node_lexer(t_lexer **lst, t_lexer *newnode)
{
	t_lexer	*last;

	if (*lst)
	{
		last = last_node(*lst);
		last->next = newnode;
	}
	else
		*lst = newnode;
}

t_lexer	*lexer_init(t_lexer **lexer, char **split, t_env *env)
{
	t_lexer	*first_node;
	t_lexer	*new;
	int		i;

	i = -1;
	while (split[++i])
	{
		new = new_node_lexer(split[i]);
		add_node_lexer(lexer, new);
	}
	i = -1;
	first_node = *lexer;
	while (*lexer)
	{
		(*lexer)->content = clean_str(split[++i], env);
		if ((*lexer)->content == NULL)
		{
			free_lexer(&first_node);
			free_tab(split);
			return (NULL);
		}
		*lexer = (*lexer)->next;
	}
	free_tab(split);
	return (first_node);
}
