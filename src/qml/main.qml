import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import CORE

ApplicationWindow {
    id: root

    visible: true

    title: qsTr("Mine Sweeper")

    width: 1080
    height: 720

    Controller { id: controller }

    GridLayout {
        anchors.centerIn: parent

        columnSpacing: 0
        rowSpacing: 0

        rows: controller.rows
        columns: controller.columns

        Repeater {

            model: parent.rows * parent.columns

            Rectangle {
                width: 25
                height: 25
                color: "#333333"
                border.color: "#888888"

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        parent.color = "green"
                    }
                }
            }
        }
    }
}
