#include "BackupManager.h"
#include "Book.h"
#include "Magazine.h"

// Save a deep copy of the items
void BackupManager::saveBackup(const QList<Item*>& currentItems) {
    backupItems.clear();
    for (Item* item : currentItems) {
        if (item->getType() == "Book")
            backupItems.append(new Book(item->getName()));
        else if (item->getType() == "Magazine")
            backupItems.append(new Magazine(item->getName()));
    }
}

// Return a deep copy of the saved backup
QList<Item*> BackupManager::restoreBackup() {
    QList<Item*> restored;
    for (Item* item : backupItems) {
        if (item->getType() == "Book")
            restored.append(new Book(item->getName()));
        else if (item->getType() == "Magazine")
            restored.append(new Magazine(item->getName()));
    }
    return restored;
}

