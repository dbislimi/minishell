/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:03:31 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/02 19:35:55 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*lexer(t_lexer *list, char *str, t_env *env)
{
	char	**split;

	split = ft_split_lexer(str);
	if (split == NULL)
		return (NULL);
	list = lexer_init(&list, split, env);
	free_tab(split);
	if (list == NULL)
		return (NULL);
	print_lexer(list);
	return (list);
}
