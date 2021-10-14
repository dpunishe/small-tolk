/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpunishe <dpunishe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 22:38:40 by csherill          #+#    #+#             */
/*   Updated: 2021/10/12 21:13:15 by dpunishe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static int	ft_atoi(char *str)
{
	int	value;
	int	i;
	int	j;

	if (!str)
		return (-1);
	i = 0;
	j = 0;
	value = 0;
	while (str[i] == '\f' || str[i] == '\n' || str[i] == '\r' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == ' ')
		i++;
	while (*(str + i) >= '0' && *(str + i) <= '9')
		value = (value * 10) + (*(str + i++) - '0');
	if (i > j)
		return (value);
	return (-1);
}

void	error(char *message, int flag)
{	
	int	i;

	i = 0;
	while (message[i] != 0)
		i++;
	if (flag == 1)
		write(2, "\33[38;2;255;51;51;1m", 19);
	if (flag == 2)
		write(2, "\33[38;2;0;145;15;1m", 19);
	write(2, message, i);
	write(2, "\033[m\n", 5);
	exit(1);
}

int	pid_validater(char *str)
{
	int	pid;

	pid = ft_atoi(str);
	if (pid == -1 || pid < 0 || pid >= 99999)
		error("clinet: not valid pid", 1);
	if (pid == 0)
		error("clinet: forbidden pid", 1);
	return (pid);
}

void	donwload_and_message(int len, int count, int pid, char **argv)
{
	int		i;
	int		bit_8;

	i = 10;
	bit_8 = 0;
	while (count != len + 1)
	{
		bit_8 = 128;
		while (bit_8 != 0)
		{
			usleep(350);
			if (bit_8 & argv[2][count])
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bit_8 = bit_8 >> 1;
		}
		count++;
		if ((int)len / count == i)
		{
			write(1, "\33[38;2;0;145;15;1m|\033[m", 23);
			i--;
		}
	}
}

int	main(int argc, char *argv[])
{
	size_t	len;
	int		pid;

	if (argc < 2 || argc > 3)
		error("Please write again", 1);
	pid = pid_validater(argv[1]);
	if (argc == 2)
		error("Please write again", 1);
	len = 0;
	while (argv[2][len] != 0)
		len++;
	write(1, "{", 2);
	donwload_and_message(len, 0, pid, argv);
	write(1, "}\n", 2);
	error("message has been sent\n", 2);
}
