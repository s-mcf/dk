#include "../arch/x86/video.h"

void kernel_main() {
	video_init();

	puts("Hello world!");
}
