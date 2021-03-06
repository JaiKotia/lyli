/*
 * This file is part of Lyli-Qt, a GUI to control Lytro camera
 * Copyright (C) 2015  Lukas Jirkovsky <l.jirkovsky @at@ gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "imagelistmodel.h"

#include <filesystem/filesystemaccess.h>
#include <filesystem/photo.h>
#include <filesystem/photoptr.h>

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QHash>
#include <QUrl>
#include <QVariant>

#include <algorithm>
#include <fstream>

#include "context.h"

ImageListModel::ImageListModel(Context* context, QObject *parent) : QAbstractListModel(parent), m_context(context) {

}

ImageListModel::~ImageListModel() {

}

QVariant ImageListModel::data(const QModelIndex& index, int role) const {
	if (! index.isValid() || static_cast<ModelFileList::size_type>(index.row()) >= m_fileList.size()) {
		return QVariant();
	}

	if (role == Qt::DisplayRole) {
		return QVariant::fromValue(m_fileList[index.row()]);
	}

	return QVariant();
}

int ImageListModel::rowCount(const QModelIndex& parent) const {
	Q_UNUSED(parent);
	return m_fileList.size();
}

void ImageListModel::onCameraChanged(Lyli::Camera* camera) {
	beginResetModel();

	m_fileList.clear();

	if (camera != nullptr) {
		Lyli::Filesystem::PhotoList fileList = std::move(camera->getFilesystemAccess().getPictureList());
		m_fileList.reserve(fileList.size());
		for (auto entry : fileList) {
			m_fileList.push_back(ImageListItem(camera, entry));
		}
	}

	endResetModel();
}

void ImageListModel::downloadFile(const QModelIndex &index, const QString &outputDirectory) {
	QString outputFile;
	QString outputFilePath;
	std::ofstream ofs;
	Lyli::Filesystem::PhotoPtr file(m_fileList[index.row()].getPhoto());

	QDateTime datetime = m_fileList[index.row()].getTime();
	QString outputFileBase =  outputDirectory + QDir::separator() + datetime.toString("yyyy-MM-dd_HH:mm:ss");

	qDebug() << "downloading file " << outputFileBase;

	outputFilePath = outputFileBase + ".TXT";
	ofs.open(outputFilePath.toLocal8Bit().data(), std::ofstream::out | std::ofstream::binary);
	file->getImageMetadata(ofs);
	ofs.flush();
	ofs.close();

	outputFilePath = outputFileBase + ".RAW";
	ofs.open(outputFilePath.toLocal8Bit().data(), std::ofstream::out | std::ofstream::binary);
	file->getImageData(ofs);
	ofs.flush();
	ofs.close();
}
