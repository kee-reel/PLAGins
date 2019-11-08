#ifndef MENUITEM_H
#define MENUITEM_H

#include <QPushButton>
#include <QResizeEvent>

class UniquePushButton : public QPushButton
{
	Q_OBJECT
public:
	explicit UniquePushButton(uid_t id, QString name, QWidget *parent = nullptr);

	uid_t getId();

private:
	uid_t m_id;

signals:
	void OnMenuItemSelected(UniquePushButton *);

protected:
	void mouseReleaseEvent(QMouseEvent *event) override;
	//    void resizeEvent(QResizeEvent *event) override;
};

#endif // MENUITEM_H
