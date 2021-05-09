#ifndef CLIENT2_H
#define CLIENT2_H

#include <QObject>
#include <klibcore/src/kmacro.h>
#include <src/network/klocalsyncronizer.h>

#include <dlfcn.h>
#include <functional>


#define __invocable(I) \
{ __f ## I(); } void __f ## I()


#define invocable(ARGS...) \
    (ARGS) { [=](){} _f(a0, b0); } void _f(ARGS)


#define MKLABEL2(x) label ## x
#define MKLABEL(x) MKLABEL2(x)
#define ADDR(NAME) MKLABEL(__LINE__): void *NAME = &&MKLABEL(__LINE__);

class Client2 : public QObject
{
    Q_OBJECT
    K_QML_INTERFACE(Client2)
    K_AUTO_PROPERTY(QString, text, text, setText, textChanged, QString())
    K_READONLY_PROPERTY(QString, initialInfo, initialInfo, setInitialInfo, initialInfoChanged, QString())

    KLocalSyncronizer local;
    QMap<int, std::function<void()>> map;
public:
    explicit Client2(QObject *parent = nullptr);

    void a() {
        auto g = [](){

        };
        g();
    }



    template<typename T>
    struct ftype {
        typedef T type;
    };

    template<typename T>
    auto make_ftype(T) {
        return ftype<T>();
    }

    //void foo(int ooo) __invocable(0) {
    //
    //    [=](){
    //
    //    };
    //}
    //
    //void gogadoda invocable(int a0, int b0) {
    //
    //
    //}


signals:

};

#endif // CLIENT2_H
