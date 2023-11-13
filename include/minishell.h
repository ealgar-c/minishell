/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:01:29 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/13 16:46:01 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include "minishell_structs.h"

t_signals	g_signals;

/************************FUNCIONES***************************/

/*							LEXER							*/
// lexer.c
void			ft_lexer(char *str, t_info *info);
t_lexer			*ft_create_list(char *str, int *i, t_info *in,
					t_lexer *tmp_node);

// lexer_utils.c
bool			ft_token_check(char c);
char			*ft_add_space(char *str, int s, char *content, char q);
char			*get_content(char *str, int i, t_info *info);

// lexer_list_utils.c
t_ast_utils		*ft_utils_init(t_info *info);
t_lexer			*new_lexer_node(char *content, int token, t_ast_utils *utils);
void			ft_lxadd_back(t_lexer **root, t_lexer *new);
bool			ft_check_last_node(t_ast_utils *utils);
bool			ft_lexer_list(char *str, t_info *info, t_lexer *tmp_node);

/*							PARSER							*/
// parser.c
void			ft_parser(t_info *info);

// parser_arguments_utils.c
t_parser_args	*par_newargnode(t_lexer *tmp);
void			get_arguments(t_lexer *lex, t_parser *par);
void			get_final_cmd(t_parser *node, t_info *info);

// parser_utils.c
void			fill_new_par_node(t_parser *new, t_parser *prev,
					t_lexer *tmp_lex);

// redirections.c
void			ft_redirector(t_parser *parser_node, t_info *info);
void			ft_redirector_back(t_info *info);
int				ft_heredoc(t_parser *parser, t_info	*info);

/*							BUILTINS						*/
// builtin_exit.c
void			ft_exit(char **cmd, t_info *info);

//builtin_unset.c
void			ft_unset(t_parser *parser_node, t_info *info);

//builtin_env.c
void			ft_env(t_parser *parser_node, t_info *info);

// builtin_cd.c
void			ft_cd(t_parser *parser_node, t_info *info);

// builtin_cd_utils.c

void			ft_check_cd_error(char *path);
void			ft_change_pwd_env(t_info *info);
void			ft_change_oldpwd_env(t_info *info);

// builtin_pwd.c
void			ft_pwd(t_info *info);

// builtin_echo.c
void			ft_echo(t_parser *parser_node, t_info *info);

// builtin_export.c
void			ft_export(t_parser *parser_node, t_info *info);
void			save_variable(char *variable, t_info *info);
bool			input_checker(char *arg, char *cmd);

// builtin_export_utils.c
void			ft_non_arg_export(t_info *info);
bool			check_export_arg(char *str);

// builtin_unset.c
void			ft_unset(t_parser *parser_node, t_info *info);

/*							EXECUTER						*/
// executer.c
void			ft_executer(t_info *info);
void			ft_builtin(t_parser *parser_node, char **cmd, t_info *info);
char			**env_to_array(t_info *info);
char			*get_useful_path(char *cmd, t_env *env_root);

// executer_utils.c
void			ft_non_builtin(t_info *info, t_parser *parser, char *path);
bool			ft_check_paths(t_env *env_root);

/*							UTILS						*/
// signals.c
void			ctrlc_handler(int sign);

// extensor.c
char			*get_env(char *env, t_info *info);
char			*check_extensor(char *content, t_info *info, char quoted);

// enviroment.c
t_env			*save_envp(char **envp);
t_env			*ft_new_env_node(char *name, char *value);
void			env_add_back(t_env **root, t_env *new);
char			*ft_get_env_name(char *fullenv);
char			*ft_get_env_value(char *fullenv);

// extend_and_quote.c
void			ft_extend_and_quotes(char **cmd, t_info *info);

// pipes_config.c
void			config_pipes(t_parser *parser, int mode, t_info *info);
int				ft_redirector_builtinpipes(t_parser *parser_node, t_info *info);

//errors.c
void			ft_error_handling(int error, char *str, t_info	*info);

// free_utils.c
void			ft_free_utils(t_info *info, bool mode);
void			ft_free_env(t_env *root);
void			ft_free(char **str);

#endif