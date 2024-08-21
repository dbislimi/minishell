/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:25:33 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/05 19:38:46 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_target_dir(t_env *env, t_parser *parser)
{
	char	*dir;

	dir = NULL;
	if (parser->cmd[1] == NULL || strcmp(parser->cmd[1], "~") == 0)
	{
		dir = find_value("HOME", env);
		if (!dir)
			write(2, "minishell: cd: HOME not set\n", 23);
	}
	else if (strcmp(parser->cmd[1], "-") == 0)
	{
		dir = find_value("OLDPWD", env);
		if (!dir)
			write(2, "minishell: cd: OLDPWD not set\n", 25);
		else
			printf("%s\n", dir);
	}
	else
		dir = parser->cmd[1];
	return (dir);
}

int	my_cd(t_env **env, t_parser *parser)
{
	char	*temp;
	char	*dir;

	dir = get_target_dir(*env, parser);
	if (!dir)
		return (1);
	if (chdir(dir) != 0)
	{
		write(STDERR_FILENO, "minishell: cd: ", 10);
		write(STDERR_FILENO, dir, ft_strlen(dir));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
		return (1);
	}
	temp = find_value("PWD", *env);
	temp = ft_strjoinf("OLDPWD=", temp, 0);
	add_node(env, new_node(temp));
	free(temp);
	temp = ft_strjoinf("PWD=", getcwd(NULL, 0), 2);
	add_node(env, new_node(temp));
	free(temp);
	return (0);
}
