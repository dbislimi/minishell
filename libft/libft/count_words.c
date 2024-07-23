/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:49:08 by dren              #+#    #+#             */
/*   Updated: 2024/05/07 14:23:50 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char const *s, char c)
{
	int	i;
	int	res;
	int	flag;

	i = 0;
	res = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!flag)
			{
				res++;
				flag = 1;
			}
		}
		else
			flag = 0;
		i++;
	}
	return (res);
}
