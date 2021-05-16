#include "backend.h"
#include <QDebug>
#include <QString>
#include <string>

using namespace std;

Backend::Backend(QObject *parent) : QObject(parent)
{

}

// set the suspend state (called from QML)
void Backend::setEnabled(bool state)
{
    curstate = state;
    qInfo() << "setEnabled:" << state ;
    SetSuspendState(state);
    emit enabledChanged(state);
}

// get the XFCE lid-close suspend and update the UI
void Backend::setEnabled()
{
    bool state = GetSuspendState();
    curstate = state;
    qInfo() << "setEnabled:" << state ;
    emit enabledChanged(state);
}

// run a command in the shell and grap the output
QString Backend::exec(QString cmdToRun)
{
    string sCmd = cmdToRun.toStdString();
    const char* cmd = sCmd.c_str();
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    QString res = QString::fromStdString(result).trimmed();
    return res;

}

/*
 * Get the lid-action using the xfconf-query cmdline tool
 *
 * 1 = suspend, 3 = lock screen
 *
 */
bool Backend::GetSuspendState()
{
    QString cmdOnAC = "xfconf-query -c xfce4-power-manager -p /xfce4-power-manager/lid-action-on-ac";
    auto res = exec(cmdOnAC);
    qInfo() << "cmdOnAC: " << res;
    if(res == "1") {
        return true;
    } else {
        return false;
    }

}

/*
 * Set the lid-action using the xfconf-query cmdline tool
 *
 * 1 = suspend, 3 = lock screen
 *
 */
void Backend::SetSuspendState(bool state)
{
    QString cmdOnBattery = "xfconf-query -c xfce4-power-manager -p /xfce4-power-manager/lid-action-on-battery";
    QString cmdOnAC = "xfconf-query -c xfce4-power-manager -p /xfce4-power-manager/lid-action-on-ac";
    QString res;

    if(state) {
        cmdOnAC += " -s 1";
        cmdOnBattery += " -s 1";
    } else {
        cmdOnAC += " -s 3";
        cmdOnBattery += " -s 3";
    }

    res = exec(cmdOnAC);
    res = exec(cmdOnBattery);
    qInfo() << "SetSuspendState" << state;
}

