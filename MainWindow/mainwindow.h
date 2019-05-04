#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "main.h"
#include "syntacticalanalyzer.h"
#include "reversepolishnotationbuilder.h"
#include "lexicalanalyzer.h"
#include "gorodlangexception.h"
#include <Executor/executor.h>
#include <QMainWindow>
#include <QTimer>
#include <QFuture>
#include <QTextCursor>
#include <QtConcurrent/QtConcurrent>

namespace Ui {
class MainWindow;
}

using namespace Gorod;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

private slots:
    void on_plainTextEdit_textChanged();

    void on_pushButton_clicked();

    void on_actionShow_Tree_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

private:
    static QVariantMap ParseGorodLang(const QString &inputProg);

    void setErrorPosition();

    void setLexerTable(const QString &lexerTable);

    void executeGorodProg() const;

private:
    Ui::MainWindow *ui;

    QTimer timer_;
    QFuture<QVariantMap> *parserResult_;
    int lastErrorPos_, lastErrorLine_;
    QGraphicsScene scene_;
    QGraphicsView view_;

    Executor executor;

    bool isErrorUnderling;
};

#endif // MAINWINDOW_H
