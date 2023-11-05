/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:40:28 by erivero-          #+#    #+#             */
/*   Updated: 2023/11/05 22:01:52 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lexer	*get_token(char *str, int i, t_ast_utils *utils)
{
	t_lexer	*node;

	if (str[i] == '|')
		node = new_lexer_node("|", PIPE, utils);
	else if (str[i] == '>' && str[i + 1] != '>')
		node = new_lexer_node(">", GREAT, utils);
	else if (str[i] == '>' && str[i + 1] == '>')
		node = new_lexer_node(">>", GREAT_GREAT, utils);
	else if (str[i] == '<' && str[i + 1] != '<')
		node = new_lexer_node("<", LESS, utils);
	else
		node = new_lexer_node("<<", LESS_LESS, utils);
	return (node);
}

bool	cmd_conditions(t_lexer *tmp, bool getcmd)
{
	if (!tmp)
		return (true);
	if (tmp->token != ARG)
	{
		if (tmp->token == PIPE)
			return (true);
		else if (getcmd == true && tmp->token != REDIR_FILE)
			return (true);
	}
	return (false);
}

t_lexer	*ft_create_list(char *str, int *i, t_info *in, t_lexer *tmp_node)
{
	bool	getcmd;

	getcmd = false;
	if (ft_token_check(str[*i]))
		tmp_node = get_token(str, *i, in->utils);
	else if (cmd_conditions(tmp_node, getcmd))
	{
		tmp_node = new_lexer_node(get_content(str, *i, 0, in), CMD, in->utils);
		getcmd = false;
	}
	else if (!ft_check_last_node(in->utils))
		tmp_node = new_lexer_node(get_content(str, *i, 1, in), ARG, in->utils);
	else
	{
		tmp_node = new_lexer_node(get_content(str, *i, 7, in), 7, in->utils);
		getcmd = true;
	}
	if (tmp_node == NULL)
		return (NULL);
	*i += ft_strlen(tmp_node->content);
	return (tmp_node);
}

bool	ft_lexer_list(char *str, t_info *info, t_lexer *tmp_node)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] > 0 && str[i] < 33)
			i++;
		tmp_node = ft_create_list(str, &i, info, tmp_node);
		if (!tmp_node)
			return (false);
		if (!str[i])
			return (true);
	}
	return (true);
}

void	ft_lexer(char *str, t_info *info)
{
	int			i;
	t_lexer		*tmp_node;
	bool		ret;
	char		*line;

	i = 0;
	tmp_node = NULL;
	ret = true;
	line = ft_strtrim(str, " ");
	g_signals.error = false;
	if (!line[i])
		ft_error_handling(0, NULL, info);
	if (line[i] == '|' || line[ft_strlen(line) - 1] == '|')
		ft_error_handling(1, "|", info);
	else if (!g_signals.error)
		ret = ft_lexer_list(line, info, tmp_node);
	else if (!ret)
		ft_error_handling(0, NULL, info);
	tmp_node = info->utils->lexer_root;
	if (!g_signals.error && tmp_node->token > 2
		&& tmp_node->token < 7 && !tmp_node->next)
		ft_error_handling(1, "newline", info);
	free(line);
}
