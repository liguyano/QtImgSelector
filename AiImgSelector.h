//
// Created by kurum on 2024/8/17.
//

#ifndef IMGSELECTOR_AIIMGSELECTOR_H
#define IMGSELECTOR_AIIMGSELECTOR_H
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QListView>
#include <QStandardItemModel>
#include <QPixmap>
#include <QStandardPaths>
#include <QFileDialog>

class ImageSelectionWidget : public QWidget {
Q_OBJECT

public:
    ImageSelectionWidget(const QStringList& imagePaths, QWidget *parent = nullptr)
            : QWidget(parent), selectedImagePath(""), imagePathList(imagePaths) {
        setupUi();
    }

private slots:
    void onItemClicked(QModelIndex index) {
        QStandardItem *item = model->itemFromIndex(index);
        selectedImagePath = item->data(Qt::UserRole).toString();
        emit imageSelected(selectedImagePath);
    }

    void onConfirmButtonClicked() {
        emit imageConfirmed(selectedImagePath);
    }

private:
    void setupUi() {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        QStandardItemModel *model = new QStandardItemModel(this);
        this->model = model;

        for (const auto& imagePath : imagePathList) {
            QStandardItem *item = new QStandardItem;
            QPixmap pixmap(imagePath);
            pixmap = pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            item->setData(pixmap, Qt::DecorationRole);
            item->setData(imagePath, Qt::UserRole); // Store the path in user role
            model->appendRow(item);
        }

        QListView *listView = new QListView(this);
        listView->setModel(model);
        listView->setViewMode(QListView::IconMode);
        listView->setResizeMode(QListView::Adjust);
        listView->setGridSize(QSize(200, 200));
        listView->setMovement(QListView::Static);
        listView->setSpacing(10);
        listView->setWrapping(true);
        listView->setFlow(QListView::LeftToRight);
        listView->setSelectionMode(QAbstractItemView::SingleSelection);
        listView->setSelectionRectVisible(false);
        // 允许自动显示滚动条
        listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        listView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        listView->setStyleSheet("QListView { border: none; }");

        // 设置尺寸策略为可扩展
        listView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

        connect(listView, &QListView::clicked, this, &ImageSelectionWidget::onItemClicked);

        mainLayout->addWidget(listView);

        QPushButton *confirmButton = new QPushButton("Confirm", this);
        connect(confirmButton, &QPushButton::clicked, this, &ImageSelectionWidget::onConfirmButtonClicked);

        QHBoxLayout *buttonLayout = new QHBoxLayout;
        buttonLayout->addStretch();
        buttonLayout->addWidget(confirmButton);
        buttonLayout->addStretch();

        mainLayout->addLayout(buttonLayout);

        setLayout(mainLayout);
    }

signals:
    void imageSelected(const QString &path);
    void imageConfirmed(const QString &path);

private:
    QStandardItemModel *model;
    QString selectedImagePath;
    QStringList imagePathList;
};

#endif //IMGSELECTOR_AIIMGSELECTOR_H
