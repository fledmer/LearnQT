#ifndef MYHIGHLIGHTER_H
#define MYHIGHLIGHTER_H

#endif // MYHIGHLIGHTER_H
#include <QSyntaxHighlighter>

class MyHighLighter: public QSyntaxHighlighter
{
    Q_OBJECT;

    QTextCharFormat myClassFormat;

public:
    MyHighLighter(QTextDocument *parent):QSyntaxHighlighter(parent){
        myClassFormat.setFontWeight(QFont::Bold);
        myClassFormat.setForeground(Qt::red);
    }
protected:
    virtual void highlightBlock(const QString& str){
        for(int i = 0;i<str.length();i++){
            if(str.at(i).isDigit()){
                setFormat(i,1,myClassFormat);
            }
        }
    }
};
