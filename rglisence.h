#ifndef RGLISENCE_H
#define RGLISENCE_H

#include "rglisence_global.h"
#include "lisencemanage.h"

class RGLISENCESHARED_EXPORT RGLisence
{
    
public:
    RGLisence();
    bool getLisenceResult();
private:
    bool result;
};

extern "C" RGLISENCESHARED_EXPORT bool getLisenceResult();

#endif // RGLISENCE_H
