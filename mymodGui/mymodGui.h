#pragma once

// Includes the QtWidgets library for creating graphical user interfaces.
#include <QtWidgets/QWidget>

// Includes the generated UI header file for the `mymodGui` class.
#include "ui_mymodGui.h"

// The `mymodGui` class represents the graphical user interface (GUI) for the application.
// It is a QWidget-based class that provides the main interface functionality.
class mymodGui : public QWidget
{
    Q_OBJECT // Macro enabling Qt's signal and slot mechanism.

public:
    /**
     * @brief Constructs the `mymodGui` class.
     * 
     * @param parent The parent widget. Defaults to `nullptr` for a top-level widget.
     */
    mymodGui(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the `mymodGui` class.
     * 
     * Cleans up resources and performs necessary teardown for the GUI.
     */
    ~mymodGui();

private:
    /**
     * @brief The UI object for managing and interacting with the GUI components.
     * 
     * This object is auto-generated from the associated Qt Designer `.ui` file.
     */
    Ui::mymodGuiClass ui;
};
