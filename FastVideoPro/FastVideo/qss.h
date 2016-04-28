#ifndef QSS_H
#define QSS_H

#include <QString>

// "background-color: transparent;"
/*#define transparentBtn_StyleSheet "QPushButton {"\
        "background-color: transparent;"\
        "border-width: 2px;"\
        "border-radius: 5;}"\
        "QPushButton:hover{background-color: transparent;border-width: 0px;border-radius: 5;}"\
        "QPushButton:pressed{background-color: transparent;padding: 3px;}"*/


#define transparentBtn_StyleSheet "QPushButton {"\
        "background-color: transparent;"\
        "border-width: 0px;"\
        "border-color: white;"\
        "border-style: solid;"\
		"border-radius: 3;}"\
        "QPushButton:hover{border-width: 1px;}"\
        "QPushButton:pressed{padding: 3px;}"
#endif // QSS_H
