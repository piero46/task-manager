import QtQuick
import QtQuick.Controls


Window  {
    visible: true
    width: 640
    height: 480
    title: qsTr("Привет")
     ListModel{
        id:task

    }
     Component.onCompleted: {
         task.clear(); // ← ОЧИСТИТЬ старые задачи!
         var saved = auth.loadTasks();
         for (var i = 0; i < saved.length; i++) {
             task.append({ text: saved[i], color: "#000000" });
         }
     }
    function saveTasksToSettings() {
            var tasks = [];
            for (var i = 0; i < task.count; i++) {
                tasks.push(task.get(i).text);
            }
            auth.saveTasks(tasks);
        }

    Rectangle{
        anchors.fill: parent
        color: "grey"
    }


        Column{
                x:5
                y:200
                Label{
                    text:"Добавление задач"

                }
            Row{
                TextField{
                    id:field
                    placeholderText: "Задача"
                    width: 100
                }
                Image {
                    id: but
                    source: "qrc:/16.png"
                    width: 20
                    height: 20
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if (field.text !== "") {
                                task.append({ text: field.text, color: "#000000" });
                                saveTasksToSettings();
                                field.text = "";
                            }
                        }
                    }
                }
                Rectangle {
                       height: 500
                       width:70
                       color: "transparent"
                   }
                Column{
                        Label{
                            text: "Список Задач"
                            font.family: "ГОСТ ТИП А"
                            font.pixelSize: 18
                        }

                        ListView {
                            width: 300
                            height: 150
                            model: task
                            delegate: Row {
                                          width: ListView.view.width
                                          spacing: 8
                                          Text {
                                              text: model.text
                                              color: model.color
                                              width: parent.width - 60
                                              elide: Text.ElideRight
                                          }

                                          // Кнопка "Выполнено" (галочка)
                                          Image {
                                              source: "qrc:/16.png"
                                              width: 20
                                              height: 18
                                              MouseArea {
                                                  anchors.fill: parent
                                                  onClicked: {
                                                      model.color = "red";
                                                  }
                                              }
                                          }

                                          // Кнопка "Удалить" (корзина)
                                          Image {
                                              source: "qrc:/24.png"
                                              width: 20
                                              height: 18
                                              MouseArea {
                                                  anchors.fill: parent
                                                  onClicked: {
                                                      task.remove(index);
                                                      saveTasksToSettings();
                                                  }
                                              }
                                          }
                                      }
                        }
                }
            }

        }


}
