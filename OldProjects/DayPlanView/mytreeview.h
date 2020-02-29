#pragma once


#include <QDebug>
#include <QTreeView>
#include <QScroller>
#include <QDropEvent>
#include <QMouseEvent>
#include <QDragMoveEvent>
#include <QTapAndHoldGesture>

class MyTreeView : public QTreeView
{
public:
    MyTreeView(QWidget *parent);
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void OnTreeViewItemCheck(const QModelIndex &index);
};

