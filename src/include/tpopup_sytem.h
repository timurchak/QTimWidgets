#ifndef TPOPUPSYTEM_H
#define TPOPUPSYTEM_H
#include <tpopup.h>
#include <iostream>
#include <QObject>
#include <QEvent>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QMutex>
#include <QStandardPaths>

#include <plnlog/plnlog.h>

#define POPUP(txt, tittle, mode, interval){ TPopUpSystem::instance().addMessageWithSignal(txt, tittle, mode, interval); }

#define POPUPID(txt, tittle, mode, interval, id){ TPopUpSystem::instance().addMessageWithSignal(txt, tittle, mode, interval,id); }

class TPopUpSystem : public QObject
{
    Q_OBJECT
public:
    static TPopUpSystem& instance(QObject* par = nullptr) {
        std::cout << "TPopSystem instance" << std::endl;
        static TPopUpSystem instance(par);
        return instance;
    }
    TPopUpSystem(const TPopUpSystem &) = delete;
    TPopUpSystem &operator=(const TPopUpSystem &) = delete;
    TPopUpSystem(TPopUpSystem &&) = delete;
    TPopUpSystem &operator=(TPopUpSystem &&) = delete;
    void addMessage(const QString& text, const QString& title = "", bool autoHide = true, int interval = 3, int typeID = -1);
    void addMessageWithSignal(const QString& text, const QString& title = "", bool autoHide = true, int interval = 3, int typeID = -1);
    void setFixedWidthPopUp(int w = -1);
    void setAutoWidthPopUp();
    void setParentWidget(QWidget* par);

    void setEnable(bool value);
    void setLogSett(const QString& path, int lvlLog);

private:
    TPopUpSystem(QObject* par = nullptr);
    int getId();
    void searchTypeID(int id);
private slots:
    void removePopUp(int id);
    bool eventFilter(QObject* target, QEvent* event);
private:
    QWidget *parent;
    QMutex mutex;
    QMap<int, TPopUp*> messages;
    int nextID;
    int width;
    bool enable;    
signals:
    void start();
    void addMessageSignal(const QString&, const QString&, bool, int, int);
};

#endif // TPOPUPSYTEM_H
