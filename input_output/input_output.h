/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:05:00 by aghergut          #+#    #+#             */
/*   Updated: 2025/12/12 22:13:55 by aghergut         ###   ########.fr       */
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

// INPUT_OUTPUT MAIN FUNCTIONS
void	ft_readinput(t_process *process);
char	*ft_prompt(t_process *process);
int		ft_inputvar(t_process *process, char **line);
int		ft_parse_line(t_process *process);
int		ft_tokenize_line(t_process *process, char *line);

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
int		is_var_start(char c);
int		check_ansi_quote(char *line, int idx, char delim);

// INPUT_OUTPUT/UTILS - PARSING
char	*ft_parse_token(t_process *process, char *content, char token);
char	*ft_parse_delimiter(char *str, int *quoted);
int		ft_check_syntax(t_process *proc);

// INPUT_OUTPUT/UTILS - EXECUTION
void	ft_fork_process(t_process *process);
char	*ft_get_cmd_path(char *cmd, char **envp);
void	cmd_not_found(char *cmd);
void	ft_exec_error(char *path, char *cmd, int err);
void	config_pipes(t_cmd *cmd, int *pipefd, int prev_fd);
int		ft_apply_redirs(t_cmd *cmd);
void	close_fds(t_cmd *cmd, int prev_fd);

// INPUT_OUTPUT/UTILS - COMMANDS
t_cmd	*ft_new_cmd(void);
int		is_redir(char *str);
int		ft_tokens_to_cmds(t_process *proc);
int		ft_exec_redirs(t_cmd *cmd, int *status);
void	ft_pipe_utils(t_process *process);

#endif
