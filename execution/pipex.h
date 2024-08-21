/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <theo@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:55:54 by thmouty           #+#    #+#             */
/*   Updated: 2024/07/17 14:56:39 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../includes/minishell.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define FILE_TEMP ".here_doc_tmp"

typedef struct s_exe
{
	t_env	**env;
	char	**env_tab;
	struct	s_parser *parser;

	char	*path;
	char	**envp;
	char	**split;
	int		fd[2];
	int		input_fd;
	int		error;
}			t_exe;

// pipex.c
int			execute_pipeline(t_exe *exe, t_parser *cmd);
void		execute_child(t_exe *exe, t_parser *cmd);
void		execute_parent(t_exe *exe, t_parser *cmd);

// tools.c
int			free_exe(t_exe *exe, int is_malloc, int error,
				char *message);
int			redirect_input(t_exe *exe, t_parser *cmd);
int			redirect_output(t_exe *exe, t_parser *cmd);
int			get_path_cmd(t_exe *exe, char *cmd);
void		create_path(t_exe *exe, char *cmd, char *path);
int			here_doc(t_exe *exe, t_parser *cmd);

#endif