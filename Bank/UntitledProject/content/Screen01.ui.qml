/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick 6.5
import QtQuick.Controls 6.5
import UntitledProject

Rectangle {
    width: 700
    height: 500
    opacity: 1

    color: Constants.backgroundColor

    TextInput {
        id: textInput
        x: 275
        y: 246
        width: 150
        height: 30
        text: qsTr("")
        font.pixelSize: 12
    }

    TextInput {
        id: textInput1
        x: 275
        y: 210
        width: 150
        height: 30
        font.pixelSize: 12
        wrapMode: Text.NoWrap
        rightPadding: 1
        leftPadding: 1
        bottomPadding: 1
        topPadding: 1
    }

    Text {
        id: text1
        x: 270
        y: 173
        width: 150
        height: 20
        text: qsTr("Enter name and password")
        font.pixelSize: 12
    }

    Text {
        id: text2
        x: 236
        y: 246
        width: 33
        height: 30
        text: qsTr("Pin")
        font.pixelSize: 12
    }

    Text {
        id: text3
        x: 236
        y: 210
        width: 33
        height: 30
        text: qsTr("Name")
        font.pixelSize: 12
    }

    Button {
        id: button
        x: 305
        y: 282
        text: qsTr("Login")
        checkable: false
        highlighted: true
        flat: false
    }
}
