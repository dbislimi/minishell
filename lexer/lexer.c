/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:03:31 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/10 19:41:35 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer(t_lexer **list, char *str, t_env *env)
{
	char	**split;

	split = ft_split_lexer(str);
	if (split == NULL)
		return ;
	lexer_init(list, split, env);
	free_tab(split);
	if (*list == NULL)
		return ;
	//print_lexer(*list);
}
