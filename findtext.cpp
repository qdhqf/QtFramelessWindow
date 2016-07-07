/* ============================================================
* QuiteRSS is a open-source cross-platform RSS/Atom news feeds reader
* Copyright (C) 2011-2016 QuiteRSS Team <quiterssteam@gmail.com>
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
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
* ============================================================ */
#include "findtext.h"

FindTextContent::FindTextContent(QWidget *parent)
  : QLineEdit(parent)
{
  findInSitesAct = new QAction(this);
  findInSitesAct->setObjectName("findInNewsAct");
  findInSitesAct->setIcon(QIcon(":/image/find/FindContent.png"));
  findInSitesAct->setText(QStringLiteral("Find in Sites"));
  findInSitesAct->setCheckable(true);
  findInSitesAct->setChecked(true);

  findInNetworksAct = new QAction(this);
  findInNetworksAct->setObjectName("findTitleAct");
  findInNetworksAct->setIcon(QIcon(":/image/find/FindContent.png"));
  findInNetworksAct->setText(QStringLiteral("Find in Networks"));
  findInNetworksAct->setCheckable(true);

  findInPlanAct = new QAction(this);
  findInPlanAct->setObjectName("findAuthorAct");
  findInPlanAct->setIcon(QIcon(":/image/find/FindContent.png"));
  findInPlanAct->setText(QStringLiteral("Find in Network Plan"));
  findInPlanAct->setCheckable(true);

  findInCircuitAct = new QAction(this);
  findInCircuitAct->setObjectName("findCategoryAct");
  findInCircuitAct->setIcon(QIcon(":/image/find/FindContent.png"));
  findInCircuitAct->setText(QStringLiteral("Find in Circuit Table"));
  findInCircuitAct->setCheckable(true);


  findGroup_ = new QActionGroup(this);
  findGroup_->setExclusive(true);
  findGroup_->addAction(findInSitesAct);
  findGroup_->addAction(findInNetworksAct);
  findGroup_->addAction(findInPlanAct);
  findGroup_->addAction(findInCircuitAct);


  findMenu_ = new QMenu(this);
  findMenu_->addActions(findGroup_->actions());
  findMenu_->insertSeparator(findInNetworksAct);
  findMenu_->insertSeparator(findInCircuitAct);

  findButton_ = new QToolButton(this);
  findButton_->setFocusPolicy(Qt::NoFocus);
  QPixmap findPixmap(":/image/find/selectFind.png");
  findButton_->setIcon(QIcon(findPixmap));
  findButton_->setIconSize(findPixmap.size());
  findButton_->setCursor(Qt::ArrowCursor);
  findButton_->setStyleSheet("QToolButton { border: none; padding: 0px; }");

  connect(findButton_, SIGNAL(clicked()), this, SLOT(slotMenuFind()));
  connect(findGroup_, SIGNAL(triggered(QAction*)),
          this, SLOT(slotSelectFind(QAction*)));

  clearButton_ = new QToolButton(this);
  clearButton_->setFocusPolicy(Qt::NoFocus);
  QPixmap pixmap(":/image/find/ClearFind.png");
  clearButton_->setIcon(QIcon(pixmap));
  clearButton_->setIconSize(pixmap.size());
  clearButton_->setCursor(Qt::ArrowCursor);
  clearButton_->setStyleSheet("QToolButton { border: none; padding: 0px; }");
  clearButton_->hide();
  connect(clearButton_, SIGNAL(clicked()), this, SLOT(slotClear()));
  connect(this, SIGNAL(textChanged(const QString&)),
          SLOT(updateClearButton(const QString&)));

  findLabel_ = new QLabel(QStringLiteral("Find site or subnetwork here"), this);
  findLabel_->setStyleSheet("QLabel { color: gray; }");

  int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
  setStyleSheet(QString("QLineEdit { padding-right: %1px; padding-left: %2px; }").
                arg(clearButton_->sizeHint().width() + frameWidth + 1).
                arg(findButton_->sizeHint().width() + frameWidth + 1));
  QSize msz = minimumSizeHint();
  setMinimumSize(
        qMax(msz.width(), clearButton_->sizeHint().height() + findButton_->sizeHint().height() + frameWidth * 2 + 2),
        qMax(msz.height(), clearButton_->sizeHint().height() + frameWidth * 2 + 2));
}

void FindTextContent::retranslateStrings()
{





  findLabel_->setText(findGroup_->checkedAction()->text());
  if (findLabel_->isVisible()) {
    findLabel_->hide();
    findLabel_->show();
  }
}

void FindTextContent::resizeEvent(QResizeEvent *)
{
  int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
  QSize sz = findButton_->sizeHint();
  findButton_->move(frameWidth+3,
                   (rect().bottom() + 1 - sz.height())/2);
  sz = findLabel_->sizeHint();
  findLabel_->move(frameWidth+findButton_->sizeHint().width()+5,
                   (rect().bottom() + 1 - sz.height())/2);
  sz = clearButton_->sizeHint();
    clearButton_->move(rect().right() - frameWidth - sz.width(),
                      (rect().bottom() + 1 - sz.height())/2);
}

void FindTextContent::focusInEvent(QFocusEvent *event)
{
  findLabel_->setVisible(false);
  QLineEdit::focusInEvent(event);
}

void FindTextContent::focusOutEvent(QFocusEvent *event)
{
  if (text().isEmpty())
    findLabel_->setVisible(true);
  QLineEdit::focusOutEvent(event);
}

void FindTextContent::updateClearButton(const QString& text)
{
  clearButton_->setVisible(!text.isEmpty());
  if (!hasFocus())
    findLabel_->setVisible(true);
}

void FindTextContent::slotClear()
{
  clear();
  emit signalClear();
}

void FindTextContent::slotMenuFind()
{
  findMenu_->popup(mapToGlobal(QPoint(0, height()-1)));
}

void FindTextContent::slotSelectFind(QAction *act)
{
  if (act->objectName() == "findInBrowserAct") {
    findButton_->setIcon(QIcon(":/image/find/ArrowFind.png"));
  } else {
    findButton_->setIcon(QIcon(":/image/find/selectFind.png"));
  }
  findLabel_->setText(act->text());
  emit signalSelectFind();
}
