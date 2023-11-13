/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:18:51 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/13 16:30:47 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_check_cd_error(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_printf("\033[0;33mcd: %s: No such file or directory\n\033[0m", path);
	else
		ft_printf("\033[0;33mcd: %s: Not a directory\n\033[0m", path);
	close(fd);
}

void	ft_change_pwd_env(t_info *info)
{
	char	*to_send;
	char	*path;

	path = malloc(sizeof(char) * 100);
	path = getcwd(path, 100);
	to_send = ft_strjoin("PWD=", path);
	save_variable(to_send, info);
	free(to_send);
	free(path);
}

void	ft_change_oldpwd_env(t_info *info)
{
	char	*to_send;
	char	*path;

	path = malloc(sizeof(char) * 100);
	path = getcwd(path, 100);
	to_send = ft_strjoin("OLDPWD=", path);
	save_variable(to_send, info);
	free(to_send);
	free(path);
}
