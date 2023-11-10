/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_and_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:11:25 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/10 15:20:35 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_quote_handling(char *str, int *i, t_info *info)
{
	char	*content;
	int		len;
	char	q;

	len = 1;
	q = str[*i];
	if (str[*i + len] == q)
	{
		*i += 2;
		return (NULL);
	}
	while (str[*i + len] && str[*i + len] != q)
		len++;
	if (str[*i + len] != q)
	{
		ft_error_handling(42, "Wrong quotes, please fix", info);
		return (NULL);
	}
	content = check_extensor(ft_substr(str, *i + 1, len - 1), info, str[*i]);
	*i += len + 1;
	return (content);
}

char	*ft_content_handling(char *str, int *i, t_info *info)
{
	char	*content;
	int		len;

	len = 0;
	while (str[*i + len] && str[*i + len] != 34 && str[*i + len] != 39)
		len++;
	content = check_extensor(ft_substr(str, *i, len), info, str[*i]);
	*i += len;
	return (content);
}

char	*update_prev(char *prev, char *content)
{
	char	*temp;

	temp = prev;
	if (!content)
		return (prev);
	if (prev)
	{
		prev = ft_strjoin(prev, content);
		free(temp);
	}
	else
		prev = ft_strdup(content);
	free(content);
	return (prev);
}

char	*ft_join_content(char *str, t_info *info)
{
	char	*cmd;
	char	*prev;
	char	*content;
	int		i;

	i = 0;
	cmd = 0;
	while (str[i] && !info->error)
	{
		prev = cmd;
		content = NULL;
		if (str[i] == 34 || str[i] == 39)
		{
			content = ft_quote_handling(str, &i, info);
			if (info->error)
				return (free(cmd), str);
		}
		else
			content = ft_content_handling(str, &i, info);
		cmd = update_prev(prev, content);
	}
	return (free(str), cmd);
}

void	ft_extend_and_quotes(char **cmd, t_info *info)
{
	int		j;

	j = 0;
	while (cmd[j] && !info->error)
	{
		cmd[j] = ft_join_content(cmd[j], info);
		if (info->error)
			return ;
		j++;
	}
}
