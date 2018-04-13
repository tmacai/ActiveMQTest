/****************************************************************************
** Meta object code from reading C++ file 'ActiveMQConsumer.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ActiveMQConsumer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ActiveMQConsumer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CActiveMQConsumer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   19,   18,   18, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CActiveMQConsumer[] = {
    "CActiveMQConsumer\0\0strNewMsg\0"
    "sigNewMessage(QString)\0"
};

void CActiveMQConsumer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CActiveMQConsumer *_t = static_cast<CActiveMQConsumer *>(_o);
        switch (_id) {
        case 0: _t->sigNewMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CActiveMQConsumer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CActiveMQConsumer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CActiveMQConsumer,
      qt_meta_data_CActiveMQConsumer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CActiveMQConsumer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CActiveMQConsumer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CActiveMQConsumer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CActiveMQConsumer))
        return static_cast<void*>(const_cast< CActiveMQConsumer*>(this));
    if (!strcmp(_clname, "MessageListener"))
        return static_cast< MessageListener*>(const_cast< CActiveMQConsumer*>(this));
    if (!strcmp(_clname, "Runnable"))
        return static_cast< Runnable*>(const_cast< CActiveMQConsumer*>(this));
    if (!strcmp(_clname, "ExceptionListener"))
        return static_cast< ExceptionListener*>(const_cast< CActiveMQConsumer*>(this));
    return QObject::qt_metacast(_clname);
}

int CActiveMQConsumer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void CActiveMQConsumer::sigNewMessage(const QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
