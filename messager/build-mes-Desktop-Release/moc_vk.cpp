/****************************************************************************
** Meta object code from reading C++ file 'vk.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mes/vk.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vk.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Vk_t {
    QByteArrayData data[15];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Vk_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Vk_t qt_meta_stringdata_Vk = {
    {
QT_MOC_LITERAL(0, 0, 2), // "Vk"
QT_MOC_LITERAL(1, 3, 8), // "onReturn"
QT_MOC_LITERAL(2, 12, 0), // ""
QT_MOC_LITERAL(3, 13, 3), // "run"
QT_MOC_LITERAL(4, 17, 1), // "c"
QT_MOC_LITERAL(5, 19, 6), // "unread"
QT_MOC_LITERAL(6, 26, 19), // "onItemDoubleClicked"
QT_MOC_LITERAL(7, 46, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(8, 63, 4), // "item"
QT_MOC_LITERAL(9, 68, 13), // "keyPressEvent"
QT_MOC_LITERAL(10, 82, 10), // "QKeyEvent*"
QT_MOC_LITERAL(11, 93, 5), // "event"
QT_MOC_LITERAL(12, 99, 11), // "changeEvent"
QT_MOC_LITERAL(13, 111, 7), // "QEvent*"
QT_MOC_LITERAL(14, 119, 1) // "e"

    },
    "Vk\0onReturn\0\0run\0c\0unread\0onItemDoubleClicked\0"
    "QListWidgetItem*\0item\0keyPressEvent\0"
    "QKeyEvent*\0event\0changeEvent\0QEvent*\0"
    "e"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Vk[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    1,   45,    2, 0x0a /* Public */,
       5,    0,   48,    2, 0x0a /* Public */,
       6,    1,   49,    2, 0x0a /* Public */,
       9,    1,   52,    2, 0x0a /* Public */,
      12,    1,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

void Vk::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Vk *_t = static_cast<Vk *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onReturn(); break;
        case 1: _t->run((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->unread(); break;
        case 3: _t->onItemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 5: _t->changeEvent((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Vk::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Vk.data,
      qt_meta_data_Vk,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Vk::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Vk::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Vk.stringdata0))
        return static_cast<void*>(const_cast< Vk*>(this));
    return QDialog::qt_metacast(_clname);
}

int Vk::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
