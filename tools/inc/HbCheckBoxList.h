/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBHbCheckBoxList_H
#define HBHbCheckBoxList_H

// Qt
#include <QtCore/QObject>
#include <QtWidgets/QComboBox>
// Hb
#include <HbTools.h>


namespace hb
{
    namespace tools
    {
        class HB_TOOLS_DECL HbCheckBoxList : public QComboBox
        {
            Q_OBJECT

        public:
            HbCheckBoxList(QWidget *parent = 0);
            virtual ~HbCheckBoxList();
            //bool eventFilter(QObject *object, QEvent *event);
            //virtual void paintEvent(QPaintEvent *);
            //void setDisplayText(QString text);
            //QString getDisplayText() const;

        private:

        public slots:
            void onCheckStateChanged();

        signals:
        };
    }
}

#endif // HBHbCheckBoxList_H
