/****************************************************************************
** Meta object code from reading C++ file 'vk.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mes/vk.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vk.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Vk_t {
    QByteArrayData data[8];
    char stringdata[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Vk_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Vk_t qt_meta_stringdata_Vk = {
    {
QT_MOC_LITERAL(0, 0, 2),
QT_MOC_LITERAL(1, 3, 8),
QT_MOC_LITERAL(2, 12, 0),
QT_MOC_LITERAL(3, 13, 3),
QT_MOC_LITERAL(4, 17, 6),
QT_MOC_LITERAL(5, 24, 19),
QT_MOC_LITERAL(6, 44, 16),
QT_MOC_LITERAL(7, 61, 4)
    },
    "Vk\0onReturn\0\0run\0unread\0onItemDoubleClicked\0"
    "QListWidgetItem*\0item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Vk[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    1,   37,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void Vk::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Vk *_t = static_cast<Vk *>(_o);
        switch (_id) {
        case 0: _t->onReturn(); break;
        case 1: _t->run(); break;
        case 2: _t->unread(); break;
        case 3: _t->onItemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Vk::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Vk.data,
      qt_meta_data_Vk,  qt_static_metacall, 0, 0}
};


const QMetaObject *Vk::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Vk::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Vk.stringdata))
        return static_cast<void*>(const_cast< Vk*>(this));
    return QDialog::qt_metacast(_clname);
}

int Vk::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
