/*
 * udprelay.h - the header file of UdpRelay class
 *
 * Copyright (C) 2014, Symeon Huang <hzwhuang@gmail.com>
 *
 * This file is part of the libQtShadowsocks.
 *
 * libQtShadowsocks is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * libQtShadowsocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pdnsd; see the file COPYING. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef UDPRELAY_H
#define UDPRELAY_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QMap>
#include "encryptor.h"
#include "common.h"

using namespace QSS;

namespace QSS {

class UdpRelay : public QObject
{
    Q_OBJECT
public:
    explicit UdpRelay(bool is_local = true, QObject *parent = 0);

signals:
    void info(const QString &);
    void error(const QString &);

private:
    const bool isLocal;
    QUdpSocket *listen;
    QUdpSocket *remote;
    Encryptor *encryptor;

    static QMap<CacheKey, QUdpSocket *> cache;
    static QMap<qintptr, Address> clientDescriptorToServerAddr;
    static const qint64 RecvSize = 65536;//64KB, same as shadowsocks-python (udprelay)

private slots:
    void onSocketError();
    void onListenStateChanged(QAbstractSocket::SocketState);
    void onServerUdpSocketReadyRead();
    void onClientUdpSocketReadyRead();
    void onClientDisconnected();
};

}

#endif // UDPRELAY_H
