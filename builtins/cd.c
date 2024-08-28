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
			ft_fprintf(STDERR_FILENO, "minishell: cd: HOME not set\n");
	}
	else if (strcmp(parser->cmd[1], "-") == 0)
	{
		dir = find_value("OLDPWD", env);
		if (!dir)
			ft_fprintf(STDERR_FILENO, "minishell: cd: OLDPWD not set\n");
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

	if (parser->cmd[1] && parser->cmd[2])
	{
		ft_fprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
		return (1);
	}
	dir = get_target_dir(*env, parser);
	if (!dir)
		return (1);
	if (chdir(dir) != 0)
	{
		ft_fprintf(STDERR_FILENO, "minishell: cd: %s: %s\n", dir,
			strerror(errno));
		return (1);
	}
	temp = ft_strjoinf("OLDPWD=", find_value("PWD", *env), 0);
	add_node(env, new_node(temp), 0);
	free(temp);
	temp = ft_strjoinf("PWD=", getcwd(NULL, 0), 2);
	add_node(env, new_node(temp), 0);
	free(temp);
	return (0);
}
