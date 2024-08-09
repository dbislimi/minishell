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
	add_node(&env, new_node(parser->cmd[1]));
	if (!parser->cmd[1])
		my_env(env, parser);
	return (1);
}
