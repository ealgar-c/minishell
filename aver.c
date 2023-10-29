#include <unistd.h>

int	main(void)
{
	while (1)
		write(1, "A", 1);
}