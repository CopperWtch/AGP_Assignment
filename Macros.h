/**
AGP Assignment
Macros.h
Purpose: File which has macros we need for the project. 

@author Marcel Zobus
*/

// is responsible for the creation of the scenes.
// it creates a new scene and calls the init function of it
#define CREATE_FUNC(__TYPE__) \
	static __TYPE__* create() \
{ \
	__TYPE__ *scene = new __TYPE__(); \
if (scene && scene->Init()) \
	{ \
	return scene; \
	} \
	else \
	{ \
	delete scene; \
	scene = NULL; \
	return NULL; \
	} \
}