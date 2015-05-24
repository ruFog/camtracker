#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLabel>

#include "helpers/asettingshelper.h"

#include "asettingsdialog.h"

// ========================================================================== //
// Constructor.
// ========================================================================== //
ASettingsDialog::ASettingsDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle(ASettingsDialog::tr("Settings"));

    QLabel *lang_label = new QLabel(this);
    lang_label->setText(ASettingsDialog::tr("Language:"));

    _lang_cbox = new QComboBox(this);
    _lang_cbox->addItem(QStringLiteral("Eng"), QStringLiteral("en"));
    _lang_cbox->addItem(QStringLiteral("Rus"), QStringLiteral("ru"));

    QLabel *user_label = new QLabel(this);
    user_label->setText(ASettingsDialog::tr("Username:"));

    _user_ledit = new QLineEdit(this);

    QLabel *pswd_label = new QLabel(this);
    pswd_label->setText(ASettingsDialog::tr("Password:"));

    _pswd_ledit = new QLineEdit(this);
    _pswd_ledit->setEchoMode(QLineEdit::Password);

    QLabel *duration_label = new QLabel(this);
    duration_label->setText(
        ASettingsDialog::tr("No more in front\nof webcamera:"));

    _duration_spbox = new QSpinBox(this);
    _duration_spbox->setSuffix(ASettingsDialog::tr(" min."));
    _duration_spbox->setRange(1,60);

    _register_label = new QLabel(this);
    _register_label->setOpenExternalLinks(true);

    QPushButton *login_pbut = new QPushButton(this);
    login_pbut->setText(ASettingsDialog::tr("Login"));

    QPushButton *test_pbut = new QPushButton(this);
    test_pbut->setText(ASettingsDialog::tr("Test webcamera"));

    QLabel *statistic_label = new QLabel(this);
    statistic_label->setOpenExternalLinks(true);
    statistic_label->setText(
        ASettingsDialog::tr("Statistic available" \
        " <a href=\"http://google.ru\">at link</a>."));

    QLabel *rss_label = new QLabel(this);
    rss_label->setOpenExternalLinks(true);
    rss_label->setText("RSS...");

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(lang_label, 0, 0, 1, 1);
    layout->addWidget(_lang_cbox, 0, 1, 1, 2);
    layout->addWidget(user_label, 1, 0, 1, 1);
    layout->addWidget(_user_ledit, 1, 1, 1, 2);
    layout->addWidget(pswd_label, 2, 0, 1, 1);
    layout->addWidget(_pswd_ledit, 2, 1, 1, 2);
    layout->addWidget(duration_label, 3, 0, 1, 1);
    layout->addWidget(_duration_spbox, 3, 1, 1, 1);
    layout->addWidget(_register_label, 1, 3, 1, 1);
    layout->addWidget(login_pbut, 2, 3, 1, 1);
    layout->addWidget(test_pbut, 4, 1, 1, 2);
    layout->addWidget(statistic_label, 5, 1, 1, 2);
    layout->addWidget(rss_label, 6, 1, 1, 3);
    layout->setColumnStretch(2,2);

    setLayout(layout);

    QMetaObject::invokeMethod(this, "loadSettings", Qt::QueuedConnection);
}


// ========================================================================== //
// Load settings.
// ========================================================================== //
void ASettingsDialog::loadSettings() {
    _lang_cbox->setCurrentText(
        ASettingsHelper::value(QStringLiteral("language")
            , QStringLiteral("Eng")).toString());

    _user_ledit->setText(
        ASettingsHelper::value(QStringLiteral("username")).toString());
    _pswd_ledit->setText(
        ASettingsHelper::value(QStringLiteral("password")).toString());

    _duration_spbox->setValue(
        ASettingsHelper::value(QStringLiteral("duration"), 30).toInt());

    _register_label->setText(
        QString("<a href=\"%1\">%2</a>")
            .arg(ASettingsHelper::value(QStringLiteral("registration-link"))
                .toString())
            .arg(ASettingsDialog::tr("Register")));
}