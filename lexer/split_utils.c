/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 20:11:20 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/01 19:16:54 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_quotes(char c, int *res, t_flag *flag)
{
	if (c == '"' && flag->d_quote == 0 && flag->sg_quote == 0)
	{
		printf("d quote open\n");
		flag->d_quote = 1;
	}
	else if (c == '"' && flag->d_quote == 1)
	{
		++*res;
		printf("d quote close\n");
		flag->d_quote = 0;
	}
	else if (c == '\'' && flag->sg_quote == 0 && flag->d_quote == 0)
	{
		printf("s quote open\n");
		flag->sg_quote = 1;
	}
	else if (c == '\'' && flag->sg_quote == 1)
	{
		++*res;
		flag->sg_quote = 0;
		printf("s quote close\n");
	}
}

void	is_start_of_word(int *res, t_flag f, bool *flag)
{
	if (*flag == 0 && !(f.d_quote || f.sg_quote))
	{
		*flag = 1;
		++*res;
	}
}

void	found_quote(t_index *idx, const char *s, bool *flag)
{
	int	backslash;

	backslash = 0;
	if (s[idx->start] == '"')
	{
		idx->end = idx->start + 1;
		handle_backslash(s[idx->end], &backslash);
		while (s[idx->end] && !(s[idx->end] == '"' && backslash == 0))
		{
			++idx->end;
			handle_backslash(s[idx->end], &backslash);
		}
	}
	else
	{
		idx->end = idx->start + 1;
		while (s[idx->end] && !(s[idx->end] == '\''))
			++idx->end;
	}
	++idx->end;
	*flag = 1;
}

void	found_word(t_index *idx, const char *s, bool *flag)
{
	while (s[idx->end] && (!is_whitespace(s[idx->end])
			&& !(s[idx->end] == '"' || s[idx->end] == '\'')))
		++idx->end;
	*flag = 0;
}
