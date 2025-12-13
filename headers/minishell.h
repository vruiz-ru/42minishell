/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:49:41 by aghergut          #+#    #+#             */
/*   Updated: 2025/12/13 14:45:05 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../builtins/builtins.h"
# include "../input_output/input_output.h"
# include "../import/libft/libft.h"
# include "macros.h"
# include "structs.h"
# include <errno.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

// VARIABLE GLOBAL
extern int	g_signal_status;
// MAIN FUNCTIONS
void		ft_shell_loop(t_process *process);
void		ft_reset_utils(t_process **process);
// UTILS
int			ft_init_parent(t_process **parent, char *name, char *envp[]);
char		*ft_construct(t_list *tokens, char *str);
void		ft_free_process(t_process *proc);
void		ft_clear_strtok(void);
void		ft_safeadd_tokens(t_list **tokens, char **token);
void		ft_addspace(t_list **tokens);
void		ft_free_array(char **arr);
void		ft_free_cmds(t_cmd *cmds);
int			ft_heredoc(char *delimiter, int expand, t_process *proc);
void		ft_add_io(t_cmd *cmd, t_io_type type, char *path, int fd);
char		*ft_expand_heredoc_line(t_process *proc, char *str);
int			ft_tokens_to_cmds(t_process *proc);
// HANDLERS
void		ft_sigint(int sig);

#endif