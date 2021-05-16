#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <string>

using namespace std;

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)

public:
    explicit Backend(QObject *parent = nullptr);
    bool isEnabled() const { return curstate; };

public slots:
    void setEnabled(bool state);
    void setEnabled();

signals:
    void enabledChanged(bool newstate);

private:
    bool curstate {false} ;
    QString exec(QString cmdToRun);
    bool GetSuspendState();
    void SetSuspendState(bool state);

};

#endif // BACKEND_H
