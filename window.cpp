#include "window.h"

#include <QPushButton>

Window::Window(QWidget *parent) :
 QWidget(parent)
{
 // Set size of the window
 setFixedSize(100, 50);

 // Create and position the button
 m_button = new QPushButton("Hello World", this);
 m_button->setGeometry(10, 10, 80, 30);
 m_button->setCheckable(true);

connect(m_button, SIGNAL (clicked(bool)), this, SLOT (slotButtonClicked(bool)));
}

void Window::slotButtonClicked(bool checked)
{
 if (checked) {
 m_button->setText("Checked");
 } else {
 m_button->setText("Hello World");
 }
}
