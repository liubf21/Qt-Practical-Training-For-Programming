/****************************************************************************
** Meta object code from reading C++ file 'player.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../VideoEdit/player.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'player.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VideoPlayer_t {
    QByteArrayData data[18];
    char stringdata0[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoPlayer_t qt_meta_stringdata_VideoPlayer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "VideoPlayer"
QT_MOC_LITERAL(1, 12, 8), // "openFile"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 4), // "play"
QT_MOC_LITERAL(4, 27, 4), // "jump"
QT_MOC_LITERAL(5, 32, 11), // "QModelIndex"
QT_MOC_LITERAL(6, 44, 5), // "index"
QT_MOC_LITERAL(7, 50, 23), // "playlistPositionChanged"
QT_MOC_LITERAL(8, 74, 11), // "currentItem"
QT_MOC_LITERAL(9, 86, 17), // "mediaStateChanged"
QT_MOC_LITERAL(10, 104, 19), // "QMediaPlayer::State"
QT_MOC_LITERAL(11, 124, 5), // "state"
QT_MOC_LITERAL(12, 130, 15), // "positionChanged"
QT_MOC_LITERAL(13, 146, 8), // "position"
QT_MOC_LITERAL(14, 155, 15), // "durationChanged"
QT_MOC_LITERAL(15, 171, 8), // "duration"
QT_MOC_LITERAL(16, 180, 11), // "setPosition"
QT_MOC_LITERAL(17, 192, 11) // "handleError"

    },
    "VideoPlayer\0openFile\0\0play\0jump\0"
    "QModelIndex\0index\0playlistPositionChanged\0"
    "currentItem\0mediaStateChanged\0"
    "QMediaPlayer::State\0state\0positionChanged\0"
    "position\0durationChanged\0duration\0"
    "setPosition\0handleError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoPlayer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    1,   61,    2, 0x0a /* Public */,
       7,    1,   64,    2, 0x0a /* Public */,
       9,    1,   67,    2, 0x08 /* Private */,
      12,    1,   70,    2, 0x08 /* Private */,
      14,    1,   73,    2, 0x08 /* Private */,
      16,    1,   76,    2, 0x08 /* Private */,
      17,    0,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::LongLong,   13,
    QMetaType::Void, QMetaType::LongLong,   15,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,

       0        // eod
};

void VideoPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VideoPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openFile(); break;
        case 1: _t->play(); break;
        case 2: _t->jump((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->playlistPositionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->mediaStateChanged((*reinterpret_cast< QMediaPlayer::State(*)>(_a[1]))); break;
        case 5: _t->positionChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 6: _t->durationChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 7: _t->setPosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->handleError(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaPlayer::State >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VideoPlayer::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_VideoPlayer.data,
    qt_meta_data_VideoPlayer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VideoPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VideoPlayer.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int VideoPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
