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

int	my_export(t_env *env, struct s_parser *parser)
{
	int	i;

	i = 0;
	while (parser->cmd[++i])
		add_node(&env, new_node(parser->cmd[i]));
	if (!parser->cmd[1])
		print_env(env, "export");
	return (1);
}
