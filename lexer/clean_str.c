/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:12:57 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/09 19:20:01 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*simple_clean(char *toclean)
{
	char	*clean_str;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (toclean && toclean[len + 1] != '\'')
		++len;
	printf("len : %zu\n", len);
	clean_str = malloc(sizeof(char) * (len + 1));
	if (!clean_str)
		return (NULL);
	++toclean;
	while (i < len)
		clean_str[i++] = *toclean++;
	clean_str[i] = '\0';
	return (clean_str);
}

static char	*clean(char *tab, t_env *env)
{
	char	*clean_str;
	size_t	len;
	size_t	i;

	i = 0;
	len = strlen2(tab, env, 0);
	clean_str = ft_calloc(len + 1, sizeof(char));
	if (!clean_str)
		return (NULL);
	if (*tab == '"')
		++tab;
	while (i < len)
	{
		if (*tab == '\\' && is_special_char(*(tab + 1)))
			++tab;
		else if (*tab == '$')
		{
			++tab;
			i += handle_dollar(clean_str, &tab, find_value(tab, env));
			continue ;
		}
		clean_str[i++] = *tab++;
	}
	clean_str[i] = '\0';
	return (clean_str);
}

static char	*clean2(char *tab, t_env *env)
{
	char	*clean_str;
	size_t	len;
	size_t	i;

	i = 0;
	len = strlen2(tab, env, 1);
	clean_str = ft_calloc(len + 1, sizeof(char));
	if (!clean_str)
		return (NULL);
	while (i < len)
	{
		if (*tab == '\\')
			++tab;
		else if (*tab == '$')
		{
			++tab;
			i += handle_dollar(clean_str, &tab, find_value(tab, env));
			continue ;
		}
		clean_str[i++] = *tab++;
	}
	clean_str[i] = '\0';
	return (clean_str);
}

char	*strjoinlexer(char const *s1, char *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	i = 0;
	j = 0;
	joined = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined)
		return (NULL);
	while (s1[i++])
		joined[i - 1] = s1[i - 1];
	while (s2[j])
		joined[i++ - 1] = s2[j++];
	joined[i - 1] = 0;
	free(s2);
	return (joined);
}

size_t	skip_word(const char *s, char c)
{
	size_t	i;
	int		backslash;

	i = 0;
	backslash = 0;
	handle_backslash(s[i], &backslash);
	printf("skib, %c\n", s[i]);
	while (s[i] && ((c == '\0' && !is_quote(s[i], backslash)) || (s[i] == c && !is_quote(s[i], backslash))))
	{
		printf("skip, %c -> backslash : %d\n", s[i], backslash);
		++i;
		handle_backslash(s[i], &backslash);
	}
	return (i);
}

char	*clean_str(char *str, t_env *env)
{
	size_t	len;
	char	*clean_str;

	len = 0;
	clean_str = NULL;
	while (str[len])
	{
		if (str[len] == '\'')
		{
			clean_str = strjoinlexer(clean_str, simple_clean(str + len));
			len += skip_word(str + len, '\'') + 2;
		}
		else if (str[len] == '"')
		{
			clean_str = strjoinlexer(clean_str, clean(str + len++, env));
			len += skip_word(str + len, '"') + 1;
		}
		else
		{
			clean_str = strjoinlexer(clean_str, clean2(str + len, env));
			printf("len: %zu\n", len);
			len += skip_word(str + len, '\0') + 1;
		}
		printf("clean_str : {%s}\nlen : %zu\nchar : %c\n", clean_str, len, str[len]);
	}
	return (clean_str);
}
