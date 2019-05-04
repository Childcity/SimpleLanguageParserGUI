#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardItemModel>
#include <typeinfo>

static ASTNode::SharedPtr lastAstTree_;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Loading font
    int id = QFontDatabase::addApplicationFont(":/res/RobotoMono-Regular.ttf");
    if(id < 0){
        DEBUGM("Font can't be loaded!");
    }else{
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        QFont font1(family, 10, QFont::Bold);
        setFont(font1);
        font1.setPointSize(11);
        ui->label_2->setFont(font1);
        for(auto &menu : ui->menuBar->children()){
            static_cast<QMenu*>(menu)->setFont(font1);
        }
        QFont font2(family, 11, QFont::Normal);
        ui->plainTextEdit->setFont(font2);
    }

    ui->label->setTextFormat(Qt::RichText);
    parserResult_ = nullptr;
    isErrorUnderling = false;
    view_.setScene(&scene_);
    view_.setRenderHints(QPainter::SmoothPixmapTransform);

    connect(&timer_, &QTimer::timeout, this, [=]{
        if(parserResult_ && parserResult_->isResultReadyAt(0)){

            QVariantMap res = parserResult_->result();
            ui->label->setText(res["message"].toString());
            int errorline = res["line"].toInt();
            if(errorline > 0){
                lastErrorLine_ = errorline;
                lastErrorPos_ = res["pos"].toInt();
            }else{
                lastErrorLine_ = 0;
            }
            setLexerTable(res["lexTable"].toString());
            ui->label_3->setText(res["polish"].toString());
            parserResult_ = nullptr;
            scene_.clear();

            if(lastErrorLine_)
                return ;

            executor.setIsRunning(true);
            executor.exec(lastAstTree_);
        }
    });

    QObject::connect(&executor, &Executor::sigWriteText, this, [this](qint64 number){
        ui->plainTextEdit_2->appendPlainText(QString("%1").arg(number));
    });

    QObject::connect(&executor, &Executor::sigReadText, this, [this](qint64 &number){
        QEventLoop evLoop;
        QString value;

        ui->plainTextEdit_2->appendPlainText("\n");
        int oldPos = ui->plainTextEdit_2->textCursor().position();

        QMetaObject::Connection conn;
        conn = connect(ui->plainTextEdit_2, &QPlainTextEdit::textChanged, this, [&, this]{
            if(! executor.isRunning()){
                disconnect(conn);
                evLoop.quit();
                return;
            }

            QTextCursor c = ui->plainTextEdit_2->textCursor();
            c.setPosition(oldPos, QTextCursor::KeepAnchor);
            value = c.selectedText();
            if(value.contains("\xE2\x80\xA9")){
                value = value.split("\xE2\x80\xA9").first();
                if(! value.isEmpty()){
                    disconnect(conn);
                    evLoop.quit();
                }
            }
        });

        evLoop.exec();

        bool ok;
        number = value.toLongLong(&ok);
        if(! ok && executor.isRunning()){
            executor.setIsRunning(false);
            ui->plainTextEdit_2->appendPlainText("exception: NaN");
        }
    });

    timer_.start(300);
    on_plainTextEdit_textChanged();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_plainTextEdit_textChanged()
{
    if(isErrorUnderling)
        return;

    ui->label->setText("<b>Status:</b> <i>processing...</i>");
    int maxLines = ui->plainTextEdit->toPlainText().split('\n').length();

    QString lines;
    for(int i = 1; i <= maxLines; ++i)
        lines += QString::number(i) + "\n";
    ui->label_2->setText(lines);

    executor.setIsRunning(false);
    ui->plainTextEdit_2->clear();

    parserResult_ = new QFuture<QVariantMap>;
    *parserResult_ = QtConcurrent::run(ParseGorodLang, ui->plainTextEdit->toPlainText());
}

void MainWindow::on_pushButton_clicked()
{
    setErrorPosition();
}

QVariantMap MainWindow::ParseGorodLang(const QString &inputProg){
    QVariantMap result;

    try {
        try {
            const auto lexResult = LexicalAnalyzer::Parse(inputProg);
            //                outputTable <<QJsonDocument::fromVariant(lexResult)
            //                              .toJson(QJsonDocument::JsonFormat::Indented);

            result["lexTable"] = LexicalAnalyzer::GenerateCSVTable(lexResult);

            qDebug()<<"\n";
            DEBUGM("LEXICAL ANALIZE PASSED ( OK )!");
            qDebug()<<"\n";

            lastAstTree_ = SyntacticalAnalyzer::Parse(lexResult);
            ReversePolishNotationBuilder rpnBuilder(lastAstTree_);
            QVariantList rpnLst = rpnBuilder.Generate();
            result["message"] = "<b>Status:</b><br>Lexical analize: <i>OK</i><br>Syntactical analize: <i>OK</i>";
            result["polish"] = rpnLst.at(rpnLst.size()-2).toMap()["polish"].toString();DEBUGM(result["polish"]<<rpnBuilder.toRawJson().data())
        } catch (LexicalException &e) {
            result["isPosWord"] = false;
            throw;
        } catch (SyntacticalException &e){
            result["isPosWord"] = true;
            throw;
        }
    } catch (Gorod::Exception &e) {
        result["message"] = "<b>Status:</b> <i>" + e.what() +"</i>";
        result["line"] = e.getLine();
        result["pos"] = e.getPos();
    }

    return result;
}

