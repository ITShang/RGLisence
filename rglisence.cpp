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
        QMessageBox::information(0,QObject::tr("��ʾ"),QObject::tr("���ʹ������"));
    }
    else
    {
        QMessageBox::information(0,QObject::tr("��ʾ"),QObject::tr("���֤����"));
    }
    return result;
}

bool getLisenceResult()
{
    RGLisence lisence;
    return lisence.getLisenceResult();
}
