#include "rglisence.h"
#include <QMessageBox>

RGLisence::RGLisence()
{
    LisenceManage manage;
    result = manage.getCheckResult();
}

bool RGLisence::getLisenceResult()
{
    if(result)
    {
        QMessageBox::information(0,QObject::tr("提示"),QObject::tr("软件使用期内"));
    }
    else
    {
        QMessageBox::information(0,QObject::tr("提示"),QObject::tr("许可证到期"));
    }
    return result;
}

bool getLisenceResult()
{
    RGLisence lisence;
    return lisence.getLisenceResult();
}
