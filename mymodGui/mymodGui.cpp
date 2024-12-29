#include "mymodGui.h"

/**
 * @brief Constructs the `mymodGui` class and initializes the user interface.
 * 
 * @param parent The parent widget. Defaults to `nullptr` if no parent is specified.
 *               This parameter is passed to the base `QWidget` class.
 */
mymodGui::mymodGui(QWidget *parent)
    : QWidget(parent) // Initializes the base class with the parent widget.
{
    ui.setupUi(this); // Sets up the UI components defined in the associated `.ui` file.
}

/**
 * @brief Destructor for the `mymodGui` class.
 * 
 * Performs cleanup when the `mymodGui` object is destroyed. The UI cleanup is
 * handled automatically by the Qt framework.
 */
mymodGui::~mymodGui()
{}
