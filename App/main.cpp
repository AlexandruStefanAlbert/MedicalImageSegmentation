#include "MedicalSegmentation.h"
#include <QtWidgets/QApplication>
#include <qfiledialog.h>




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QDialog widget;
    Ui::MainWindow ui;
    ui.setupUi(&widget);
    
    
    widget.show();
    return app.exec();
}


