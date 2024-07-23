/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:48:35 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/23 16:58:30 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(char *str, int option)
{
	if (option)
		printf("%s", str);
	else
		printf("%s\n", str);
	rl_on_new_line ();
	rl_redisplay();
}
