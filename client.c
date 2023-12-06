#include "minitalk.h"

int	ft_atoi(const char *nptr)
{
	int	number;
	int	sign;
	int	count;

	number = 0;
	sign = 1;
	count = 0;
	while ((nptr[count] >= 9 && nptr[count] <= 13) || (nptr[count] == 32))
		count++;
	if (nptr[count] == '-')
		sign = -1;
	if (nptr[count] == '-' || nptr[count] == '+')
		count++;
	while (nptr[count] >= '0' && nptr[count] <= '9')
		number = number * 10 + (nptr[count++] - '0');
	return (number * sign);
}

int	*atob(char c)
{
	int	*bin;
	int	count;

	bin = (int *) malloc (sizeof(int) * 8);
	count = 7;
	while (count >= 0)
	{
		bin[count] = c % 2;
		c /= 2;
		count--;
	}
	return (bin);
}

void	signal_handler_client(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("Receiving acknowledge of SIGUSR1\n");
	else if (sig == SIGUSR2)
		ft_printf("Receiving acknowledge of SIGUSR2\n");
	return ;
}

void	send_signal(pid_t server_pid, int bin[8])
{
	int	count;

	count = 0;
	while (count < 8)
	{
		if (bin[count] == 0)
			kill(server_pid, SIGUSR1);
		else if (bin[count] == 1)
			kill(server_pid, SIGUSR2);
		count++;
		usleep(SLEEP_TIME);
	}
}

int	main(int argc, char *argv[])
{
	pid_t	server_pid;
	char	*str;
	int		*bin;
	int		count;

	signal(SIGUSR1, signal_handler_client);
	signal(SIGUSR2, signal_handler_client);
	if (argc != 3)
		return ((ft_printf("expected 2 arguments, got %i\n", argc - 1) * -1));
	server_pid = (pid_t) ft_atoi(argv[1]);
	str = argv[2];
	count = 0;
	while (str[count])
	{
		bin = atob(str[count++]);
		if (!bin)
			return (-1);
		send_signal(server_pid, bin);
		free (bin);
	}
}
