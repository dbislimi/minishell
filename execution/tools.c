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

#include "../includes/execution.h"

t_exe	init_exe(t_env **env, t_parser *parser)
{
	t_exe	exe;

	exe.env_cpy = dup_env(*env);
	exe.env = env;
	exe.env_tab = convert_env_tab(*env);
	exe.parser = parser;
	exe.path = NULL;
	exe.fd[0] = 0;
	exe.fd[1] = 0;
	exe.fd_heredoc[0] = 0;
	exe.fd_heredoc[1] = 0;
	exe.error = 0;
	exe.fd_tmp = 0;
	exe.fd_in = 0;
	exe.i = 0;
	return (exe);
}

int	free_exe(t_exe *exe, int is_malloc, int error, char *message)
{
	if (exe->env_tab)
		exe->env_tab = free_all_split(exe->env_tab);
	if (exe->path)
		exe->path = ft_free(exe->path);
	if (error)
	{
		if (message && (*message == '1' || *message == '2'))
			ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", exe->path,
				strerror(errno));
		else if (message)
		{
			ft_fprintf(STDERR_FILENO, "minishell: %s", message);
			if (message[ft_strlen(message) - 1] != '\n')
				ft_fprintf(STDERR_FILENO, "\n");
		}
		if (is_malloc)
			free(message);
		return (error);
	}
	return (EXIT_SUCCESS);
}

void	check_bultins(t_exe *exe, t_parser *cmd)
{
	t_env	**used_env;

	used_env = exe->env;
	if (cmd->builtin == &my_export && cmd->cmd[1])
		used_env = exe->env_cpy;
	else if (cmd->builtin == &my_unset || cmd->builtin == &my_cd)
		used_env = exe->env_cpy;
	add_node_char("?", ft_itoa(cmd->builtin(used_env, cmd)), true,
		exe->env_cpy);
}
