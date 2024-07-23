/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:22:17 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/23 18:22:52 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	envclear(t_env **lst)
{
	t_env	*temp;

	while (*lst != NULL)
	{
		temp = (*lst)->next;
		free((*lst)->variable);
		free((*lst)->value);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
