/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:48:44 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/10 18:15:14 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	skip_word(const char *s, char c)
{
	size_t	i;
	int		backslash;

	if (c)
		i = 1;
	else
		i = 0;
	backslash = 0;
	handle_backslash(s[i], &backslash);
	while (s[i] && !(is_quote(s[i], backslash) && (!c || s[i] == c)))
	{
		++i;
		handle_backslash(s[i], &backslash);
	}
	return (i);
}
