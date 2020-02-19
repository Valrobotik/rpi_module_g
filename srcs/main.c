#include "main.h"
#include "open.h"
#include <stdio.h>

#define BAUDRATE B19200


/* set interface for lidar */

int	set_interface_attribs(int fd, int speed, int parity)
{
	struct termios serial;

	if (tcgetattr(fd, &serial) < 0) {
		perror("Getting configuration");
		return -1;
	}
	memset(&serial, 0, sizeof(serial));
	if (tcgetattr(fd, &serial) != 0)
	{
		ft_putstr("can't get attributes of tty\n");
		return (-1);
	}
	cfsetospeed(&serial, speed);
	cfsetispeed(&serial, speed);
	serial.c_cflag = (serial.c_cflag & ~CSIZE) | CS8;	//8 bits char
	serial.c_iflag &= ~IGNBRK;				//Ignore break in input flags, do not take \00 as break
	serial.c_oflag = 0;
	serial.c_lflag = 0;
	serial.c_cc[VMIN] = 0;					//read does not block
	serial.c_cc[VTIME] = 0;					//time out : 5 = 0.5 sec 
	serial.c_iflag &= ~(IXON | IXOFF | IXANY);
	serial.c_cflag |=  (CLOCAL | CREAD);
	serial.c_cflag &=  (PARENB | PARODD);
	serial.c_cflag |=  parity;
	serial.c_cflag &=  ~CSTOPB;
	serial.c_cflag &= ~CRTSCTS;
	tcsetattr(fd, TCSANOW, &serial);			// Apply configuration
	return (0);
}

void	init_pin(void)
{
	bcm2835_gpio_fsel(PINOUT, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(PINREED, BCM2835_GPIO_FSEL_INPT);	
	bcm2835_gpio_fsel(PINRESET, BCM2835_GPIO_FSEL_INPT);	
	bcm2835_gpio_fsel(PINSIDE, BCM2835_GPIO_FSEL_INPT);	
	bcm2835_gpio_fsel(10, BCM2835_GPIO_FSEL_INPT);	//bouton gauche	
	bcm2835_gpio_fsel(9, BCM2835_GPIO_FSEL_INPT);	//bouton droit
	bcm2835_gpio_fsel(17, BCM2835_GPIO_FSEL_INPT);	//switch color
}

int 	main(int argc, char** argv)
{
	g_fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NONBLOCK);	//glo
	if (g_fd == -1)
	{
		perror(argv[1]);
	}
	g_fds[0].fd = g_fd;
	g_fds[0].events = POLLRDNORM;
	if (!bcm2835_init())
		return (1);
	init_pin();		//select INPUT/OUTPUT pin
	if (argc > 1)		//si il y a un argument (probablement un flag)
	{
		do_flag(argv[1], argc, argv);		//fonction dans flag.c
		return (0);
	}
	ft_putstr("argument missing:\n");
	ft_putstr("-m for match condition\n");
	ft_putstr("-i for an unfinished interface\n");
	ft_putstr("-l for the lidar interface\n");
	return (1);
}
