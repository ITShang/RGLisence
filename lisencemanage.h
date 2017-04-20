#ifndef LISENCEMANAGE_H
#define LISENCEMANAGE_H

#include <QObject>
class QFile;

class LisenceManage : public QObject
{
    Q_OBJECT
public:
    enum CheckResult{
        CHECH_RIGHT=0x0,
        CHECK_ERROR=0x1,
        CHECK_FILEISNOTEXITED=0x2,
        CHECK_FILEREADERROR=0x3,
        CHECK_FILEWRITEERROR=0x4,
        CHECK_FILEWRIGHTRIGHT=0x5
    };
    struct Parameter{
        double ID;
        int year;
        int month;
        int date;
        double unique;
    };
    explicit LisenceManage(QObject *parent = 0);
    bool getCheckResult();

private:
    void checkLocalInfo();
    void createLocalLisence();
    void createTargetLisence();
    void checkLocalFile();
    void compareLisence();
    void nomalReadLocalFile(QFile *file);
    void fileIsNotExited();
    void initFirstRunning();
    void writeParaToLocal();
    void checkLisenceDir();

    bool isFirstRun;
    bool checkOK;
    double machineID;
    QString localMachineNum;
    QString tempLisence;
    QString fileLisence;
    Parameter machine;

    
};

#endif // LISENCEMANAGE_H
