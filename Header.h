#pragma once
#include <stdio.h>

void black() {
	printf("\x1B[0m");
}
void red() {
	printf("\x1B[31m");
}
void green() {
	printf("\x1B[32m");
}
void yellow() {
	printf("\x1B[33m");
}