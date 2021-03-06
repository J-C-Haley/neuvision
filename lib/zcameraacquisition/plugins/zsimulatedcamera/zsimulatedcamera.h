/* * Z3D - A structured light 3D scanner
 * Copyright (C) 2013-2016 Nicolas Ulrich <nikolaseu@gmail.com>
 *
 * This file is part of Z3D.
 *
 * Z3D is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Z3D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Z3D.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "ZCameraAcquisition/zcamerainterface_p.h"

#include <QCache>
#include <QDir>

namespace Z3D
{

class ZSimulatedCamera : public ZCameraBase
{
    Q_OBJECT

public:
    explicit ZSimulatedCamera(QVariantMap options, QObject *parent = nullptr);
    ~ZSimulatedCamera() override;

signals:

public slots:
    virtual bool startAcquisition() override;
    virtual bool stopAcquisition() override;

    virtual QList<Z3D::ZCameraInterface::ZCameraAttribute> getAllAttributes() override;
    virtual QVariant getAttribute(const QString &name) const override;

    /// this is unique, only for simulated camera
    void loadImageFromFilename(const QString &fileName);

protected slots:
    virtual bool setAttribute(const QString &name, const QVariant &value, bool notify) override;

    void emitNewImage();

private:
    QString m_folder;
    QString m_currentFile;

    QDir m_dir;

    int m_currentImageNumber;

    struct CacheItem {
        ZCameraImagePtr image;
    };

    QCache<QString, CacheItem> m_imageCache;
};

} // namespace Z3D
