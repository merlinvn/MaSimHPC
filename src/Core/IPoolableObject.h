
#ifndef MODERNCPP_CORE_IPOOLABLEOBJECT_H
#define MODERNCPP_CORE_IPOOLABLEOBJECT_H
class IPoolableObject {
	virtual void init() = 0;

	virtual void clean() = 0;
};


#endif //MODERNCPP_CORE_IPOOLABLEOBJECT_H