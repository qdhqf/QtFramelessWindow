/**
	主菜单：包括关于我们、新版特性等
	作者：╰☆奋斗ing❤孩子`
	博客地址：http://blog.sina.com.cn/liang19890820
	QQ：550755606
	Qt分享、交流群：26197884

	注：请尊重原作者劳动成果，仅供学习使用，请勿盗用，违者必究！
*/

#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMenu>


class MainMenu : public QMenu
{
	Q_OBJECT

public:

	explicit MainMenu(QWidget *parent = 0);
	void translateActions();

signals:

	void showSettingDialog();
	void showNewCharacter();
	void showAboutUs();


private:
	
	void createActions();

private:

	QAction *action_setting; //设置
	QAction *action_check_update; //检查更新
	QAction *action_help_online; //在线帮助
	QAction *action_about_us; //关于我们

};

#endif //MAINMENU_H
