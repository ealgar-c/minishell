/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_extend_and_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:11:25 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/09 11:32:58 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_quote_handling(char *str, char *prev, int i, t_info *info)
{
	char	*content;
	int		len;
	char	q;

	len = 1;
	q = str[i];
	while (str[i + len] && str[i + len] != q)
		len++;
	if (!str[i + len])
	{
		ft_error_handling(42, "Wrong quotes, please fix", info);
		return (free(prev), NULL);
	}
	if (len - i > 0) // si hay algo entre las comillas
		content = check_extensor(ft_substr(str, i + 1, len - 1), info, q);
	else // dice enrique que hay que alojar el nulo
		content = ft_strdup(NULL);
	if (prev)
	{
//		ft_printf("Q_h PREV was: %s, content was: %s\n", content);
		content = ft_strjoin(prev, content);
		free(prev);
	}
//	ft_printf("after quote_h: %s\n", content);
	return (content);
}

char	*ft_content_handling(char *str, char *prev, int i, t_info *info)
{
	char	*content;
	int		len;

	len = 0;
	while (str[i + len] && str[i + len] != 34 && str[i + len] != 39)
		len++;
	content = check_extensor(ft_substr(str, i, len), info, str[i]);
	if (prev)
	{
//		ft_printf("cont_h PREV was: %s, content was: %s\n", content);
		content = ft_strjoin(prev, content);
		free(prev);
	}
//	ft_printf("cont_h after joinin: %s\n", content);
	return (content);
}

char	*ft_join_content(char *str, t_info *info)
{
	char	*cmd;
	char	*prev;
	int		i;

	i = 0;
	cmd = NULL;
	while (str[i] && !info->error)
	{
		prev = cmd;
//		ft_printf("FT_JOIN_CONTENT: prev is: %s\n", prev);
		if (str[i] == 34 || str[i] == 39)
		{
			cmd = ft_quote_handling(str, prev, i, info);
			i += 2;
		}
		else
			cmd = ft_content_handling(str, prev, i, info);
		i += ft_strlen(cmd);
	}
//	ft_printf("content after join content is: %s\n", cmd);
	return (free(str), cmd);
}

void	ft_extend_and_quotes(char **cmd, t_info *info)
{
	int		j;

	j = 0;
	while (cmd[j] && !info->error)
	{
		cmd[j] = ft_join_content(cmd[j], info);
//		ft_printf("cmd[j] is: %s\n", cmd[j]);
		j++;
	}
}