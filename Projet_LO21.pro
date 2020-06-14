QT += widgets
QT += xml
QT += printsupport
RC_ICONS = resources/icon.ico
RESOURCES += resources.qrc

SOURCES += \
    core/ClasseCompte.cpp \
    core/ComptabiliteManager.cpp \
    core/Compte.cpp \
    core/CompteAbstrait.cpp \
    core/CompteRacine.cpp \
    core/CompteVirtuel.cpp \
    core/Configuration.cpp \
    core/Operation.cpp \
    core/Transaction.cpp \
    core/TypeCompte.cpp \
    core/TypeOperation.cpp \
    gui/ComptabiliteForm.cpp \
    gui/ComptesForm.cpp \
    gui/CreationCompteCapitauxDialog.cpp \
    gui/CreationCompteDialog.cpp \
    gui/CreationTransactionDialog.cpp \
    gui/GenerationBilanDialog.cpp \
    gui/GenerationReleveDialog.cpp \
    gui/GenerationResultatDialog.cpp \
    gui/MainWindow.cpp \
    gui/ModificationTransactionDialog.cpp \
    gui/OperationForm.cpp \
    gui/RapprochementCompteDialog.cpp \
    gui/SuppressionCompteDialog.cpp \
    gui/SuppressionTransactionDialog.cpp \
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
    core/Configuration.h \
    core/ConfigurationException.h \
    core/ConstContainerWrapper.h \
    core/ConstReferenceIterator.h \
    core/ContainerWrapper.h \
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
    gui/CreationCompteCapitauxDialog.h \
    gui/CreationCompteDialog.h \
    gui/CreationTransactionDialog.h \
    gui/GenerationBilanDialog.h \
    gui/GenerationReleveDialog.h \
    gui/GenerationResultatDialog.h \
    gui/MainWindow.h \
    gui/ModificationTransactionDialog.h \
    gui/OperationForm.h \
    gui/RapprochementCompteDialog.h \
    gui/SuppressionCompteDialog.h \
    gui/SuppressionTransactionDialog.h \
    gui/TransactionsForm.h \
    gui/VisualiseurForm.h

DISTFILES +=

FORMS += \
    gui/ComptabiliteForm.ui \
    gui/ComptesForm.ui \
    gui/CreationCompteCapitauxDialog.ui \
    gui/CreationCompteDialog.ui \
    gui/CreationTransactionDialog.ui \
    gui/GenerationBilanDialog.ui \
    gui/GenerationReleveDialog.ui \
    gui/GenerationResultatDialog.ui \
    gui/MainWindow.ui \
    gui/ModificationTransactionDialog.ui \
    gui/OperationForm.ui \
    gui/RapprochementCompteDialog.ui \
    gui/SuppressionCompteDialog.ui \
    gui/SuppressionTransactionDialog.ui \
    gui/TransactionsForm.ui \
    gui/VisualiseurForm.ui
