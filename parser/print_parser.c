/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:17:32 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/14 14:08:38 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_parser(t_parser *parser)
{
	int	i;

	while (parser)
	{
		i = 0;
		printf("\n");
		printf("command : ");
		if (parser->cmd)
		{
			while (parser->cmd[i])
				printf("[%s] ", parser->cmd[i++]);
		}
		else
			printf("NULL");
		printf("\nredirection : ");
		while (parser->redirections)
		{
			printf("(%d) %s|", parser->redirections->token,
				parser->redirections->content);
			parser->redirections = parser->redirections->next;
		}
		printf("\n");
		parser = parser->next;
	}
}
