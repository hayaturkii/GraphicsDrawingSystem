# Graphics Drawing System
An interactive desktop drawing application built with **C++** and the **Qt Framework**. Developed as part of an Object-Oriented Programming (OOP) course, the project demonstrates the use of inheritance, polymorphism, event-driven programming, and graphical user interface development.

## Features
- Draw geometric shapes including:
  - Lines
  - Rectangles
  - Ellipses
  - Polylines
- Select and manipulate existing shapes
- Move shapes using coordinate offsets
- Change shape colors using Qt's built-in color picker
- Real-time calculation of:
  - Area
  - Perimeter
  - Length
- Save and load drawings using custom `.draw` files
- Interactive mouse-based drawing with live visual feedback

## Technologies Used
- C++
- Qt Framework (Widgets, QPainter, QDataStream)
- Object-Oriented Programming (Inheritance, Polymorphism, Encapsulation)

## Architecture
The application is built around an abstract `Shape` base class, allowing all geometric objects to share a common interface while implementing their own drawing and calculation logic.

```text
       +-----------------------+
       |   Shape (Abstract)    |
       +-----------------------+
                   |
     +---------+---+---------+---------+
     |         |             |         |
 +---+---+ +---+---+     +---+---+ +---+---+
 | Line  | | Rect  |     |Ellipse| |Polyline|
 +-------+ +-------+     +-------+ +-------+
