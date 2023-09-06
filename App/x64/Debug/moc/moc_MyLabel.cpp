/****************************************************************************
** Meta object code from reading C++ file 'MyLabel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../MyLabel.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyLabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_MyLabel_t {
    uint offsetsAndSizes[26];
    char stringdata0[8];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[10];
    char stringdata5[13];
    char stringdata6[11];
    char stringdata7[13];
    char stringdata8[2];
    char stringdata9[16];
    char stringdata10[13];
    char stringdata11[15];
    char stringdata12[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MyLabel_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MyLabel_t qt_meta_stringdata_MyLabel = {
    {
        QT_MOC_LITERAL(0, 7),  // "MyLabel"
        QT_MOC_LITERAL(8, 10),  // "mousePress"
        QT_MOC_LITERAL(19, 0),  // ""
        QT_MOC_LITERAL(20, 5),  // "paint"
        QT_MOC_LITERAL(26, 9),  // "mouseMove"
        QT_MOC_LITERAL(36, 12),  // "mouseRelease"
        QT_MOC_LITERAL(49, 10),  // "paintEvent"
        QT_MOC_LITERAL(60, 12),  // "QPaintEvent*"
        QT_MOC_LITERAL(73, 1),  // "e"
        QT_MOC_LITERAL(75, 15),  // "mousePressEvent"
        QT_MOC_LITERAL(91, 12),  // "QMouseEvent*"
        QT_MOC_LITERAL(104, 14),  // "mouseMoveEvent"
        QT_MOC_LITERAL(119, 17)   // "mouseReleaseEvent"
    },
    "MyLabel",
    "mousePress",
    "",
    "paint",
    "mouseMove",
    "mouseRelease",
    "paintEvent",
    "QPaintEvent*",
    "e",
    "mousePressEvent",
    "QMouseEvent*",
    "mouseMoveEvent",
    "mouseReleaseEvent"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MyLabel[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,    1 /* Public */,
       3,    0,   63,    2, 0x06,    2 /* Public */,
       4,    0,   64,    2, 0x06,    3 /* Public */,
       5,    0,   65,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,   66,    2, 0x0a,    5 /* Public */,
       9,    1,   69,    2, 0x0a,    7 /* Public */,
      11,    1,   72,    2, 0x0a,    9 /* Public */,
      12,    1,   75,    2, 0x0a,   11 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,    8,
    QMetaType::Void, 0x80000000 | 10,    8,
    QMetaType::Void, 0x80000000 | 10,    8,

       0        // eod
};

Q_CONSTINIT const QMetaObject MyLabel::staticMetaObject = { {
    QMetaObject::SuperData::link<QLabel::staticMetaObject>(),
    qt_meta_stringdata_MyLabel.offsetsAndSizes,
    qt_meta_data_MyLabel,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MyLabel_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MyLabel, std::true_type>,
        // method 'mousePress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'paint'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'mouseMove'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'mouseRelease'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'paintEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPaintEvent *, std::false_type>,
        // method 'mousePressEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'mouseMoveEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'mouseReleaseEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>
    >,
    nullptr
} };

void MyLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyLabel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->mousePress(); break;
        case 1: _t->paint(); break;
        case 2: _t->mouseMove(); break;
        case 3: _t->mouseRelease(); break;
        case 4: _t->paintEvent((*reinterpret_cast< std::add_pointer_t<QPaintEvent*>>(_a[1]))); break;
        case 5: _t->mousePressEvent((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 6: _t->mouseMoveEvent((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 7: _t->mouseReleaseEvent((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyLabel::*)();
            if (_t _q_method = &MyLabel::mousePress; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyLabel::*)();
            if (_t _q_method = &MyLabel::paint; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyLabel::*)();
            if (_t _q_method = &MyLabel::mouseMove; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MyLabel::*)();
            if (_t _q_method = &MyLabel::mouseRelease; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *MyLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyLabel.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int MyLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MyLabel::mousePress()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MyLabel::paint()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MyLabel::mouseMove()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MyLabel::mouseRelease()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
