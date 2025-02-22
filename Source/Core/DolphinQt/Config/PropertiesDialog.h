// Copyright 2016 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QDialog>

namespace UICommon
{
class GameFile;
}

class PropertiesDialog final : public QDialog
{
  Q_OBJECT
public:
  explicit PropertiesDialog(QWidget* parent, const UICommon::GameFile& game);

signals:
  void OpenGeneralSettings();
  void OpenGraphicsSettings();
};

class GeckoDialog final : public QDialog
{
  Q_OBJECT
public:
  explicit GeckoDialog(QWidget* parent);

signals:
  void OpenGeneralSettings();
};
