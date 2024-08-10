/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:10:26 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/10 18:15:05 by dbislimi         ###   ########.fr       */
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

static t_lexer	*new_node_lexer(void *content, t_env *env, int i)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (0);
	new->token = tokenize(content);
	if (new->token == 0)
		new->content = clean_str(content, env);
	else
		new->content = NULL;
	if (new->token == 0 && new->content == NULL)
		new->index = -1;
	else
		new->index = i;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lexer	*last_node(t_lexer *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}

static t_lexer	*add_node_lexer(t_lexer **lst, t_lexer *newnode)
{
	t_lexer	*last;

	if (*lst)
	{
		last = last_node(*lst);
		last->next = newnode;
		newnode->prev = last;
	}
	else
		*lst = newnode;
	return (newnode);
}

void	lexer_init(t_lexer **lexer, char **split, t_env *env)
{
	t_lexer	*last_node;
	int		i;

	i = -1;
	while (split[++i])
	{
		last_node = add_node_lexer(lexer, new_node_lexer(split[i], env, i));
		if (last_node->index == -1)
		{
			free_lexer(lexer);
			return ;
		}
	}
}
