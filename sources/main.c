/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:24:22 by miguelro          #+#    #+#             */
/*   Updated: 2023/03/16 14:56:10 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error(char *str)
{
	perror(str);
	exit(1);
}

char	*path_finder(char **cmds, char **envp)
{
	int		i;
	char	*cmd;
	char	*path;
	char	*dir;
	char	*bin;

	cmd = cmds[0];
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (cmd);
	path = envp[i] + 5;
	while (path && str_ichr(path, ':') > -1)
	{
		dir = ft_substr(path, 0, str_ichr(path, ':'));
		bin = ft_strjoin(ft_strjoin(dir, "/"), cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += str_ichr(path, ':') + 1;
	}
	return (cmd);
}

void	child(char **av, int *pipe_fd, char **envp, int fd)
{
	char	**cmds;

	dup2(fd, 0);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	cmds = ft_split(av[2], ' ');
	execve(path_finder(cmds, envp), cmds, NULL);
}

void	parent(char **av, int *pipe_fd, char **envp, int fd)
{
	char	**cmds;

	dup2(fd, 1);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	cmds = ft_split(av[3], ' ');
	execve(path_finder(cmds, envp), cmds, NULL);
}

int	main(int ac, char **av, char **envp)
{
	int		f1;
	int		f2;
	int		pipe_fd[2];
	pid_t	pid;

	if (ac != 5)
		error("Invalid number of parameters\n");
	f1 = open(av[1], O_CREAT | O_RDWR);
	f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
		perror("Error while opening infile or outfile\n");
	if (pipe(pipe_fd) == -1)
		error("Error creating the pipe");
	pid = fork();
	if (pid == -1)
		error("Error while creating a fork");
	if (pid == 0)
		child(av, pipe_fd, envp, f1);
	parent(av, pipe_fd, envp, f2);
	return (0);
}
