#ifndef APPSERVICE_HPP
#define APPSERVICE_HPP

#include "Service.hpp"

class AppService : public Service
{
    Q_OBJECT

public:

    explicit AppService(QString name, QString version);

protected:

};

#endif // APPSERVICE_HPP
