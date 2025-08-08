#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H

#include <QList>
#include "Items.h"

class BackupManager{
private:
    QList<Item*> backupItems;

public:
    void saveBackup(const QList<Item*>& currenItems);
    QList<Item*> restoreBackup();

};

#endif // BACKUPMANAGER_H
