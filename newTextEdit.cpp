#include "newTextEdit.h"

void TextEdit::setPlaceholderText(QString text) {
    placeholderText=text;
    if(toPlainText().isEmpty())
        setHtml(QString("<font color=\"#808080\"><i>%1</i></font>").arg(placeholderText));
}

QString TextEdit::getPlaceholderText() {
    return placeholderText;
}

void TextEdit::focusInEvent(QFocusEvent *e) {
  if (!placeholderText.isNull()) {
      QString t=toPlainText();
      if (t.isEmpty() || t==placeholderText) clear();
  }
  QTextEdit::focusInEvent(e);
}

void TextEdit::focusOutEvent(QFocusEvent *e) {
  if (!placeholderText.isNull()) {
      if (toPlainText().isEmpty())
          setHtml(QString("<font color=\"#808080\"><i>%1</i></font>").arg(placeholderText));
  }
  QTextEdit::focusOutEvent(e);
}
