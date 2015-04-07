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