/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:17:32 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/15 15:22:17 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_redirections(t_lexer *redirections)
{
	printf("\nredirections : ");
	while (redirections)
	{
		printf("(%d) %s", redirections->token,
			redirections->content);
		if (redirections->next)
			printf(" & ");
		redirections = redirections->next;
	}
	printf("\n");
}

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
		print_redirections(parser->redirections);
		parser = parser->next;
	}
}
