/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:05:00 by vruiz-ru          #+#    #+#             */
/*   Updated: 2025/12/14 12:53:20 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_OUTPUT_H
# define INPUT_OUTPUT_H

# include "../headers/macros.h"
# include "../headers/structs.h"
# include "../import/libft/libft.h"
# include "../builtins/builtins.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>

// INPUT_OUTPUT MAIN FUNCTIONS
void	ft_readinput(t_process *process);
char	*ft_prompt(t_process *process);
int		ft_inputvar(t_process *process, char **line);
int		ft_parse_line(t_process *process);
int		ft_tokenize_line(t_process *process, char *line);
int		ft_is_fd_redirect(char *line);
int		ft_is_fd_redir_start(char *line, int pos);
int		ft_is_sep_char_at_pos(char *line, int pos);

// INPUT_OUTPUT/UTILS - INPUTVAR HELPERS
void	ft_trimmer(char **line, char *name, int raw_val_len);
int		ft_add_var(t_process *proc, char *n, char *v);
int		ft_get_raw_value_len(char *line);
int		ft_process_assignment(t_process *p, char **line, char *name, char *val);
int		ft_get_data(char *line, char **name, char **val, int *raw_len);

// INPUT_OUTPUT/UTILS - VARIABLE EXPANSION
int		ft_return_value(t_process *process, char *line);
int		ft_add_split_tokens(t_list **tokens, char *value);
int		ft_contains_variable(char *token);
int		ft_specialvars(t_process *proc, char **var_name, char ch);
int		ft_is_var_start(char c);
int		ft_check_ansi_quote(char *line, int idx, char delim);

// INPUT_OUTPUT/UTILS - PARSING
char	*ft_parse_token(t_process *process, char *content, char token);
char	*ft_parse_delimiter(char *str, int *quoted);
int		ft_check_syntax(t_process *proc);

// INPUT_OUTPUT/UTILS - TOKEN UTILS
int		is_operator_token(char *str);
int		was_fully_quoted(char *str);
int		is_quoted_token(char *s);
int		check_quotes(char c, char *quote);
char	*mark_if_quoted_op(char *res, int was_quoted);
char	*remove_quote_marker(char *str);

// INPUT_OUTPUT/UTILS - EXECUTION
void	ft_fork_process(t_process *process);
char	*ft_get_cmd_path(char *cmd, char **envp);
void	ft_cmd_not_found(char *cmd);
void	ft_exec_error(char *path, char *cmd, int err);
void	ft_config_pipes(t_cmd *cmd, int *pipefd, int prev_fd);
int		ft_apply_redirs(t_cmd *cmd);
void	ft_close_fds(t_cmd *cmd, int prev_fd);

// INPUT_OUTPUT/UTILS - COMMANDS
t_cmd	*ft_new_cmd(void);
int		ft_is_redir(char *str);
int		ft_tokens_to_cmds(t_process *proc);
int		ft_exec_redirs(t_cmd *cmd, int *status);
void	ft_pipe_utils(t_process *process);

// INPUT_OUTPUT/UTILS - COMMAND HELPERS
void	ft_handle_redir_token(t_cmd *node, t_list **tokens, t_process *proc);
void	ft_handle_arg_token(t_cmd *node, t_list **tokens, int *i);
t_cmd	*ft_create_new_command(t_list *curr);
int		ft_count_args(t_list *tokens);
void	ft_parse_redir(t_cmd *node, char *redir, char *file, t_process *proc);
void	ft_handle_fd_redir(t_cmd *node, char *redir);
void	ft_handle_heredoc_redir(t_cmd *node, char *file, t_process *proc);
void	ft_handle_fd_redir_check(t_cmd *node, char *redir);

#endif
