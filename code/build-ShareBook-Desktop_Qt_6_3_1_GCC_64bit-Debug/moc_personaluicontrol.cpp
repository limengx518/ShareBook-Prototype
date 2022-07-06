/****************************************************************************
** Meta object code from reading C++ file 'personaluicontrol.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../ShareBook/personaluicontrol.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'personaluicontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PersonalUIControl_t {
    const uint offsetsAndSize[22];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_PersonalUIControl_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_PersonalUIControl_t qt_meta_stringdata_PersonalUIControl = {
    {
QT_MOC_LITERAL(0, 17), // "PersonalUIControl"
QT_MOC_LITERAL(18, 16), // "netizenIdChanged"
QT_MOC_LITERAL(35, 0), // ""
QT_MOC_LITERAL(36, 2), // "id"
QT_MOC_LITERAL(39, 11), // "signChanged"
QT_MOC_LITERAL(51, 4), // "sign"
QT_MOC_LITERAL(56, 18), // "netizenInfoChanged"
QT_MOC_LITERAL(75, 8), // "jottings"
QT_MOC_LITERAL(84, 8), // "initData"
QT_MOC_LITERAL(93, 9), // "netizenId"
QT_MOC_LITERAL(103, 11) // "netizenInfo"

    },
    "PersonalUIControl\0netizenIdChanged\0\0"
    "id\0signChanged\0sign\0netizenInfoChanged\0"
    "jottings\0initData\0netizenId\0netizenInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PersonalUIControl[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       3,   48, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    4 /* Public */,
       4,    1,   41,    2, 0x06,    6 /* Public */,
       6,    1,   44,    2, 0x06,    8 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       8,    0,   47,    2, 0x02,   10 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,

 // methods: parameters
    QMetaType::Void,

 // properties: name, type, flags
       9, QMetaType::QString, 0x00015103, uint(0), 0,
       5, QMetaType::QString, 0x00015103, uint(1), 0,
      10, QMetaType::QString, 0x00015103, uint(2), 0,

       0        // eod
};

void PersonalUIControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PersonalUIControl *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->netizenIdChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->signChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->netizenInfoChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->initData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PersonalUIControl::*)(const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PersonalUIControl::netizenIdChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PersonalUIControl::*)(const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PersonalUIControl::signChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PersonalUIControl::*)(const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PersonalUIControl::netizenInfoChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PersonalUIControl *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getNetizenId(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->getSign(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->getNetizenInfo(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<PersonalUIControl *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setNetizenId(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setSign(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setNetizenInfo(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject PersonalUIControl::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_PersonalUIControl.offsetsAndSize,
    qt_meta_data_PersonalUIControl,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_PersonalUIControl_t
, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<PersonalUIControl, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString, std::false_type>

, QtPrivate::TypeAndForceComplete<void, std::false_type>

>,
    nullptr
} };


const QMetaObject *PersonalUIControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PersonalUIControl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PersonalUIControl.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PersonalUIControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void PersonalUIControl::netizenIdChanged(const QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PersonalUIControl::signChanged(const QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PersonalUIControl::netizenInfoChanged(const QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
