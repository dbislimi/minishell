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

int	redirect_pipe(t_exe *exe, t_parser *cmd, int type)
{
	if (exe->fd_in != STDIN_FILENO && (type == 0 || type == 2))
	{
		if (dup2(exe->fd_in, STDIN_FILENO) == -1)
		{
			exe->fd_in = close(exe->fd_in);
			return (free_exe(exe, 0, 1, "Failed to redirect input"));
		}
		exe->fd_in = close(exe->fd_in);
	}
	if (cmd->next && (type == 1 || type == 2))
	{
		if (dup2(exe->fd[1], STDOUT_FILENO) == -1)
		{
			exe->fd[1] = close(exe->fd[1]);
			return (free_exe(exe, 0, 1, "Failed to redirect input"));
		}
		exe->fd[1] = close(exe->fd[1]);
	}
	return (0);
}

int	redirect_input(t_exe *exe, t_parser *cmd)
{
	char	*msg;

	if (!cmd)
		return (0);
	if (cmd->redirections->token == HEREDOC)
		return (here_doc(exe, cmd));
	else if (access(cmd->redirections->content, F_OK) != 0)
		return (free_exe(exe, 1, 1, ft_strjoinf(msg,
					": No such file or directory\n", 1)));
	exe->fd_tmp = open(cmd->redirections->content, O_RDONLY);
	if (exe->fd_tmp == -1)
		return (free_exe(exe, 0, 1, "Failed to open input file"));
	if (dup2(exe->fd_tmp, STDIN_FILENO) == -1)
	{
		exe->fd_tmp = close(exe->fd_tmp);
		return (free_exe(exe, 0, 1, "Failed to redirect input"));
	}
	exe->fd_tmp = close(exe->fd_tmp);
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

static void	here_doc_child(t_parser *cmd, int pipefd[2])
{
	char	*line;

	close(pipefd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(pipefd[1]);
			exit(0);
		}
		if (ft_strncmp(line, cmd->redirections->content,
				ft_strlen(cmd->redirections->content)) == 0
			&& ft_strlen(line) == ft_strlen(cmd->redirections->content))
		{
			free(line);
			break ;
		}
		line = ft_strjoinf(line, "\n", 1);
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipefd[1]);
	exit(0);
}

int	here_doc(t_exe *exe, t_parser *cmd)
{
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (free_exe(exe, 0, 1, "1"));
	exe->pid = fork();
	if (exe->pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (free_exe(exe, 0, 1, "1"));
	}
	if (exe->pid == 0)
		here_doc_child(cmd, pipefd);
	else
	{
		close(pipefd[1]);
		wait(NULL);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
		{
			close(pipefd[0]);
			return (free_exe(exe, 0, 1, "1"));
		}
		close(pipefd[0]);
	}
	return (0);
}
