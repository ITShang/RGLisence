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
    checkLocalInfo();               //检测本地硬件信息
    createLocalLisence();           //生成机器码
    createTargetLisence();          //生成本地临时识别码
    checkLocalFile();               //读取本地配置文件
    compareLisence();               //比较结果
}

//检测本地硬件信息
void LisenceManage::checkLocalInfo()
{
    machineID = 987654321;
}

//生成本地机器码,发送给软件维护人员
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

//读取本地配置文件
void LisenceManage::checkLocalFile()
{
    QFile file(localFilePath);
    if(!file.open(QFile::ReadOnly))
    {
        QMessageBox::information(0,QObject::tr("提示"),QObject::tr("读取配置文件异常"));
        return;
    }
    nomalReadLocalFile(&file);
}

//根据本机机器码，生成用于识别唯一性的识别码，即许可证
void LisenceManage::createTargetLisence()
{
    //此处需要设计，如何将localMachineNum转换为tempLisence
    tempLisence = localMachineNum;
    qDebug()<<__FILE__<<__LINE__<<"\n"
           <<"本地识别码:"<<tempLisence
          <<"\n";
}

//正常读取本地配置文件
void LisenceManage::nomalReadLocalFile(QFile *file)
{
    QByteArray byte = file->readAll();
    fileLisence = byte;
    qDebug()<<__FILE__<<__LINE__<<"\n"
           <<"配置识别码:"<<byte
          <<"\n";
}

//比较每次实时计算的识别码是否和配置文件中的许可证一致
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

//返回结果
bool LisenceManage::getCheckResult()
{
    return checkOK;
}

//本地配置文件不存在
void LisenceManage::fileIsNotExited()
{

}

//第一次运行时需要创建本地默认时间配置文件
void LisenceManage::initFirstRunning()
{

}

//写入内容到本地文件
void LisenceManage::writeParaToLocal()
{
    QFile file(localFilePath);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(0,QObject::tr("提示"),QObject::tr("文件写入错误"));
        return;
    }
    char *buff = new char[sizeof(Parameter)];
    memcpy(buff,&machine,sizeof(machine));

    file.write(buff);
    file.close();
}

//检测文件夹是否存在
void LisenceManage::checkLisenceDir()
{
    QDir dir(localDirPath);
    if(!dir.exists())
    {
        if(!dir.mkdir(localDirPath))
        {
            QMessageBox::information(0,QObject::tr("提示"),QObject::tr("文件夹创建失败"));
            checkOK = false;
            return;
        }
    }

    QFile file(localFilePath);
    if(!file.open(QFile::ReadWrite))
    {
        QMessageBox::information(0,QObject::tr("提示"),QObject::tr("配置文件异常"));
        file.close();
        return;
    }
    file.close();
}

