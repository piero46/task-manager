import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs


Window {
    width: 250
    height: 250
    visible: false
    id:regform
    title: qsTr("Регистрация")
    MessageDialog {
        id: dialog
        title: "Успех"
        buttons: MessageDialog.Ok
        text: "Регистрация прошла успешно!"
    }
    MessageDialog {
        id: dialog1
        title: "Неудача"
        buttons: MessageDialog.Ok
        text: "Попробуйте снова"
    }
    Column {
        anchors.centerIn: parent
        TextField {
            id:loginField
            placeholderText: "Логин"
        }
        TextField {
            id:passField
            placeholderText: "Пароль"
        }

        Button {
            text:"Регистрация"
            onClicked: {
                if(auth.registerUser(loginField.text,passField.text)){
                    dialog.open();

                }else{
                   dialog1.open();
                }
            }
        }

    }
}
