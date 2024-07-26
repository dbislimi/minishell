/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:44:48 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/26 18:31:08 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_quotes(char c, int *res, t_flag *flag)
{
	if (c == '"' && flag->d_quote == 0 && flag->sg_quote == 0)
		flag->d_quote = 1;
	else if (c == '"' && flag->d_quote == 1)
	{
		++*res;
		flag->d_quote = 0;
	}
	else if (c == '\'' && flag->sg_quote == 0 && flag->d_quote == 0)
		flag->sg_quote = 1;
	else if (c == '\'' && flag->sg_quote == 1)
	{
		++*res;
		flag->sg_quote = 0;
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

int	count_words_lexer(const char *s)
{
	int	i;
	int	res;
	t_flag f;
	bool	flag;

	i = 0;
	res = 0;
	flag = 0;
	f.d_quote = 0;
	f.sg_quote = 0;
	while (s[i])
	{
		if ((s[i] == '"' && !(i > 0 && s[i - 1] == '\\')) || s[i] == '\'')
			handle_quotes(s[i], &res, &f);
		else if (!is_whitespace(s[i]))
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

void	found_quote(t_index *idx, const char *s, bool *flag)
{
	if (s[idx->start] == '"')
	{
		idx->end = idx->start + 1;
		while (s[idx->end] && !(s[idx->end] == '"' && s[idx->end - 1] != '\\'))
			++idx->end;
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
	while (s[idx->end] && (!is_whitespace(s[idx->end]) && !(s[idx->end] == '"' || s[idx->end] == '\'')))
		++idx->end;
	*flag = 0;
}

char	**ft_split_lexer(const char *s)
{
	char		**split;
	int			size;
	int			i;
	t_index		idx;
	bool		quote;

	i = 0;
	quote = 0;
	idx.start = 0;
	size = count_words_lexer(s);
	if (size == -1)
	{
		printf("Error: check your quotes\n");
		return (NULL);
	}
	split = malloc(sizeof(char *) * (size + 1));
	if (!split)
		return (NULL);
	while (i < size)
	{
		while (s[idx.start] && is_whitespace(s[idx.start]))
			++idx.start;
		idx.end = idx.start + 1;
		if (((s[idx.start] == '"' && !(idx.start > 0 && s[idx.start - 1] == '\\') )|| s[idx.start] == '\''))
			found_quote(&idx, s, &quote);
		else
			found_word(&idx, s, &quote);
		split[i] = fill_str_with(s, idx.start, idx.end);
		if (quote)
			idx.start = idx.end + 1;
		else
			idx.start = idx.end;
		i++;
	}
	split[i] = NULL;
	return (split);
}
//" a   ." bjr"arv\"'sisi " ' \' "\"" salut\a\\tion
// void	lexing(char *str)
// {
// 	t_lexer	*lexer;
// }

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	printf("%d\n", count_words_lexer(av[1]));
// }