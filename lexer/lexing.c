/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:44:48 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/24 16:25:38 by dbislimi         ###   ########.fr       */
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

int	count_words_lexer(char const *s)
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
		if ((s[i] == '"' || s[i] == '\'') && !(i > 0 && s[i - 1] == '\\'))
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

static char	*fill_str_with(char const *s, int start, int end)
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

char	**ft_split(char const *s, char c)
{
	char		**split;
	int			size;
	int			i;
	int			end;
	int			start;

	i = 0;
	start = 0;
	size = count_words_lexer(s);
	split = malloc(sizeof(char *) * (size + 1));
	if (!split)
		return (NULL);
	while (i < size)
	{
		while (s[start] == c && s[start])
			start++;
		end = start + 1;
		while (s[end] != c && s[end])
			end++;
		split[i] = fill_str_with(s, start, end);
		start = end + 1;
		i++;
	}
	split[i] = NULL;
	return (split);
}

// void	lexing(char *str)
// {
// 	t_lexer	*lexer;
// }

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	printf("%d\n", count_words_lexer(av[1]));
// }