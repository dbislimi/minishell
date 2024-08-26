/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <theo@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:55:54 by thmouty           #+#    #+#             */
/*   Updated: 2024/07/17 14:56:39 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_exe	init_exe(t_env **env, t_parser *parser)
{
	t_exe	exe;

	exe.env = env;
	exe.env_tab = convert_env_tab(*env);
	exe.parser = parser;
	exe.path = NULL;
	exe.fd[0] = 0;
	exe.fd[1] = 0;
	exe.error = 0;
	exe.fd_tmp = 0;
	exe.fd_in = 0;
	return (exe);
}

int	free_exe(t_exe *exe, int is_malloc, int error, char *message)
{
	if (access(FILE_TEMP, F_OK) == 0)
		unlink(FILE_TEMP);
	if (exe->path)
		exe->path = ft_free(exe->path);
	if (error)
	{
		if (message && (*message == '1' || *message == '2'))
		{
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
		}
		else if (message)
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, message, ft_strlen(message));
			if (message[ft_strlen(message) - 1] != '\n')
				write(STDERR_FILENO, "\n", 1);
		}
		if (is_malloc)
			free(message);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	get_path_cmd(t_exe *exe, char *cmd)
{
	char	**path;
	int		i;

	i = 0;
	while (exe->env_tab && exe->env_tab[i] && ft_strncmp(exe->env_tab[i],
			"PATH=", 5) != 0)
		i++;
	if (!exe->env_tab || !exe->env_tab[i])
		return (0);
	path = ft_split(exe->env_tab[i] + 5, ':');
	if (!path)
		return (free_exe(exe, 0, 1, "Failed to allocate memory\n"));
	i = -1;
	while (path[++i])
	{
		create_path(exe, cmd, path[i]);
		if (access(exe->path, 0) == 0)
			break ;
		exe->path = ft_free(exe->path);
	}
	path = free_all_split(path);
	if (!exe->path)
		return (free_exe(exe, 1, 127, ft_strjoinf("command not found: ", cmd,
					0)));
	return (0);
}

void	create_path(t_exe *exe, char *cmd, char *path)
{
	if (ft_strncmp(cmd, "/", 1) == 0 || ft_strncmp(cmd, "./", 2) == 0
		|| ft_strncmp(cmd, "../", 3) == 0)
		exe->path = ft_strdup(cmd);
	else
	{
		exe->path = ft_strjoinf(path, "/", 0);
		exe->path = ft_strjoinf(exe->path, cmd, 1);
	}
}
