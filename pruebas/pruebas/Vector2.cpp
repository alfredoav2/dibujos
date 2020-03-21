#include "Vector2.h"
float Vector2::getx() {
	return x;
}
void Vector2::setx(float x) {
	this->x = x;
}
float Vector2::gety() {
	return y;
}
void Vector2::sety(float y) {
	this->y = y;
}
Vector2::Vector2(float x, float y) {
	setx(x);
	sety(y);
}