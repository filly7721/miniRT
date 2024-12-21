#include "miniRT.h"

int	keyboard_handler(int keycode, t_minirt *miniRT)
{
	if (keycode == 53)
		(deinit(miniRT), exit(1));
	return (0);
}
