/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:25:33 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/05 19:38:46 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_cd(t_env *env, struct s_parser *parser)
{
	(void)env;
	(void)parser;
	printf("use of cd\n");
	return (1);
}
