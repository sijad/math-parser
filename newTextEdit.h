#include <QtGui>

class TextEdit;

class TextEdit : public QTextEdit {
    Q_PROPERTY(QString placeholderText READ placeholderText WRITE setPlaceholderText)
public:
    TextEdit(QWidget *parent=0) : QTextEdit(parent) {}
    void setPlaceholderText(QString text);
    QString getPlaceholderText();
protected:
    void focusInEvent(QFocusEvent *e);
    void focusOutEvent(QFocusEvent *e);
private:
    QString placeholderText;
};
