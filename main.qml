import QtQuick 6.0
import QtQuick.Window 6.0
import QtQuick.Controls 6.0
import QtQuick.Controls.Material 6.0

ApplicationWindow {
    id: window
    width: 400
    height: 400
    visible: true
    title: qsTr("Xfce Suspend")

    flags: Qt.WindowCloseButtonHint | Qt.WindowMinimizeButtonHint | Qt.CustomizeWindowHint | Qt.Dialog | Qt.WindowTitleHint

    Material.theme: Material.Dark
    Material.accent: Material.Blue



    Rectangle {
        id: topbar
        height: 40
        color: Material.color(Material.Purple)

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: 10
        }
        radius: 10

        Text {
            id: toptext
            text: qsTr("XFCE Lid Close Action")
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: "#ffffff"
            font.pointSize: 12
        }

        Image {
            id: image
            width: 200
            height: 200
            source: "images/lid_close.png"
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: topbar.bottom
                topMargin: 25
            }

        }

        Rectangle {
            id: container
            anchors.top: image.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin : 25
            width: parent.width
            height: 60
            //color: Material.color(Material.Lime)
            color: "transparent"

            radius: 10

            Text {
                id: lblSuspend
                text: qsTr("Suspend")
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: "#ffffff"
                font.pointSize: 20
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 30
            }

            Switch {
                id: btnSuspend
                anchors.right: parent.right
                anchors.verticalCenter: text.verticalCenter
                anchors.rightMargin: 20
                checked: backend ? backend.isEnabled : false
                onClicked: {
                    backend.setEnabled(checked);
                }
            }

        }


    }

    Connections {
        target: backend
   }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