void MainWindow::setErrorPosition()
{
    isErrorUnderling = true;

    QTextCharFormat newcharfmt;// = ui->plainTextEdit->currentCharFormat();;
    QTextCursor cursor = ui->plainTextEdit->textCursor();

    //clearing old undeling
    cursor.movePosition( QTextCursor::Start );
    cursor.movePosition( QTextCursor::End, QTextCursor::KeepAnchor);
    ui->plainTextEdit->setTextCursor(cursor);
    newcharfmt.setUnderlineStyle(QTextCharFormat::NoUnderline);
    ui->plainTextEdit->setCurrentCharFormat( newcharfmt );
    ui->plainTextEdit->setTextCursor(cursor);

    if(lastErrorLine_ == 0 ){
        cursor.movePosition( QTextCursor::Start );
        ui->plainTextEdit->setTextCursor(cursor);
        isErrorUnderling = false;
        return;
    }

    cursor.movePosition( QTextCursor::Start );
    cursor.movePosition( QTextCursor::Down, QTextCursor::MoveAnchor, lastErrorLine_ - 1 );
    cursor.movePosition( QTextCursor::StartOfLine );
    cursor.movePosition( QTextCursor::Right, QTextCursor::MoveAnchor, lastErrorPos_ - 1 );
    //cursor.movePosition( QTextCursor::Word, QTextCursor::KeepAnchor);
    cursor.movePosition( QTextCursor::WordRight, QTextCursor::KeepAnchor );
    ui->plainTextEdit->setTextCursor(cursor);



    // = ui->plainTextEdit->currentCharFormat();
    newcharfmt.setUnderlineColor(QColor(Qt::red));
    QFont errorFont(ui->plainTextEdit->font());
    errorFont.setBold(true);
    newcharfmt.setFont(errorFont);
    newcharfmt.setFontPointSize(errorFont.pointSize() + 1);
    newcharfmt.setUnderlineStyle(QTextCharFormat::WaveUnderline);
    ui->plainTextEdit->setCurrentCharFormat( newcharfmt );

    cursor.movePosition( QTextCursor::WordLeft ); // remove selection and set cursor to begining
    ui->plainTextEdit->setTextCursor(cursor);
    ui->plainTextEdit->setFocus();

    lastErrorLine_ = 0;
    isErrorUnderling = false;
}

void MainWindow::setLexerTable(const QString &lexerTable)
{
    QStringList rows = lexerTable.split('\n');

    QStandardItemModel *model = new QStandardItemModel(rows.size(), 4, ui->tableView);
    ui->tableView->setModel(model);

    for(int row=0; row!=model->rowCount(); ++row){
        QStringList cells = rows.at(row).split(';');
        for(int column=0; column < model->columnCount() && column < cells.length(); ++column) {
            QStandardItem *newItem = new QStandardItem(cells.at(column));
            newItem->setTextAlignment(Qt::AlignCenter);
            model->setItem(row, column, newItem);
        }
    }
}

void MainWindow::on_actionShow_Tree_triggered()
{
    ASTNodeWalker::ShowASTTree(lastAstTree_, scene_, view_);
}

void MainWindow::on_actionOpen_triggered()
{
    auto fileDiag = new QFileDialog(this, "Select Gorod program file", QDir::homePath(), "GorodFile (*.gor)");
    fileDiag->setFileMode(QFileDialog::ExistingFile);
    int id = QFontDatabase::addApplicationFont(":/res/RobotoMono-Regular.ttf");
    if(id >= 0){
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        QFont RobotoMono(family, 8, QFont::Normal);
        fileDiag->setFont(RobotoMono);
    }
    if (fileDiag->exec()){
        QFile gorFile(fileDiag->selectedFiles().first());
        gorFile.open(QIODevice::ReadOnly | QIODevice::Text);
        ui->plainTextEdit->setPlainText(gorFile.readAll());
    }
}

void MainWindow::on_actionSave_triggered()
{
    auto fileDiag = new QFileDialog(this, "Select Gorod program file", QDir::homePath(), "GorodFile (*.gor)");
    int id = QFontDatabase::addApplicationFont(":/res/RobotoMono-Regular.ttf");
    if(id >= 0){
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        QFont RobotoMono(family, 8, QFont::Normal);
        fileDiag->setFont(RobotoMono);
    }
    if (fileDiag->exec()){
        QFile gorFile(fileDiag->selectedFiles().first());
        gorFile.open(QIODevice::WriteOnly | QIODevice::Text);
        gorFile.write(ui->plainTextEdit->toPlainText().toUtf8());
    }
}
