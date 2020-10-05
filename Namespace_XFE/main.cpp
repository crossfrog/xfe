#include <iostream>
#include "xfe.h"

int main() {
	xfe::context context(xfe::vector2i{ 640, 480 }, "XFE Dev Project", 60, xfe::colour{ 0, 0, 127 });

	xfe::actor_section as;

	while (context.update());
	return 0;
}