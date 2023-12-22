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
            model: controller.tileModel

            Rectangle {
                width: 25
                height: 25
                color: {
                    switch(model.state){
                        default:
                        case 0: return "#333333";
                        case 1: return "green"
                        case 2: return "red"
                        case 3: return "orange"
                    }
                }
                border.color: "#888888"

                Label {
                    anchors.centerIn: parent
                    width: 15
                    height: 15
                    text: model.state === 1 ? display : ""
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        controller.onTileClicked(index);
                    }
                }
            }
        }
    }
}
