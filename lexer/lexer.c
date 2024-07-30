/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:03:31 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/30 19:11:36 by dbislimi         ###   ########.fr       */
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
	if (list == NULL)
		return (NULL);
	//print_lexer(list);
	return (list);
}
