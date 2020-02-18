#include <stdlib.h>
#include "open.h"
#include "lidar.h"
#include <bcm2835.h>

#define NBR_VAL 682

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stropts.h>
#include <time.h>
#include <string.h>
#include <termios.h>

#include <bcm2835.h>
#include <errno.h>



void	lidar_get_resp_print(struct pollfd fds[1], int fd)
{
	int	ret;
	int	res;
	char	buffer[LIDAR_BUFF];
	int	end;

	end = 1;
	while(end)
	{
		ret = poll(fds, 1, 1000);
		if (ret > 0)
		{
			if (fds[0].revents & POLLRDNORM)
			{
				write(1, "resp\n\n", 5);
				res = read(fd, buffer, LIDAR_BUFF);
				buffer[res] = 0;
				write(1, buffer, strlen(buffer));
				end = 0;
			}
		}
	}
}

int	lidar_try_get_resp_print(struct pollfd fds[1], int fd)
{
	int	ret;
	int	res;
	char	buffer[LIDAR_BUFF];

	ret = poll(fds, 1, 1000);
	if (ret > 0)
	{
		if (fds[0].revents & POLLRDNORM)
		{
			write(1, "resp\n\n", 5);
			res = read(fd, buffer, LIDAR_BUFF);
			buffer[res] = 0;
			write(1, buffer, strlen(buffer));
			return (1);
		}
	}
	return (0);
}

void	lidar_get_resp(struct pollfd fds[1], int fd)
{
	int	ret;
	int	res;
	int	end;

	end = 1;
	while(end)
	{
		ret = poll(fds, 1, 1000);
		if (ret > 0)
		{
			if (fds[0].revents & POLLRDNORM)
			{
				res = read(fd, g_buff, LIDAR_BUFF);
				g_buff[res] = '\0';
				end = 0;
			}
		}
	}
}

int	lidar_try_get_resp(struct pollfd fds[1], int fd)
{
	int	ret;
	int	res;

	ret = poll(fds, 1, 1000);
	if (ret > 0)
	{
		if (fds[0].revents & POLLRDNORM)
		{
			res = read(fd, g_buff, LIDAR_BUFF);
			g_buff[res] = '\0';
			return (1);
		}
	}
	return (0);
}
