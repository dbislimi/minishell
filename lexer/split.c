/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:44:48 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/10 18:13:09 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_words_lexer(char *s)
{
	int		i;
	int		res;
	t_flag	f;
	bool	flag;

	i = 0;
	res = 0;
	flag = 0;
	f.d_quote = 0;
	f.sg_quote = 0;
	f.backslash = 0;
	while (s[i])
	{
		handle_backslash(s[i], &f.backslash);
		if ((s[i] == '"' && f.backslash == 0) || s[i] == '\'')
			handle_quotes(s[i], &f);
		if (!is_whitespace(s[i]))
			is_start_of_word(&res, f, &flag);
		else if (!(f.d_quote || f.sg_quote))
			flag = 0;
		i++;
	}
	if (f.d_quote || f.sg_quote)
		return (-1);
	return (res);
}

static char	*fill_str_with(const char *s, int start, int end)
{
	char	*fill;
	int		i;

	i = 0;
	fill = malloc(sizeof(char) * (end - start + 1));
	if (!fill)
		return (NULL);
	while (start < end)
		fill[i++] = s[start++];
	fill[i] = 0;
	return (fill);
}

int	is_quote(char c, int backslash)
{
	return ((c == '"' && backslash == 0) || c == '\'');
}

static void	split_loop(int size, char *s, char **split)
{
	t_flag	f;
	t_index	idx;
	bool	quote;
	int		i;

	i = 0;
	f.backslash = 0;
	quote = 0;
	idx.start = 0;
	while (i < size)
	{
		handle_backslash(s[idx.start], &f.backslash);
		while (s[idx.start] && is_whitespace(s[idx.start]))
			++idx.start;
		idx.end = idx.start - 1;
		while (s[++idx.end] && (!is_whitespace(s[idx.end])))
		{
			handle_backslash(s[idx.end], &f.backslash);
			if (is_quote(s[idx.end], f.backslash))
				found_quote(&idx, s, &quote);
		}
		split[i++] = fill_str_with(s, idx.start, idx.end);
		idx.start = idx.end;
	}
	split[i] = NULL;
}

char	**ft_split_lexer(char *s)
{
	char		**split;
	int			size;

	size = count_words_lexer(s);
	if (size == -1)
	{
		printf("Error: check your quotes\n");
		return (NULL);
	}
	split = malloc(sizeof(char *) * (size + 1));
	if (!split)
		return (NULL);
	split_loop(size, s, split);
	return (split);
}
