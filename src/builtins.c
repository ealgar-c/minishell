/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:40:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/27 13:27:37 by erivero-         ###   ########.fr       */
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
}

void	ft_exit(char **cmd)
{
	if (cmd[1])
		ft_printf("Flags no suported in this case\n");
//	ft_free(whatever);
	ft_printf("exit\n");
	exit (0);
}

void	ft_echo(char **cmd)
{
	int		i;

	i = 1;
	while (cmd[i])
	{
		if (i < ft_array_len(cmd) && i > 1)
			ft_printf(" ");
		ft_printf("%s", cmd[i]);
		i++;
	}
	ft_printf("\n");
}

/* sobreentendiendo que el executer ha spliteado la string de argumentos
y que ya le está mandando a mi función el string con la ruta a cambiar
aprovechando que chdir guarda el código de error en la variable global errno
utilizo perror para que, además de printear mi mensaje de error, printee
el error concreto que haya sucedido (directorio inexistente o whatever) */
void	ft_cd(char *rute)
{
	if (chdir((const char)(rute)) == -1)
	{
		perrror("Error while changing directory");
		exit(EXIT_FAILURE);
	}
	return ;
}

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
