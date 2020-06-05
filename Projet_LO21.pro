QT += widgets
QT += xml
RC_ICONS = resources/icon.ico
RESOURCES += resources.qrc

SOURCES += \
    core/ClasseCompte.cpp \
    core/ComptabiliteManager.cpp \
    core/Compte.cpp \
    core/CompteAbstrait.cpp \
    core/CompteVirtuel.cpp \
    core/Operation.cpp \
    core/Transaction.cpp \
    gui/ComptabiliteForm.cpp \
    gui/ComptesForm.cpp \
    gui/CreationCompteDialog.cpp \
    gui/CreationTransactionDialog.cpp \
    gui/MainWindow.cpp \
    gui/TransactionsForm.cpp \
    gui/VisualiseurForm.cpp \
    main.cpp

HEADERS += \
    core/ClasseCompte.h \
    core/ComptabiliteManager.h \
    core/Compte.h \
    core/CompteAbstrait.h \
    core/CompteException.h \
    core/CompteRacine.h \
    core/CompteVirtuel.h \
    core/ConstReferenceIterator.h \
    core/ConstReferenceIteratorProxy.h \
    core/ISerialisable.h \
    core/Operation.h \
    core/OperationException.h \
    core/ReferenceIterator.h \
    core/SauvegardeException.h \
    core/Transaction.h \
    core/TransactionException.h \
    core/TypeCompte.h \
    core/TypeOperation.h \
    gui/ComptabiliteForm.h \
    gui/ComptesForm.h \
    gui/CreationCompteDialog.h \
    gui/CreationTransactionDialog.h \
    gui/MainWindow.h \
    gui/TransactionsForm.h \
    gui/VisualiseurForm.h

DISTFILES +=

FORMS += \
    gui/ComptabiliteForm.ui \
    gui/ComptesForm.ui \
    gui/CreationCompteDialog.ui \
    gui/CreationTransactionDialog.ui \
    gui/MainWindow.ui \
    gui/TransactionsForm.ui \
    gui/VisualiseurForm.ui
