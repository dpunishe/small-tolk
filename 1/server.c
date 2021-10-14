/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csherill <csherill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 22:38:49 by csherill          #+#    #+#             */
/*   Updated: 2021/10/12 17:42:33 by csherill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static size_t	ft_strlen(char *str1)
{
	size_t	i;

	if (!str1)
		return (0);
	i = 0;
	if (str1)
		while (str1[i] != 0)
			i++;
	return (i);
}

static void	print_pid(char *str)
{
	int		pid;
	int		len;
	char	buffer_for_pid[6];

	len = 0;
	write (1, "Id:", 4);
	pid = getpid();
	buffer_for_pid[len++] = '\n';
	while (1)
	{
		if (pid < 10)
		{
			buffer_for_pid[len++] = *(str + pid);
			break ;
		}
		else
			buffer_for_pid[len++] = *(str + (pid % 10));
		pid /= 10;
	}
	while (len + 1 != 0)
		write(1, (buffer_for_pid + len--), 1);
}

static void	error(char *message)
{
	write(2, "\33[38;2;255;51;51;1m", 19);
	write(2, message, ft_strlen(message));
	write(2, "\033[m\n", 5);
	exit(1);
}

static void	function(int signal)
{
	static char	symb = 0;
	static int	i = 0;
	static int	count = 7;
	static char	syb_buf[200];

	if (signal == SIGUSR1)
		symb = symb | (1 << count);
	else if (signal == SIGINT)
		error("\nStop Process!");
	count = count - 1;
	if (count == -1)
	{
		syb_buf[i] = symb;
		i = i + 1;
		if (symb == '\0' || i == 50)
		{
			syb_buf[i] = 0;
			write(1, syb_buf, i - 1);
			i = 0;
		}
		count = 7;
		symb = 0;
	}
}

int	main(void)
{
	print_pid("0123456789");
	signal(SIGUSR1, function);
	signal(SIGUSR2, function);
	signal(SIGINT, function);
	while (1)
	{
	}
	return (0);
}
