/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:40:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/29 11:24:55 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(char **cmd)
{
	char	*path;

	if (cmd[1])
		ft_printf("Flags no suported in this case\n");
	path = malloc(sizeof(char) * 100);
	path = getcwd(path, 100);
	ft_printf("%s\n", path);
	free(path);
	return ;
}

void	ft_exit(char **cmd)
{
	if (cmd[1])
		ft_printf("Flags no suported in this case\n");
//	ft_free(whatever);
	ft_printf("exit\n");
	exit (0);
}

void	ft_cd(char **cmd)
{
	int		i;
	char	*path;

	i = 1;
	if (!cmd[1])
		path = getenv("HOME");
	else
	{
		path = cmd[i];
		while (cmd[++i])
			path = ft_strjoin(ft_strjoin(path, " "), cmd[i]);
	}
	if (chdir((const char *)(path)) == -1)
		ft_printf("cd: %s: No such file or directory\n", path);
	return ;
}

/*
 sobreentendiendo que el executer ha spliteado la string de argumentos
y que ya le está mandando a mi función el string con la ruta a cambiar
aprovechando que chdir guarda el código de error en la variable global errno
utilizo perror para que, además de printear mi mensaje de error, printee
el error concreto que haya sucedido (directorio inexistente o whatever) 

void	ft_export(char **cmd)
{
	(void)cmd;
	//hola no esta hecho aun
	return ;
}

void	ft_unset(char **cmd)
{
	(void)cmd;
	//hola no esta hecho aun
	return ;
}

void	ft_env(char **cmd)
{
	(void)cmd;
	//hola no esta hecho aun
	return ;
}
 */