/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_and_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:11:25 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/05 21:39:40 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*clean_quotes(char *str)
{
	char	*clean;

	clean = ft_substr(str, 1, ft_strlen(str) - 2);
	return (free(str), clean);
}

int	check_quotes(char *cmd)
{
	if (cmd[0] == 34)
		return (DOUBLE);
	else if (cmd[0] == 39)
		return (SINGLE);
	return (NONE);
}

void	ft_extend_and_quotes(char **cmd, t_info *info)
{
	int			i;
	int			quoted;

	i = 0;
	while (cmd[i])
	{
		quoted = check_quotes(cmd[i]);
		if (quoted != NONE)
			cmd[i] = clean_quotes(cmd[i]);
		cmd[i] = check_extensor(cmd[i], info, quoted);
		
		i++;
	}
}
