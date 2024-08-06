/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:17:32 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/06 18:17:40 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_parser(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser)
	{
		printf("\n");
		printf("command : ");
		while (parser->cmd[i])
			printf("%s ", parser->cmd[i++]);
		if (parser->redirections)
			printf("\nredirection : (%d) %s\n", parser->redirections->token,
				parser->redirections->next->content);
		else
			printf("\nredirection : NULL\n");
		parser = parser->next;
		i = 0;
	}
}
