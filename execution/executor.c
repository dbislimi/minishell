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

static int	redirect(t_exe *exe, t_parser *cmd)
{
	int	res;

	res = 0;
	while(cmd->redirections)
	{
		res = redirect_input(exe, cmd);
		if (cmd->redirections && cmd->redirections->token == HEREDOC)
			res = here_doc(exe, cmd);
		if (res != 0)
			return (res);
		res = redirect_output(exe, cmd);
		if (res != 0)
			return (res);
		cmd->redirections = cmd->redirections->next;
	}
	return (0);
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
		return (cmd->builtin(exe->env, cmd));
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
		return (0);
	}
}

void	execute_child(t_exe *exe, t_parser *cmd)
{
	int	res;

	res = redirect(exe, cmd);
	if (res != 0)
		exit(res);
	if (cmd->cmd)
	{
		res = get_path_cmd(exe, cmd->cmd[0]);
		if (res != 0)
			exit(res);
		res = execve(exe->path, cmd->cmd, exe->env_tab);
		if (res == -1)
		{
			free_exe(exe, 0, 1, "1");
			exit(1);
		}
		exe->split = free_all_split(exe->split);
	}
}

void	execute_parent(t_exe *exe, t_parser *cmd)
{
	t_parser	*tmp;

	if (cmd->next)
	{
 		execute_pipeline(exe, cmd->next);
		close(exe->fd[0]);
		close(exe->fd[1]);
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
	exe.split = NULL;
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
