/****************************************************************************
** Meta object code from reading C++ file 'edittimeline.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/edittimeline.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'edittimeline.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EditTimeLine_t {
    QByteArrayData data[10];
    char stringdata0[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditTimeLine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditTimeLine_t qt_meta_stringdata_EditTimeLine = {
    {
QT_MOC_LITERAL(0, 0, 12), // "EditTimeLine"
QT_MOC_LITERAL(1, 13, 9), // "playClips"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 6), // "addUrl"
QT_MOC_LITERAL(4, 31, 3), // "add"
QT_MOC_LITERAL(5, 35, 3), // "url"
QT_MOC_LITERAL(6, 39, 8), // "duration"
QT_MOC_LITERAL(7, 48, 5), // "merge"
QT_MOC_LITERAL(8, 54, 6), // "remove"
QT_MOC_LITERAL(9, 61, 1) // "i"

    },
    "EditTimeLine\0playClips\0\0addUrl\0add\0"
    "url\0duration\0merge\0remove\0i"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditTimeLine[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   45,    2, 0x0a /* Public */,
       7,    0,   50,    2, 0x0a /* Public */,
       8,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QUrl,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QUrl, QMetaType::LongLong,    5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void EditTimeLine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EditTimeLine *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->playClips((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->addUrl((*reinterpret_cast< QUrl(*)>(_a[1]))); break;
        case 2: _t->add((*reinterpret_cast< QUrl(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 3: _t->merge(); break;
        case 4: _t->remove((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EditTimeLine::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EditTimeLine::playClips)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EditTimeLine::*)(QUrl );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EditTimeLine::addUrl)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EditTimeLine::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_EditTimeLine.data,
    qt_meta_data_EditTimeLine,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EditTimeLine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditTimeLine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EditTimeLine.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int EditTimeLine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void EditTimeLine::playClips(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EditTimeLine::addUrl(QUrl _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
