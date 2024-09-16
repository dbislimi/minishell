/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:26:02 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/05 19:38:56 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_export(t_env **env, struct s_parser *parser)
{
	int	i;

	i = 0;
	while (parser->cmd[++i])
	{
		if (add_node(env, new_node(parser->cmd[i]), 0))
		{
			add_node_char("?", "1", false, env);
			return (1);
		}
	}
	if (!parser->cmd[1])
		print_export(*env);
	return (0);
}

void	add_node_char(char *name, char *value, bool is_free, t_env **env)
{
	char	*temp;

	temp = ft_joinf("%s=%s", name, value);
	add_node(env, new_node(temp), 1);
	free(temp);
	if (is_free)
		free(value);
}
