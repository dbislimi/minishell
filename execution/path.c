/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <theo@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:55:54 by thmouty           #+#    #+#             */
/*   Updated: 2024/07/17 14:56:39 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	check_path(t_exe *exe, t_parser *cmd)
{
	struct stat	path_stat;
	int			res;

	res = get_path_cmd(exe, cmd->cmd[0]);
	if (res == 0)
	{
		if (stat(cmd->cmd[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
			return (free_exe(exe, 1, 126, ft_strjoin(cmd->cmd[0],
						": Is a directory")));
	}
	return (res);
}

int	get_path_cmd(t_exe *exe, char *cmd)
{
	char	**path;

	path = NULL;
	exe->i = 0;
	exe->tmp = find_value("PATH", *exe->env);
	if (exe->tmp)
	{
		path = ft_split(exe->tmp, ':');
		if (!path)
			return (free_exe(exe, 0, 1, "Failed to allocate memory\n"));
		exe->i = -1;
		while (path[++exe->i])
		{
			exe->error = create_path(exe, cmd, path[exe->i]);
			if (access(exe->path, F_OK) == 0 || exe->error)
				break ;
			exe->path = ft_free(exe->path);
		}
	}
	path = free_all_split(path);
	if (exe->error)
		return (exe->error);
	if (!exe->path)
		return (free_exe(exe, 1, 127, ft_joinf("%s: command not found", cmd)));
	return (0);
}

int	create_path(t_exe *exe, char *cmd, char *path)
{
	if (ft_strncmp(cmd, "/", 1) == 0 || ft_strncmp(cmd, "./", 2) == 0
		|| ft_strncmp(cmd, "../", 3) == 0)
	{
		exe->path = ft_strdup(cmd);
		if (access(exe->path, F_OK) != 0)
			return (free_exe(exe, 0, 127, "1"));
		if (access(exe->path, X_OK) != 0)
			return (free_exe(exe, 0, 126, "1"));
	}
	else
	{
		exe->path = ft_strjoinf(path, "/", 0);
		exe->path = ft_strjoinf(exe->path, cmd, 1);
	}
	return (0);
}
