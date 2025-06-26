#include <QMainWindow>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_installFinished(int exitCode);

private:
    Ui::MainWindow *ui;
    QProcess *installProcess;
    QString currentPackageManager;
    QString currentPackageTypeFilter;
};
