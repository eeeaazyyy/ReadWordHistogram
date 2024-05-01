import QtQuick 
import QtQuick.Controls 
import QtQuick.Dialogs 
import QtQuick.Window
import QtQuick.Layouts

import io.qt.examples.backend


Window {
    visible: true
    width: 640
    height: 480
    title: "Histogram Example"


    property string fileName: "" // Создаем переменную fileName
    property bool stopThread: false



    GridLayout{
        anchors.fill: parent
        columns: 5
        rows: 4

        ControlButton{

            id:conBut
            objectName: "contBut"
            signal qmlSignalStart()
            signal qmlSignalSenFile(string file)

        }
        TextHandler{
            id: textHand
        }



        Histogram {

            id: histogram
            objectName: "Hist"
            Layout.row: 0
            Layout.column: 0
            visible: true
            Layout.columnSpan: 5
            Layout.rowSpan: 2
            Layout.fillWidth: true
            Layout.fillHeight: true
            signal qmlSignalAddItem()
        }



            GridLayout{
                id: layoutBut
                Layout.row: 3
                Layout.column: 0
                Layout.preferredHeight: 65
                Layout.preferredWidth: 260

                Button {
                    text: "Обзор.."
                    Layout.preferredWidth: 60
                    Layout.preferredHeight: 30
                    Layout.row: 0
                    Layout.column: 0

                    onClicked: {
                        fileDialog.open()
                    }
                }




                    FileDialog {
                        id: fileDialog
                        title: "Please choose a file"
                        onAccepted: {
                            console.log("You chose: " + selectedFile)
                            fileName = selectedFile // Сохраняем выбранный файл в переменную fileName
                            fileLabel.text = selectedFile
                            conBut.slotSetFileName(fileName)

                        }
                        onRejected: {
                            console.log("Canceled")
                        }
                    }

                Button {
                    id: startButton
                    text: "Start"
                    Layout.preferredWidth: 60
                    Layout.preferredHeight: 30
                    Layout.row: 0
                    Layout.column: 1 // Измените позицию кнопки, если нужно

                    onClicked: {
                        if (fileName !== "" ) {
                            //histogram.slotRead(fileName) // Вызываем функцию с передачей fileName
                            conBut.slotButStart()
                            fileName = ""
                            //conBut.qmlSignalStart()

                        } else {
                            console.log("No file selected")
                        }
                    }
                }
                Button {
                    id: stopButton
                    text: "Pause"
                    Layout.preferredWidth: 60
                    Layout.preferredHeight: 30
                    Layout.row: 0
                    Layout.column: 2 // Измените позицию кнопки, если нужно

                    onClicked: {
                            conBut.slotButPauseResume(0)
                    }
                }
                Button {
                    id: resumeButton
                    text: "Resume"
                    Layout.preferredWidth: 60
                    Layout.preferredHeight: 30
                    Layout.row: 0
                    Layout.column: 3 // Измените позицию кнопки, если нужно

                    onClicked: {
                            conBut.slotButPauseResume(1)
                        }
                    }

                Button {
                    id: cancelButton
                    text: "Cancel"
                    Layout.preferredWidth: 60
                    Layout.preferredHeight: 30
                    Layout.row: 0
                    Layout.column: 4 // Измените позицию кнопки, если нужно

                    onClicked: {
                        fileName = ""
                        fileLabel.text = ""
                        //histogram.slotCancel()
                        conBut.slotButCancel()
                        //stopThread = true

                    }
                }
                Label {
                    id: fileLabel
                    Layout.preferredWidth: 240
                    Layout.preferredHeight: 30
                    Layout.row: 1
                    Layout.columnSpan: 4
                    Layout.column: 0
                    text: "No file selected" // Изначальное значение
                }

            }


            ProgressBar {
                from: 0
                to: 100
                id: progressBar
                value: conBut.progressBarValue
                visible: true
                Layout.row: 4
                Layout.column: 0
                Layout.columnSpan: 5
                Layout.fillWidth: true
            }


//            function onSetFile(fileName){
//                textHand.setSourceFile(fileName)
//            }
            Component.onCompleted: {
                //conBut.signalSendFile.connect(textHand.setSourceFile)
                //conBut.signalSendFile.connect(conBut.qmlSignalSenFile)
                //conBut.signalStart.connect(textHand.start)
                //threadHandler.started.connect(textHand.start)
                conBut.signalPause.connect(textHand.pause)
                conBut.signalResume.connect(textHand.resume)
                conBut.signalCancel.connect(textHand.reset)
                conBut.signalCancel.connect(histogram.slotClearHistogram)


                textHand.addItem.connect(histogram.slotFillItemsHistogram)
                textHand.progressChanged.connect(conBut.getPercentFromTotalBytes)
            }


    }
}
