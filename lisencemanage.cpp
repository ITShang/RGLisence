#include "lisencemanage.h"
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QTextCodec>
#include <QDate>
#include <QDebug>

QString localDirPath = QDir::currentPath()+QObject::tr("/lic");
QString localFilePath = localDirPath+QObject::tr("/lisence.qlic");


LisenceManage::LisenceManage(QObject *parent) :
    QObject(parent)
{
#ifdef Q_OS_WIN
    QTextCodec *code = QTextCodec::codecForName("GB2312");
    QTextCodec::setCodecForLocale(code);
    QTextCodec::setCodecForCStrings(code);
    QTextCodec::setCodecForTr(code);
#endif
    checkLisenceDir();
    checkLocalInfo();               //��Ȿ��Ӳ����Ϣ
    createLocalLisence();           //���ɻ�����
    createTargetLisence();          //���ɱ�����ʱʶ����
    checkLocalFile();               //��ȡ���������ļ�
    compareLisence();               //�ȽϽ��
}

//��Ȿ��Ӳ����Ϣ
void LisenceManage::checkLocalInfo()
{
    machineID = 987654321;
}

//���ɱ��ػ�����,���͸����ά����Ա
void LisenceManage::createLocalLisence()
{
    QDate date = QDate::currentDate();
    machine.ID = machineID;
    machine.year = date.year();
    machine.month = date.month();
    machine.date = date.day()+10;
    machine.unique = machine.ID + machine.year*machine.month*machine.date;
    localMachineNum = QString("%1%2%3%4%5").arg(machine.ID)
            .arg(machine.year).arg(machine.month)
            .arg(machine.date).arg(machine.unique);
}

//��ȡ���������ļ�
void LisenceManage::checkLocalFile()
{
    QFile file(localFilePath);
    if(!file.open(QFile::ReadOnly))
    {
        QMessageBox::information(0,QObject::tr("��ʾ"),QObject::tr("��ȡ�����ļ��쳣"));
        return;
    }
    nomalReadLocalFile(&file);
}

//���ݱ��������룬��������ʶ��Ψһ�Ե�ʶ���룬�����֤
void LisenceManage::createTargetLisence()
{
    //�˴���Ҫ��ƣ���ν�localMachineNumת��ΪtempLisence
    tempLisence = localMachineNum;
    qDebug()<<__FILE__<<__LINE__<<"\n"
           <<"����ʶ����:"<<tempLisence
          <<"\n";
}

//������ȡ���������ļ�
void LisenceManage::nomalReadLocalFile(QFile *file)
{
    QByteArray byte = file->readAll();
    fileLisence = byte;
    qDebug()<<__FILE__<<__LINE__<<"\n"
           <<"����ʶ����:"<<byte
          <<"\n";
}

//�Ƚ�ÿ��ʵʱ�����ʶ�����Ƿ�������ļ��е����֤һ��
void LisenceManage::compareLisence()
{
    if(tempLisence == fileLisence)
    {
        checkOK = true;
    }
    else
    {
        checkOK = false;
    }
}

//���ؽ��
bool LisenceManage::getCheckResult()
{
    return checkOK;
}

//���������ļ�������
void LisenceManage::fileIsNotExited()
{

}

//��һ������ʱ��Ҫ��������Ĭ��ʱ�������ļ�
void LisenceManage::initFirstRunning()
{

}

//д�����ݵ������ļ�
void LisenceManage::writeParaToLocal()
{
    QFile file(localFilePath);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(0,QObject::tr("��ʾ"),QObject::tr("�ļ�д�����"));
        return;
    }
    char *buff = new char[sizeof(Parameter)];
    memcpy(buff,&machine,sizeof(machine));

    file.write(buff);
    file.close();
}

//����ļ����Ƿ����
void LisenceManage::checkLisenceDir()
{
    QDir dir(localDirPath);
    if(!dir.exists())
    {
        if(!dir.mkdir(localDirPath))
        {
            QMessageBox::information(0,QObject::tr("��ʾ"),QObject::tr("�ļ��д���ʧ��"));
            checkOK = false;
            return;
        }
    }

    QFile file(localFilePath);
    if(!file.open(QFile::ReadWrite))
    {
        QMessageBox::information(0,QObject::tr("��ʾ"),QObject::tr("�����ļ��쳣"));
        file.close();
        return;
    }
    file.close();
}

