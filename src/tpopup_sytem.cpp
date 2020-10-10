#include "include/tpopup_sytem.h"

TPopUpSystem::TPopUpSystem(QObject* par)
    : QObject(par)
    , parent(nullptr)
    , nextID(-1)
    , width(-1)
    , enable(true)
{

    plnlog::Config conf;
    conf.timeFormat = plnlog::TimeFormat::Timestamp;
    conf.maxLogLevel = DBG_INFO;
    conf.rotationEnabled = false;
    plnlog::FacilitiesConfig facilitiesConfig;
    facilitiesConfig["TPopUpSystem"].maxLogLevel = DBG_INFO;
    facilitiesConfig["TPopUp"].maxLogLevel = DBG_INFO;
    PLNLOGF_CONFIGURE(conf, "", facilitiesConfig);
    PLNLOGF(TPopUpSystem, DBG_INFO, "c-r")
    connect(this, &TPopUpSystem::addMessageSignal, this, &TPopUpSystem::addMessage,
        Qt::ConnectionType::QueuedConnection);
}

void TPopUpSystem::addMessage(
    const QString& text, const QString& title, bool autoHide, int interval, int typeID)
{
    if (!enable) {
        return;
    }
    PLNLOGF(TPopUpSystem, DBG_INFO, "try add PopUp")
    PLNLOGF(TPopUpSystem, DBG_TRACE, "try add PopUp")
    searchTypeID(typeID);
    int id = getId();
    if (messages.isEmpty()) {
        TPopUp* popUp = new TPopUp(parent, autoHide, interval, id, typeID);
        connect(popUp, &TPopUp::hidePopUp, this, &TPopUpSystem::removePopUp);
        connect(this, &TPopUpSystem::start, popUp, &TPopUp::show, Qt::ConnectionType::QueuedConnection);
        popUp->setPopupText(text, title);
        popUp->setFixedPopUp(width);

        // emit start();
        disconnect(this, &TPopUpSystem::start, popUp, &TPopUp::show);
        popUp->show();
        messages[id] = popUp;
        PLNLOGF(TPopUpSystem, DBG_INFO,
            "List TPopUp empty create new PopUp №" << id << " count now = " << messages.count())

    } else {
        int y1 = parent->pos().y();
        int y2 = messages.last()->pos().y();
        int H2 = messages.last()->height();
        if (y2 - H2 <= y1) {
            removePopUp(messages.firstKey());
            y1 = parent->pos().y();
            y2 = messages.last()->pos().y();
        }
        int H1 = parent->height();
        int y = H1 - (y2 - y1);
        TPopUp* popUp = new TPopUp(parent, autoHide, interval, id, typeID);
        connect(popUp, &TPopUp::hidePopUp, this, &TPopUpSystem::removePopUp);
        connect(this, &TPopUpSystem::start, popUp, &TPopUp::show, Qt::ConnectionType::QueuedConnection);
        popUp->setPopupText(text, title);
        popUp->setFixedPopUp(width);
        popUp->setPosOffset(y);
        popUp->show();
        // emit start();
        disconnect(this, &TPopUpSystem::start, popUp, &TPopUp::show);
        // popUp->show();
        messages[id] = popUp;
        PLNLOGF(TPopUpSystem, DBG_INFO,
            "List TPopUp not empty add new PopUp №" << id << " to list, count now = " << messages.count()
                                                    << " position offset = " << y)
    }
}

void TPopUpSystem::addMessageWithSignal(
    const QString& text, const QString& title, bool autoHide, int interval, int typeID)
{
    emit addMessageSignal(text, title, autoHide, interval, typeID);
}

void TPopUpSystem::setFixedWidthPopUp(int w) { width = w; }

void TPopUpSystem::setAutoWidthPopUp() { width = -1; }

void TPopUpSystem::setParentWidget(QWidget* par)
{
    parent = par;
    par->installEventFilter(this);
}

int TPopUpSystem::getId()
{
    nextID++;
    if (nextID > 1e5) {
        nextID = 0;
    }
    return nextID;
}

void TPopUpSystem::searchTypeID(int id)
{
    auto it = messages.begin();
    while (it != messages.end()) {
        if (it.value()->getTypeID() == id) {
            removePopUp(it.key());
            it = messages.begin();
        } else {
            ++it;
        }
    }
}

void TPopUpSystem::removePopUp(int id)
{
    mutex.lock();
    int y = messages[id]->height();
    auto removeY = messages[id]->pos().y();
    messages[id]->deleteLater();
    messages.remove(id);
    PLNLOGF(TPopUpSystem, DBG_INFO, "Deleted PopUp №" << id << " now count = " << messages.count())
    for (auto& item : messages) {
        if (item->pos().y() < removeY) {
            item->setLivePosOffset(y);
        }
    }
    mutex.unlock();
}

bool TPopUpSystem::eventFilter(QObject* target, QEvent* event)
{
    if (target == parent) {
        if (event->type() == QEvent::Move) {
            // auto test = dynamic_cast<QWidget*>(target);
            auto mEvent = dynamic_cast<QMoveEvent*>(event);
            auto posNew = mEvent->pos();
            auto posOld = mEvent->oldPos();
            int dx = posOld.x() - posNew.x();
            int dy = posOld.y() - posNew.y();
            for (auto& item : messages) {
                item->offsetForNewPosParent(dx, dy);
            }
            return true;
        }
        if (event->type() == QEvent::Resize) {
            auto rEvent = dynamic_cast<QResizeEvent*>(event);
            auto sizeNew = rEvent->size();
            auto sizeOld = rEvent->oldSize();
            int dx = sizeOld.width() - sizeNew.width();
            for (auto& item : messages) {
                item->offsetForResizeParent(dx);
            }
            return true;
        }
    }
    return QObject::eventFilter(target, event);
}

void TPopUpSystem::setEnable(bool value) { enable = value; }

void TPopUpSystem::setLogSett(const QString& path, int lvlLog)
{
    plnlog::Config conf;
    conf.timeFormat = plnlog::TimeFormat::Timestamp;
    conf.maxLogLevel = lvlLog;
    conf.rotationEnabled = false;
    plnlog::FacilitiesConfig facilitiesConfig;
    facilitiesConfig["TPopUpSystem"].maxLogLevel = lvlLog;
    facilitiesConfig["TPopUp"].maxLogLevel = lvlLog;
    PLNLOGF_CONFIGURE(conf, path.toStdString().c_str(), facilitiesConfig);
}
