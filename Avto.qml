import QtQuick
import QtQuick.Controls

ApplicationWindow  {
    id: authWindow
    width: 250
    height: 250
    visible: true
    title: qsTr("Авторизация")
    color: "grey"
    Column {
        anchors.centerIn: parent
        TextField {
            id:field3
            placeholderText: "Логин"
        }
        TextField {
            id:field4
            placeholderText: "Пароль"
        }
        Row {
            Button {
                text: "Вход"
                onClicked: {
                    if (auth.login(field3.text, field4.text)) {
                        var comp = Qt.createComponent("Main.qml");
                        if (comp.status === Component.Ready) {
                            var mainWin = comp.createObject(authWindow);
                            mainWin.show();
                            authWindow.visible = false;
                        } else {
                            console.error("Ошибка загрузки Main.qml:", comp.errorString());
                        }
                    }
                }
            }
            Button {
                text:"Регистрация"
                onClicked: {
                    var comp = Qt.createComponent("Reg.qml");
                            if (comp.status === Component.Ready) {
                                var win = comp.createObject(win);
                                win.show();
                            }

                }
            }
        }
    }

}
