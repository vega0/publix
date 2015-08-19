#ifndef DEFINES_H
#define DEFINES_H
/**
* Файл препроцессора, определение констант и другое.
*
* Препроцессорное слияние строк
*   STRINGIZE(PPCAT(HOST, FILE))
*
* Препроцессорное хеширование строк
*   HASH(s)
*/
/* Включить дебаг для некоторых участков кода */
#define DEBUG QT_DEBUG

/* Включить позиционное хеширование файлов */
//#define HASH_P

/* Версия лаунчера */
//#define APP_VERSION 0.12


/* Директория клиента */
#define L_DIR "minecraft-client"
#define APP_LAUNCHER_LOCK

#define PPCAT_NX(A, B) A ## B
#define PPCAT(A, B) PPCAT_NX(A, B)
#define STRINGIZE_NX(A) #A
#define STRINGIZE(A) STRINGIZE_NX(A)
#define __abv(A) A
#define PLACE(A) __abv(A)

#include "HASH.h" //CompileTime хеширование строк.

#ifdef Q_OS_WIN
#define CURRENT_OS "windows"
#endif
#ifdef Q_OS_LINUX
#define CURRENT_OS "linux"
#endif
#ifdef Q_OS_OSX
#define CURRENT_OS "osx"
#endif

#ifdef QT_DEBUG
#include <QtCore/QtDebug>
#include <QDebug>
#include <QTime>

#define __mark_t( MOD ) QTime __dbg_t ## MOD ## _ex; \
    __dbg_t ## MOD ## _ex.start();

#define __mark( MOD, MSG) __DEBUG_P(MSG) \
    __mark_t( MOD )

#define __DEBUG(A, B) qDebug() << PLACE(A) << B;
#define __DEBUG_P(B) qDebug() << PLACE(__CLASS__) << B;

#define __elapsed(MOD, A) __DEBUG_P(A << "-" << __dbg_t ## MOD ## _ex.elapsed() << "millisecond(-s).");

#define ELSE_DEBUG_P(A) else {\
    __DEBUG_P(A) \
    }

#define __debug_p(A) __DEBUG_P(A)

#define __error_p(A) \
    qDebug() << "ERROR" << PLACE(__CLASS__) << A;

#else

// Определяем константы как пустые.
#   define __mark( MOD, MSG )
#   define __DEBUG(A, B)
#   define __DEBUG_P(B)

#   define __elapsed( MOD, A )
#   define ELSE_DEBUG_P(A)
#   define __mark_t( MOD )
#   define __debug_p(A)
#   define __error_p(A)
#endif

#ifdef QT_DEBUG
#   define DE else {
#   define DEC }
#else
#   define DE
#   define DEC
#endif

#define RUN_ONCE(MOD, BODY) static bool __dbg_b_ ## MOD = false;\
    if(!__dbg_b_ ## MOD) \
    { \
    __dbg_b_ ## MOD = true; \
    BODY; \
    }

#define TEST_VAL1 "Testval1"

#endif //DEFINES_H
