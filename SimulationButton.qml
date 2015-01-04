import QtQuick 2.0

Item {
    id: buttonRoot
    property Simulation simulation: simulationLoader.item
    property string simulationSource
    signal loadSimulation(var fileName)

    Loader {
        id: simulationLoader
        source: simulationSource
    }

    Rectangle {
        id: container
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: nameText.top
            margins: buttonRoot.height * 0.05
        }

        color: "black"
        border.color: "darkgrey"
        border.width: 1.0

        Image {
            anchors {
                fill: parent
                margins: buttonRoot.width * 0.05
            }
            fillMode: Image.PreserveAspectFit
            source: simulation ? simulation.imageSource : ""
        }
    }

    Text {
        id: nameText
        anchors {
            horizontalCenter: parent.horizontalCenter
            margins: buttonRoot.width * 0.02
            bottom: parent.bottom
        }
        text: simulation ? simulation.name : ""
        color: "white"
        font.pixelSize: buttonRoot.height * 0.1

        renderType: Qt.platform.os === "linux" ? Text.NativeRendering : Text.QtRendering
    }
}
