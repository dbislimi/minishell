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

int	free_all_exe(t_exe *exe, int is_malloc, int error, char *message)
{
	exe->env_tab = free_all_split(exe->env_tab);
	if (access(FILE_TEMP, 0) == 0)
		unlink(FILE_TEMP);
	if (exe->path)
		exe->path = ft_free(exe->path);
	if (exe->split)
		exe->split = free_all_split(exe->split);
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
	if (!cmd)
		return (0);
	if (cmd->redirections && cmd->redirections->token == INPUT)
	{
		exe->fd[0] = open(cmd->redirections->content, O_RDONLY);
		if (exe->fd[0] == -1)
			return (free_all_exe(exe, 0, 1, "Failed to open input file"));
		if (dup2(exe->fd[0], STDIN_FILENO) == -1)
			return (free_all_exe(exe, 0, 1, "Failed to redirect input"));
		close(exe->fd[0]);
	}
	else if (cmd->redirections && cmd->redirections->token == HEREDOC)
		return (here_doc(exe, cmd));
	else if (cmd->prev)
	{
		printf("redirect_input\n");
		if (dup2(exe->fd[0], STDIN_FILENO) == -1)
			return (free_all_exe(exe, 0, 1,
					"Failed to redirect input to pipe"));
		close(exe->fd[0]);
		close(exe->fd[1]);
	}
	return (0);
}

int	redirect_output(t_exe *exe, t_parser *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->redirections && (cmd->redirections->token == OUTPUT
			|| cmd->redirections->token == APPENDOUTPUT))
	{
		if (cmd->redirections->token == APPENDOUTPUT)
			exe->fd[1] = open(cmd->redirections->content,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			exe->fd[1] = open(cmd->redirections->content,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (exe->fd[1] == -1)
			return (free_all_exe(exe, 0, 1, "Failed to open output file"));
		if (dup2(exe->fd[1], STDOUT_FILENO) == -1)
			return (free_all_exe(exe, 0, 1, "Failed to redirect output"));
	}
	else if (cmd->next)
	{
		if (dup2(exe->fd[1], STDOUT_FILENO) == -1)
			return (free_all_exe(exe, 0, 1,
					"Failed to redirect output to pipe"));
	}
	else
		return (0);
	close(exe->fd[0]);
	close(exe->fd[1]);
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
		return (free_all_exe(exe, 0, 1, "Failed to allocate memory\n"));
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
		return (free_all_exe(exe, 1, 127,
				ft_strjoinf("zsh: command not found: ", cmd, 0)));
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

	exe->input_fd = open(FILE_TEMP, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (exe->input_fd == -1)
		return (free_all_exe(exe, 0, 1, "1"));
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (free_all_exe(exe, 0, 1, "1"));
		if (ft_strncmp(line, cmd->redirections->content,
				ft_strlen(cmd->redirections->content)) == 0
			&& ft_strlen(line) == ft_strlen(cmd->redirections->content))
			break ;
		write(exe->input_fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(exe->input_fd);
	exe->input_fd = open(FILE_TEMP, O_RDONLY);
	if (cmd->cmd && dup2(exe->input_fd, STDIN_FILENO) == -1)
		return (free_all_exe(exe, 0, 1, "1"));
	return (close(exe->input_fd));
}
