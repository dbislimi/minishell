/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:21:42 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/30 18:27:55 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	handle_dollar(char *clean, char **tab, char *env_value)
{
	if (env_value == NULL)
		return (0);
	ft_strcat(clean, env_value);
	++*tab;
	while (ft_isalnum(**tab) && **tab != '"')
		++*tab;
	return (ft_strlen(env_value));
}

size_t	count_dollar(char *str, t_env *env)
{
	char	*value;

	value = find_value(str, env);
	if (value == NULL)
		return (0);
	return (ft_strlen(value));
}
