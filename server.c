#include "minitalk.h"

char	btoa(int bin[8])
{
	char	result;
	int		count;

	result = 0;
	count = 0;
	while (count < 8)
	{
		result = result * 2 + bin[count];
		count++;
	}
	return (result);
}

void	signal_handler_server(int sig, siginfo_t *info, void *context)
{
	static int	bin[8] = {0};
	static int	count = 0;
	char		c;

	(void) context;
	if (sig == SIGUSR1)
		bin[count++] = 0;
	else if (sig == SIGUSR2)
		bin[count++] = 1;
	if (count == 8)
	{
		count = 0;
		c = btoa(bin);
		write(1, &c, 1);
	}
	if (sig == SIGUSR1)
		kill(info->si_pid, SIGUSR1);
	else if (sig == SIGUSR2)
		kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("%i\n", getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = (void *) signal_handler_server;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		continue ;
	}
}
