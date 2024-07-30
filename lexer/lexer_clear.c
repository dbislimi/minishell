/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:25:45 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/30 18:26:39 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_lexer(t_lexer **lexer)
{
	t_lexer	*temp;

	while (*lexer)
	{
		temp = (*lexer)->next;
		free((*lexer)->content);
		free(*lexer);
		*lexer = temp;
	}
	*lexer = NULL;
}

void	print_lexer(t_lexer *lexer)
{
	while (lexer)
	{
		printf("content: [%s]\ntoken: [%d]\n", lexer->content, lexer->token);
		lexer = lexer->next;
	}
}
