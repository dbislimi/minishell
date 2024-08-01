/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:10:26 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/01 18:41:52 by dbislimi         ###   ########.fr       */
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

static t_lexer	*new_node_lexer(void *content, int i)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (0);
	new->content = NULL;
	new->token = tokenize(content);
	new->index = i;
	new->next = NULL;
	new->prev = NULL;
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
		newnode->prev = last;
	}
	else
		*lst = newnode;
}
void	delete_empty_nodes(t_lexer **lexer)
{
	t_lexer	*temp;
	t_lexer	*first_node;
	
	first_node = NULL;
	while (*lexer)
	{
		if ((*lexer)->content[0] != '\0')
		{
			first_node = *lexer;
			break ;
		}
	}
	while ((*lexer))
	{
		temp = (*lexer)->next;
		if ((*lexer)->token == 0 && (*lexer)->content[0] == '\0')
		{
			printf("null\n");
			free((*lexer)->content);
			if ((*lexer)->prev != NULL)
				(*lexer)->prev->next = (*lexer)->next;
			if ((*lexer)->next != NULL)
				(*lexer)->next->prev = (*lexer)->prev;
			free((*lexer));
		}
		(*lexer) = temp;
	}
}

t_lexer	*lexer_init(t_lexer **lexer, char **split, t_env *env)
{
	t_lexer	*first_node;
	int		i;

	i = -1;
	while (split[++i])
		add_node_lexer(lexer, new_node_lexer(split[i], i));
	i = 0;
	first_node = *lexer;
	while (*lexer)
	{
		if ((*lexer)->token == 0)
		{
			(*lexer)->content = clean_str(split[i], env);
			if ((*lexer)->content == NULL)
			{
				free_lexer(&first_node);
				free_tab(split);
				return (NULL);
			}
		}
		*lexer = (*lexer)->next;
		++i;
	}
	// first_node = delete_empty_nodes(first_node);
	// if (first_node)
	// 	printf("%s\n", first_node->content);
	return (first_node);
}
