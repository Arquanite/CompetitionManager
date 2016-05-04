#include "competitionmanager.h"
#include "ui_competitionmanager.h"
#include <QTime>

CompetitionManager::CompetitionManager(QWidget *parent) : QMainWindow(parent), ui(new Ui::CompetitionManager) {
    ui->setupUi(this);
    qsrand(QTime::currentTime().msecsSinceStartOfDay());

    m_Zawody.GenerujDruzyny(40,5);
    m_Zawody.GenerujSedziow(20);
    m_Zawody.ZaplanujSpotkania();
    m_Zawody.RozegrajMecze();

    qDebug()<<"nadal działa";
    const ListaDruzyn* Druzyny = m_Zawody.Druzyny();
    m_TeamModel = new TeamModel(Druzyny);
    m_TeamProxyModel = new BetterProxyModel;

    m_TeamProxyModel->setSourceModel(m_TeamModel);
    m_TeamProxyModel->setFilterKeyColumn(2);

    ui->widokDruzyn->setModel(m_TeamProxyModel);
    ui->widokDruzyn->resizeColumnsToContents();
    ui->widokDruzyn->horizontalHeader()->setSectionsMovable(true);
    ui->widokDruzyn->sortByColumn(1, Qt::AscendingOrder);

    const ListaSedziow* Sedziowie = m_Zawody.Sedziowie();
    m_JudgeModel = new JudgeModel(Sedziowie);
    m_JudgeProxyModel = new BetterProxyModel;

    m_JudgeProxyModel->setSourceModel(m_JudgeModel);
    m_JudgeProxyModel->setFilterKeyColumn(2);

    ui->widokSedziow->setModel(m_JudgeProxyModel);
    ui->widokSedziow->resizeColumnsToContents();
    ui->widokSedziow->horizontalHeader()->setSectionsMovable(true);
    ui->widokSedziow->sortByColumn(0, Qt::AscendingOrder);

    const ListaSpotkan* Spotkania = m_Zawody.Spotkania();
    m_MatchModel = new MatchModel(Spotkania);
    m_MatchProxyModel = new BetterProxyModel;

    m_MatchProxyModel->setSourceModel(m_MatchModel);
    m_MatchProxyModel->setFilterKeyColumn(3);

    ui->widokSpotkan->setModel(m_MatchProxyModel);
    ui->widokSpotkan->resizeColumnsToContents();
    ui->widokSpotkan->horizontalHeader()->setSectionsMovable(true);
    ui->widokSpotkan->sortByColumn(2, Qt::AscendingOrder);
}

CompetitionManager::~CompetitionManager(){
    delete m_TeamModel;
    delete m_TeamProxyModel;
    delete ui;
}

void CompetitionManager::closeEvent(QCloseEvent *event){
    ExitDialog Dialog("nienazwany", this);
    int x = Dialog.exec();
    switch (x) {
    case -1:
        event->accept();
        break;
    case 0:
        event->ignore();
        break;
    case 1:
        event->accept();
        break;
    }
}

void CompetitionManager::on_Wszystkie_clicked(bool checked){
    QString Filtr = QString();
    if(checked){
        m_TeamProxyModel->setFilterFixedString(Filtr);
        m_JudgeProxyModel->setFilterFixedString(Filtr);
        m_MatchProxyModel->setFilterFixedString(Filtr);
    }
}

void CompetitionManager::on_SiatkowkaPlazowa_clicked(bool checked){
    QString Filtr = "Siatkówka Plażowa";
    if(checked){
        m_TeamProxyModel->setFilterFixedString(Filtr);
        m_JudgeProxyModel->setFilterFixedString(Filtr);
        m_MatchProxyModel->setFilterFixedString(Filtr);
    }
}

void CompetitionManager::on_PrzeciaganieLiny_clicked(bool checked){
    QString Filtr = "Przeciąganie Liny";
    if(checked){
        m_TeamProxyModel->setFilterFixedString(Filtr);
        m_JudgeProxyModel->setFilterFixedString(Filtr);
        m_MatchProxyModel->setFilterFixedString(Filtr);
    }
}

void CompetitionManager::on_DwaOgnie_clicked(bool checked){
    QString Filtr = "Dwa Ognie";
    if(checked){
        m_TeamProxyModel->setFilterFixedString(Filtr);
        m_JudgeProxyModel->setFilterFixedString(Filtr);
        m_MatchProxyModel->setFilterFixedString(Filtr);
    }
}
