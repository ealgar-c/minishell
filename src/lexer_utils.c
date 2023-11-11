/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:09:04 by erivero-          #+#    #+#             */
/*   Updated: 2023/11/11 15:26:46 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	ft_token_check(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

int	loop_check(char c, bool *quote)
{
	static char	q;

	if (!*quote)
	{
		if (c == 0 || c == 32 || ft_token_check(c))
			return (0);
		if (c == 34 || c == 39)
		{
			q = c;
			*quote = true;
		}
	}
	else
	{
		if (c == q)
			*quote = false;
		if (c == 0)
			return (0);
	}
	return (1);
}

char	*get_content(char *str, int i, t_info *info)
{
	int		len;
	bool	quote;

	len = 0;
	quote = false;
	(void)info;
	while (loop_check(str[i + len], &quote))
		len++;
	return (ft_substr(str, i, len));
}
