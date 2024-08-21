/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <theo@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:55:54 by thmouty           #+#    #+#             */
/*   Updated: 2024/07/17 14:56:39 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	redirect_pipe(t_exe *exe, t_parser *cmd)
{
	if (exe->fd[0] != STDIN_FILENO)
	{
		if (dup2(exe->fd[0], STDIN_FILENO) == -1)
			return (free_exe(exe, 0, 1, "Failed to redirect input"));
		exe->fd[0] = close(exe->fd[0]);
	}
	if (cmd->next)
	{
		if (dup2(exe->fd[1], STDOUT_FILENO) == -1)
			return (free_exe(exe, 0, 1, "Failed to redirect input"));
		exe->fd[1] = close(exe->fd[1]);
	}
	return (0);
}

static int	redirect(t_exe *exe, t_parser *cmd)
{
	int		res;
	t_lexer	*tmp;

	res = 0;
	tmp = cmd->redirections;
	while (tmp)
	{
		if (tmp->token == INPUT || tmp->token == HEREDOC)
			res = redirect_input(exe, cmd);
		else if (tmp->token == OUTPUT || tmp->token == APPENDOUTPUT)
			res = redirect_output(exe, cmd);
		if (res != 0)
			return (res);
		tmp = tmp->next;
	}
	return (redirect_pipe(exe, cmd));
}
int	execute_pipeline(t_exe *exe, t_parser *cmd)
{
	int	res;

	if (cmd->next)
	{
		if (pipe(exe->fd) == -1)
			return (free_exe(exe, 0, 1, "1"));
	}
	if (cmd->builtin != NULL)
	{
		res = redirect(exe, cmd);
		if (res != 0)
			return (res);
		cmd->builtin(exe->env, cmd);
		execute_parent(exe, cmd);
	}
	else
	{
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (free_exe(exe, 0, 1, "1"));
		if (cmd->pid == 0)
			execute_child(exe, cmd);
		else
			execute_parent(exe, cmd);
	}
	return (0);
}

void	execute_child(t_exe *exe, t_parser *cmd)
{
	int		res;
	int		fd;
	char	*gnl;

	res = redirect(exe, cmd);
	if (res != 0)
		exit(res);
	if (cmd->cmd && cmd->cmd[0])
	{
		res = get_path_cmd(exe, cmd->cmd[0]);
		if (res != 0)
			exit(res);
		res = execve(exe->path, cmd->cmd, exe->env_tab);
		if (res == -1)
		{
			free_exe(exe, 0, 1, "1");
			res = 1;
		}
	}
	exe->fd[1] = close(exe->fd[1]);
	exit(res);
}

void	execute_parent(t_exe *exe, t_parser *cmd)
{
	t_parser	*tmp;

	if (cmd->next)
	{
		exe->fd[1] = close(exe->fd[1]);
		execute_pipeline(exe, cmd->next);
		exe->fd[0] = close(exe->fd[0]);
	}
	tmp = exe->parser;
	while (tmp)
	{
		waitpid(tmp->pid, &exe->error, 0);
		tmp = tmp->next;
	}
}

static t_exe	init_exe(t_env **env, t_parser *parser)
{
	t_exe	exe;

	exe.env = env;
	exe.env_tab = convert_env_tab(*env);
	exe.parser = parser;
	exe.path = NULL;
	exe.fd[0] = 0;
	exe.fd[1] = 0;
	exe.error = 0;
	return (exe);
}
int	executor(t_env **env, t_parser *parser)
{
	t_exe	exe;
	int		saved_stin;

	saved_stin = dup(STDIN_FILENO);
	exe = init_exe(env, parser);
	execute_pipeline(&exe, exe.parser);
	dup2(saved_stin, STDIN_FILENO);
	exe.env_tab = free_all_split(exe.env_tab);
	return (free_exe(&exe, 0, 0, NULL));
}
