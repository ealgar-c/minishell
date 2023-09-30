/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:40:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/30 18:17:29 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_leakss(void)
{
	system("leaks -q minishell");
}

void	ft_exit(char **cmd)
{
	if (cmd[1])
		ft_printf("Flags no suported in this case\n");
//	ft_free(whatever);
	atexit(ft_leakss);
	ft_printf("exit\n");
	exit (0);
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