/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:44:48 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/28 18:02:49 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_words_lexer(char *s)
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
int	is_quote(char *s, t_index idx)
{
	return ((s[idx.start] == '"' && !(idx.start > 0 && s[idx.start - 1] == '\\')) || s[idx.start] == '\'');
}

static void	split_loop(int size, char *s, char **split)
{
	t_index	idx;
	bool	quote;
	int		i;

	i = 0;
	quote = 0;
	idx.start = 0;
	while (i < size)
	{
		while (s[idx.start] && is_whitespace(s[idx.start]))
			++idx.start;
		idx.end = idx.start + 1;
		printf("end : %d\n", idx.end);
		if (is_quote(s, idx))
			found_quote(&idx, s, &quote);
		else
			found_word(&idx, s, &quote);
		split[i] = fill_str_with(s, idx.start, idx.end);
		idx.start = idx.end;
		printf("c : %c\n", s[idx.start]);
		i++;
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
		free(s);
		return (NULL);
	}
	split = malloc(sizeof(char *) * (size + 1));
	if (!split)
		return (NULL);
	split_loop(size, s, split);
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