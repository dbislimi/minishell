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

int	redirect_input(t_exe *exe, t_parser *cmd)
{
	char	*msg;

	if (!cmd)
		return (0);
	if (cmd->redirections->token == HEREDOC)
		return (here_doc(exe, cmd));
	if (access(cmd->redirections->content, F_OK) != 0)
	{
		msg = ft_strjoin("minishell: ", cmd->redirections->content);
		return (free_exe(exe, 1, 1, ft_strjoinf(msg,
					": No such file or directory\n", 1)));
	}
	exe->fd_tmp = open(cmd->redirections->content, O_RDONLY);
	if (exe->fd_tmp == -1)
		return (free_exe(exe, 0, 1, "Failed to open input file"));
	if (dup2(exe->fd_tmp, STDIN_FILENO) == -1)
	{
		exe->fd_tmp = close(exe->fd_tmp);
		return (free_exe(exe, 0, 1, "Failed to redirect input"));
	}
	return (0);
}

int	redirect_output(t_exe *exe, t_parser *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->redirections->token == APPENDOUTPUT)
		exe->fd_tmp = open(cmd->redirections->content,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		exe->fd_tmp = open(cmd->redirections->content,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (exe->fd_tmp == -1)
		return (free_exe(exe, 0, 1, "Failed to open output file"));
	if (dup2(exe->fd_tmp, STDOUT_FILENO) == -1)
	{
		exe->fd_tmp = close(exe->fd_tmp);
		return (free_exe(exe, 0, 1, "Failed to redirect output"));
	}
	return (0);
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
	{
		exe->path = (ft_strdup(""));
		return (0);
	}
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
		return (free_exe(exe, 1, 127,
				ft_strjoinf("minishell: command not found: ", cmd, 0)));
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

int	here_doc(t_exe *exe, t_parser *cmd)
{
	char	*line;

	exe->fd_tmp = open(FILE_TEMP, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (exe->fd_tmp == -1)
		return (free_exe(exe, 0, 1, "1"));
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (free_exe(exe, 0, 1, "1"));
		if (get_ctrl(0) == 1)
		{
			free(line);
			exe->fd_tmp = close(exe->fd_tmp);
			free_exe(exe, 0, 0, NULL);
			get_ctrl(-1);
			return (1);
		}
		if (ft_strncmp(line, cmd->redirections->content,
				ft_strlen(cmd->redirections->content)) == 0
			&& ft_strlen(line) == ft_strlen(cmd->redirections->content))
			break ;
		write(exe->fd_tmp, line, ft_strlen(line));
		free(line);
	}
	free(line);
	exe->fd_tmp = close(exe->fd_tmp);
	exe->fd_tmp = open(FILE_TEMP, O_RDONLY);
	if (cmd->cmd && dup2(exe->fd_tmp, STDIN_FILENO) == -1)
		return (free_exe(exe, 0, 1, "1"));
	exe->fd_tmp = close(exe->fd_tmp);
	return (0);
}
