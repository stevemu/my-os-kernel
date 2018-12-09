#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "kernel.h"
#include "../libc/string.h"

// global int a = -1;
// global int b = -1;

void main() {

	/*
		test print an character
	*/

	// get high byte and low byte of the cursor

	/*
	port_byte_out(0x3d4, 14);
	int position = port_byte_in(0x3d5);
	position = position << 8;

	port_byte_out(0x3d4, 15);
	position += port_byte_in(0x3d5);

	int offset_from_vga = position * 2;


	char* video_memory = (char*) 0xb8000;
	video_memory[offset_from_vga] = 'W';
	video_memory[offset_from_vga + 1] = 0x0f;
	*/


/*
	clear_screen();
	kprint_at("Xaaaaaaaaaâ", 1,6);
	kprint_at("This text spans multiple lines", 40, 10);
	kprint_at("There is a line\nbreak", 0, 20);
	kprint("There is a line\nbreak");
	kprint_at("What happens when we run out \nof space23424234?", 45, 24);
	*/

/*
	clear_screen();

	int i = 0;
	for (i = 0; i < 24; i++) {
		char str[255];
		int_to_ascii(i, str);
		kprint_at(str, 0, i);
	}

	kprint_at("This text forces the kernel to scroll. Row 0 will disappear.", 60, 24);
	kprint("And with this text, the kernel will scroll again, and row 1 will disappear too!");

*/

/*
	isr_install();

	__asm__ __volatile__("int $1");
	//__asm__ __volatile__("int $3");
*/

	//isr_install();
	//asm volatile("sti");
//	init_timer(50);

	//init_keyboard();

	isr_install();
	irq_install();

	kprint("\n>");

}

void user_input(char *input) {
	// kprint("in user input!");
	// char *test = "";
	// int_to_ascii(a, test);
	// kprint(test);

	if (strcmp(input, "END") == 0) {
		kprint("stopping!");
		asm volatile("hlt");
	} else if (strcmp(input, "POEM") == 0) {
		kprint("Two roads diverged in a yellow wood,\n");
		kprint("And sorry I could not travel both\n");
		kprint("And be one traveler, long I stood\n");
		kprint("And looked down one as far as I could\n");
		kprint("To where it bent in the undergrowth\n");
		
	} else if (strcmp(input, "STEVE") == 0) {
		kprint("Steve is studying at BU.\n");
		
	} 
	
	else {
		kprint("Unknown command.\n");
	}

	kprint(">");

	// int num;

	// if (strcmp(input, "1") == 0) {
	// 	num = 1;
	// } else if (strcmp(input, "2") == 0) {
	// 	num = 2;
	// } else if (strcmp(input, "3") == 0) {
	// 	num = 3;
	// }

	// if a and b both not equal -1, cal and print
	// if a not equal -1, write to b
	// write to a

	// if (a != -1 && b != -1) {
	// 	kprint("cal");
	// 	int c = a + b;
	// 	char *str;
	// 	int_to_ascii(c, str);
	// 	kprint(str + '\n');
	// } else if (a != -1) {
	// 	b = num;
	// } else {
	// 	a = num;
	// }



	//char c = '0' - 48;
	// char c = input[0];
	// kprint(c);


}


