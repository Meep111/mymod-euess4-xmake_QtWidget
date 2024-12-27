#pragma once

#include <QtWidgets/QWidget>
#include "ui_mymodGui.h"

class mymodGui : public QWidget
{
    Q_OBJECT

public:
    mymodGui(QWidget *parent = nullptr);

    void GuiInit();
    void GuiUpdate();
    void GuiStart();
    ~mymodGui();

private:
    Ui::mymodGuiClass ui;
};
