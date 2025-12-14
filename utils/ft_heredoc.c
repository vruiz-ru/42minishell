/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:41:27 by vruiz-ru          #+#    #+#             */
/*   Updated: 2025/12/14 12:55:00 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	heredoc_sigint(int sig)
{
	(void)sig;
	g_signal_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

static void	write_to_tmp(int fd, char *line)
{
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
	free(line);
}

static void	warning_err(char *delimiter)
{
	char	*s;

	s = "minishell: warning: here-document delimited by end-of-file (wanted '";
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

static int	proc_loop(t_process *proc, int fd, char *delimiter, int expand)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_signal_status == 130)
				return (1);
			warning_err(delimiter);
			break ;
		}
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
		{
			free(line);
			break ;
		}
		if (expand)
			line = ft_expand_heredoc_line(proc, line);
		write_to_tmp(fd, line);
	}
	return (0);
}

int	ft_heredoc(char *delimiter, int expand, t_process *proc)
{
	int	fd;
	int	stdin_backup;
	int	status;

	stdin_backup = dup(STDIN_FILENO);
	if (stdin_backup < 0)
		return (-1);
	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (close(stdin_backup), perror("heredoc open"), -1);
	signal(SIGINT, heredoc_sigint);
	status = proc_loop(proc, fd, delimiter, expand);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	close(fd);
	if (status == 1)
	{
		unlink(".heredoc_tmp");
		return (-1);
	}
	fd = open(".heredoc_tmp", O_RDONLY);
	unlink(".heredoc_tmp");
	return (fd);
}
