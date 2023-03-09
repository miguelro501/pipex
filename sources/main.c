/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:24:22 by miguelro          #+#    #+#             */
/*   Updated: 2023/03/09 17:48:44 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int error(char *str)
{
	error(str);
	exir(1);
}

char *path_finder(char **path_arr, char **envp)
{
	//to do
}

void	child(char **av, int *pipe_fd, char **envp, int fd)
{
	char **path;
	
	dup2(fd, 0);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	path = ft_split(av[2], ' ');
	execve(path_finder(path, envp), av[2], envp);
}

void	parent(char **av, int *pipe_fd, char **envp, int fd)
{
	char **path;

	dup2(fd, 1);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	path = ft_split(av[3], ' ');
	execve(path_finder(path, envp), av[3], envp);
}

int main(int ac, char **av, char **envp)
{
 	int f1;
    int f2;
	int pipe_fd[2];
	pid_t pid;
	
	if(ac != 5)
		error("Invalid number of parameters\n");
	f1 = open(av[1], O_RDONLY);
    f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644); 
	if (f1 < 0 || f2 < 0)
        error("Error while opening infile or outfile\n");
	if(pipe(pipe_fd) == -1)
		error("Error creating the pipe");
	pid = fork();
	if(pid == -1)
		error("Error while creating a fork");
	if(pid == 0)
		child(av,pipe_fd, envp, f1);
	parent(av,pipe_fd, envp, f2);
    return (0);
}