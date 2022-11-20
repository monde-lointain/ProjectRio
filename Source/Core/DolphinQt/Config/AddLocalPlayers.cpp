// Copyright 2018 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "DolphinQt/Config/AddLocalPlayers.h"
#include "Core/LocalPlayersConfig.h"

#include <QDialogButtonBox>
#include <QFontDatabase>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QStringList>
#include <QTextEdit>
#include <QPushButton>

//#include "Core/LocalPlayersConfig.h"

#include "DolphinQt/QtUtils/ModalMessageBox.h"
#include <qdesktopservices.h>

AddLocalPlayersEditor::AddLocalPlayersEditor(QWidget* parent) : QDialog(parent)
{
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
  setWindowTitle(tr("Add Local Players"));

  CreateWidgets();
  ConnectWidgets();
}

void AddLocalPlayersEditor::SetPlayer(LocalPlayers::LocalPlayers::Player* name)
{
  m_username_edit->setText(QString::fromStdString(name->username));
  m_userid_edit->setText(QString::fromStdString(name->userid));

  m_local_player = name;
}

void AddLocalPlayersEditor::CreateWidgets()
{
  m_username_edit = new QLineEdit;
  m_userid_edit = new QLineEdit;
  m_description = new QLabel(
      tr("\nEnter a Username.\n\n"
        "NOTE: the player at port 1 will\nbe used over NetPlay."));

  m_description = new QLabel(
      tr("\nEnter the Username and User ID EXACTLY as they appear on projectrio.online\n"
         "and/or from your email. This is necessary to send stat files to our database\n"
         "properly. If you enter an invalid Username and/or User ID, your stats will\n"
         "not be saved to the database.\n\n"
         "If you do not have an account, you can create one below."));

  m_create_account = new QPushButton(tr("Create Account"));

  m_button_box = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Save);


  QGridLayout* grid_layout = new QGridLayout;

  grid_layout->addWidget(new QLabel(tr("Username:")), 0, 0);
  grid_layout->addWidget(m_username_edit, 0, 1);
  grid_layout->addWidget(new QLabel(tr("User ID:")), 1, 0);
  grid_layout->addWidget(m_userid_edit, 1, 1);
  grid_layout->addWidget(m_description, 2, 0, 1, -1);
  grid_layout->addWidget(m_create_account, 3, 0);
  grid_layout->addWidget(m_button_box, 3, 1);

  QFont monospace(QFontDatabase::systemFont(QFontDatabase::FixedFont).family());

  m_userid_edit->setFont(monospace);

  setLayout(grid_layout);
}

void AddLocalPlayersEditor::ConnectWidgets()
{
  connect(m_button_box, &QDialogButtonBox::accepted, this, &AddLocalPlayersEditor::accept);
  connect(m_button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);
  connect(m_create_account, &QPushButton::clicked, this, &AddLocalPlayersEditor::CreateAccount);
}

void AddLocalPlayersEditor::CreateAccount()
{
  QString url = QStringLiteral("https://api.projectrio.app/signup/");
  QDesktopServices::openUrl(QUrl(url));
}

bool AddLocalPlayersEditor::AcceptPlayer()
{
  m_local_player->username = m_username_edit->text().toStdString();

  if (m_local_player->username.empty())
  {
    ModalMessageBox::critical(this, tr("Error"),
                              tr("You must enter a username"));
    return false;
  }

  // checks if the username is too long
  if (22 <= m_local_player->username.length())
  {
    ModalMessageBox::critical(this, tr("Error"), tr("Username is too long."));
    return false;
  }

  // checks if the username has spaces
  for (int i = 0; i < m_local_player->username.length(); i++)
  {
    if (isspace(m_local_player->username[i]))
    {
      ModalMessageBox::critical(this, tr("Error"), tr("Username cannot have spaces."));
      return false;
    }
  }

  // checks if the username starts with "+"
  if (m_local_player->username.rfind("+", 0) == 0)
  {
    ModalMessageBox::critical(this, tr("Error"), tr("Username cannot begin with \"+\"."));
    return false;
  }
  m_local_player->userid = m_userid_edit->text().toStdString();

  if (m_local_player->userid.empty())
  {
    ModalMessageBox::critical(this, tr("Error"), tr("You must enter a User ID"));
    return false;
  }
  
  
  std::string url = "https://api.projectrio.app/validate_user_from_client/?username=" 
                  + m_local_player->username
                  + "&rio_key=" + m_local_player->userid;
  const Common::HttpRequest::Response response = m_http.Get(url);
  if (!response){
    //TODO Error if user is not validated when full beta releases
    //ModalMessageBox::critical(this, tr("Error"), tr("Username and Rio Key could not be validated"));
    //return false;

    ModalMessageBox::warning(this, tr("Warning"), tr("Username and Rio Key could not be validated.\n"
                                                     "If you are part of the beta please double check your\n"
                                                     "info otherwise please ignore and continue"));
  }
  return true;
}

void AddLocalPlayersEditor::accept()
{
  bool success = AcceptPlayer();

  if (success)
    QDialog::accept();
}
