#include "mainmenu.h"

MainMenu::MainMenu(QWidget *widget)
	: QMenu(widget)
{
	this->createActions();
	this->translateActions();
	this->setObjectName("menu");
}

void MainMenu::createActions()
{
	//创建菜单项
	action_setting = new QAction(this);
	action_check_update = new QAction(this);
	action_help_online = new QAction(this);
	action_about_us = new QAction(this);

	//添加菜单项
	this->addAction(action_setting);
	this->addAction(action_check_update);

	this->addSeparator();
	this->addAction(action_help_online);
	this->addAction(action_about_us);

	//设置信号连接
	connect(action_setting, SIGNAL(triggered()), this, SIGNAL(showSettingDialog()));
	connect(action_about_us, SIGNAL(triggered()), this, SIGNAL(showAboutUs()));
}

void MainMenu::translateActions()
{
	action_setting->setText(tr("setting"));
	action_check_update->setText(tr("check update"));
	action_help_online->setText(tr("help online"));
	action_about_us->setText(tr("about us"));
}
