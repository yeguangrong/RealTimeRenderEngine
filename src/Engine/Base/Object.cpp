#include "Object.h"

NAMESPACE_START
Object::Object() {

}

Object::~Object() {

}

bool Object::ref() {
	return ++_refCount > 0;
}

bool Object::unref() {
	return --_refCount <= 0;
}

int Object::getRefCount() {

	return _refCount;
}

NAMESPACE_END



