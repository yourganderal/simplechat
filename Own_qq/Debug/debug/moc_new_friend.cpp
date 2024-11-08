/****************************************************************************
** Meta object code from reading C++ file 'new_friend.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../new_friend.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'new_friend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_New_friend_t {
    QByteArrayData data[9];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_New_friend_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_New_friend_t qt_meta_stringdata_New_friend = {
    {
QT_MOC_LITERAL(0, 0, 10), // "New_friend"
QT_MOC_LITERAL(1, 11, 9), // "slot_read"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 9), // "slot_send"
QT_MOC_LITERAL(4, 32, 20), // "on_renew_btn_clicked"
QT_MOC_LITERAL(5, 53, 13), // "addFriendItem"
QT_MOC_LITERAL(6, 67, 7), // "userAid"
QT_MOC_LITERAL(7, 75, 13), // "accept_friend"
QT_MOC_LITERAL(8, 89, 12) // "reject_other"

    },
    "New_friend\0slot_read\0\0slot_send\0"
    "on_renew_btn_clicked\0addFriendItem\0"
    "userAid\0accept_friend\0reject_other"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_New_friend[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    1,   47,    2, 0x08 /* Private */,
       7,    1,   50,    2, 0x08 /* Private */,
       8,    1,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

void New_friend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<New_friend *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_read(); break;
        case 1: _t->slot_send(); break;
        case 2: _t->on_renew_btn_clicked(); break;
        case 3: _t->addFriendItem((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->accept_friend((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->reject_other((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject New_friend::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_New_friend.data,
    qt_meta_data_New_friend,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *New_friend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *New_friend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_New_friend.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int New_friend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
