/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:40:28 by erivero-          #+#    #+#             */
/*   Updated: 2023/11/10 13:45:42 by ealgar-c         ###   ########.fr       */
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
	if (!getcmd)
		return (false);
	if (tmp->token != ARG)
	{
		if (tmp->token == REDIR_FILE || tmp->token == PIPE)
			return (true);
	}
	return (false);
}

bool	ft_checkend(char *str, int i, bool getcmd)
{
	while (str[i])
	{
		if (str[i] != ' ')
			return (getcmd);
		i++;
	}
	return (true);
}

t_lexer	*ft_create_list(char *str, int *i, t_info *in, t_lexer *tmp_node)
{
	static bool	getcmd = true;

	if (str[*i] == '|')
		getcmd = true;
	if (ft_token_check(str[*i]))
		tmp_node = get_token(str, *i, in->utils);
	else if (cmd_conditions(tmp_node, getcmd))
	{
		tmp_node = new_lexer_node(get_content(str, *i, in), CMD, in->utils);
		getcmd = false;
	}
	else if (!ft_check_last_node(in->utils))
		tmp_node = new_lexer_node(get_content(str, *i, in), ARG, in->utils);
	else
		tmp_node = new_lexer_node(get_content(str, *i, in), 7, in->utils);
	if (tmp_node == NULL)
		return (NULL);
	*i += ft_strlen(tmp_node->content);
	getcmd = ft_checkend(str, *i, getcmd);
	return (tmp_node);
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
	info->error = false;
	if (!line[i])
		ft_error_handling(0, NULL, info);
	if (line[i] == '|' || line[ft_strlen(line) - 1] == '|')
		ft_error_handling(1, "|", info);
	else if (!info->error)
		ret = ft_lexer_list(line, info, tmp_node);
	else if (!ret)
		ft_error_handling(0, NULL, info);
	tmp_node = info->utils->lexer_root;
	if (!info->error && tmp_node->token > 2
		&& tmp_node->token < 7 && !tmp_node->next)
		ft_error_handling(1, "newline", info);
	free(line);
}
