#include "include/tpopup.h"

TPopUp::TPopUp(QWidget* _par, bool _autoHide, int _interval, int _id, int _typeID)
    : QWidget(_par)
    , par(_par)
    , labelText(new QLabel(this))
    , labelTitle(new QLabel(this))
    , btnClose(new QPushButton)
    , layout(new QVBoxLayout(this))
    , animation(new QPropertyAnimation(this))
    , popupOpacity(0.0)
    , timer(new QTimer(this))
    , posOffset(0)
    , id(_id)
    , autoHide(_autoHide)
    , interval(_interval * 1000)
    , fixedWith(-1)
    , typeID(_typeID)
{
    PLNLOGF(TPopUp, DBG_INFO, "c-r");
    setParent(_par);
    const void* address = static_cast<const void*>(par);
    std::stringstream ss;
    ss << address;
    std::string name = ss.str();
    if (par != nullptr) {
        PLNLOGF(TPopUp, DBG_TRACE, "TPopUp parent LIVE " << name);
    } else {
        PLNLOGF(TPopUp, DBG_ERROR, "TPopUp parent DEAD " << name)
    }
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);
    animation->setTargetObject(this);
    animation->setPropertyName("popupOpacity");
    connect(animation, &QAbstractAnimation::finished, this, &TPopUp::hide);

    labelText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    labelTitle->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    // labelTitle->setMaximumHeight(30);
    // labelTitle->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
    labelTitle->setStyleSheet("QLabel { color : white; "
                              "font-weight: bold;"
                              "margin-top: 6px;"
                              "margin-bottom: 0px;"
                              "margin-left: 10px;"
                              "margin-right: 10px; }");
    labelText->setStyleSheet("QLabel { color : white; "
                             "margin-top: 6px;"
                             "margin-bottom: 6px;"
                             "margin-left: 10px;"
                             "margin-right: 10px; }");

    btnClose->setStyleSheet("border-style: outset;"
                            "border-width: 2px;"
                            "border-radius: 10px;"
                            "border-color: beige;"
                            "font: bold 10px;"
                            "color : white;"
                            "min-width: 10em;"
                            "padding: 6px;");

    btnClose->setText("Закрыть");
    layout->addWidget(labelTitle);
    layout->addWidget(labelText);
    layout->setStretch(0, 2);
    layout->setStretch(1, 6);
    if (!autoHide) {
        layout->addWidget(btnClose);
        layout->setStretch(2, 2);
        connect(btnClose, &QPushButton::clicked, this, &TPopUp::hideWithButton);
    }
    // auto* spacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    // layout->addItem(spacer,3,0);
    setLayout(layout);
    if (_autoHide) {
        connect(timer, &QTimer::timeout, this, &TPopUp::hideAnimation);
    }
}

TPopUp::~TPopUp()
{
    PLNLOGF(TPopUp, DBG_TRACE, "d-r");
    // QPainter::end();
    delete labelText;
    delete labelTitle;
    delete btnClose;
    delete layout;
    delete animation;
    delete timer;
}

float TPopUp::getPopupOpacity() const { return popupOpacity; }

void TPopUp::setPopupOpacity(float opacity)
{
    popupOpacity = opacity;
    setWindowOpacity(opacity);
}

void TPopUp::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect roundedRect;
    roundedRect.setX(rect().x() + 5);
    roundedRect.setY(rect().y() + 5);
    roundedRect.setWidth(rect().width() - 10);
    roundedRect.setHeight(rect().height() - 10);

    painter.setBrush(QBrush(QColor(0, 0, 0, 180)));
    painter.setPen(Qt::NoPen);

    painter.drawRoundedRect(roundedRect, 10, 10);
}

void TPopUp::setPopupText(const QString& text, const QString& title)
{
    labelText->setText(text);
    labelTitle->setText(title);
    adjustSize();
}

void TPopUp::show()
{
    const void* address = static_cast<const void*>(par);
    std::stringstream ss;
    ss << address;
    std::string name = ss.str();
    if (par != nullptr) {
        PLNLOGF(TPopUp, DBG_TRACE, "TPopUp parent LIVE " << name);
    } else {
        PLNLOGF(TPopUp, DBG_ERROR, "TPopUp parent DEAD " << name)
    }
    setWindowOpacity(0.0);

    animation->setDuration(150);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    // auto screen = this->window()->windowHandle()->screen();
    setGeometry(par->pos().x() + par->width() - width(),
        par->pos().y() + par->height() - height() - posOffset, width(), height());
    QWidget::show();
    // parentWidget()->activateWindow();

    animation->start();
    if (autoHide) {
        timer->start(interval);
    }
}

void TPopUp::setPosOffset(int y) { posOffset = y; }

void TPopUp::setLivePosOffset(int y) { setGeometry(pos().x(), pos().y() + y, width(), height()); }

void TPopUp::offsetForNewPosParent(int dx, int dy)
{
    PLNLOGF(TPopUp, DBG_INFO,
        "TPopUp parent LIVE "
            << "TPopUp: offset: dx" << dx << " dy " << dy);
    setGeometry(pos().x() - dx, pos().y() - dy, width(), height());
}

void TPopUp::offsetForResizeParent(int dx) { setGeometry(pos().x() - dx, pos().y(), width(), height()); }

void TPopUp::setFixedPopUp(int w)
{
    fixedWith = w;
    if (w == -1) {
        adjustSize();
        return;
    }
    setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
    setFixedWidth(w);
    // std::cout << "Установка фиксированный ширины и перенос слов" << std::endl;
    labelText->setWordWrap(true);
    labelTitle->setWordWrap(true);
    adjustSize();
    PLNLOGF(TPopUp, DBG_INFO, "TPopUp set fixedWidth " << w << " and word wrap")
}

void TPopUp::hideAnimation()
{
    timer->stop();
    animation->setDuration(1000);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    animation->start();
}

void TPopUp::hide()
{
    if (getPopupOpacity() == 0.0) {
        QWidget::hide();
        emit hidePopUp(id);
    }
}

void TPopUp::hideWithButton()
{
    par->setFocus();
    timer->stop();
    QWidget::hide();
    emit hidePopUp(id);
}

int TPopUp::getTypeID() const { return typeID; }
