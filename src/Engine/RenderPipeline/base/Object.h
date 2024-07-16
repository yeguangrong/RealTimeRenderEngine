#ifndef Object_H
#define Object_H

#include<Base/Constants.h>

NAMESPACE_START

    class Object
    {
    public:

        Object();
        virtual ~Object();

        virtual bool ref();
        virtual bool unref();
        int getRefCount();

    private:

        int _refCount = 0;
    };


NAMESPACE_END

#endif //Object
