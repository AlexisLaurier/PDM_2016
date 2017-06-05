// Projet BDM 2017 -- JULIAN Romain

#ifndef WEBCAM_H
#define WEBCAM_H


#include <QWidget>
#include <QLabel>
#include "opencv2/opencv.hpp"
#include "element.h"
#include "tir.h"


class Webcam : public QLabel // Dérive de QLabel entre autre pour la fonction setPixmap permetant de facilement afficher l'image de la WebCam.
{
    Q_OBJECT
public:
    explicit Webcam(QWidget *parent = 0);
    ~Webcam();
    // Getter
    bool mainDetected() { return mainDetected_;}
    cv::Mat image() { return image_;}
    cv::Mat imageMain() { return imageMain_;}
    cv::Rect rectMain() { return rectMain_;}
    // Setter
    void setMainDetected(bool mainDetected) { mainDetected_ = mainDetected; }
    void setImageMain(cv::Mat imageMain) { imageMain_=imageMain; }
    void setLastX(int x){ lastX_=x;}
    void setLastY(int y){ lastY_=y;}
    void setTrebuchet(Element * trebuchet) {trebuchet_ = trebuchet; }
    void setTir(Tir *elm){tir_=elm;}
    // Gere le suivi de la main lorsque celle-ci est déjà detectée, gère le mouvement du trebuchet.
    void suivreMain();
    // Gere l'affichage du rectangle de detection de la main ainsi que le demarrage d'une detection (lorsque apparition d'un objet dans le cadre) La fin de la detection est gérée par la fonction reload.
    void detecterMain();


signals:

public slots:
    // Est appelé toutes les 10ms, permettant de gérer l'affichage d'une image de la Webcam. Appel les fonctions suivreMain() ou detecterMain() suivant les besoins
    void reload();
signals:
    // Est connecté au SLOT de reload du Widget OpenGL, est appelé à chaque modification du trebuchet.
    void changementOpenGl();
private:
    // Contient l'image obtenue par la webCam puis affichée
    cv::Mat image_;
    // Contient l'image de la main à suivre
    cv::Mat imageMain_;
    // Contient l'image présente dans le cadre de détection à l'initialisation.
    cv::Mat imageFond_;
    // Gère la WebCam
    cv::VideoCapture * webCam_;
    // Contient la taille que nous souhaitons donner à l'image de la webcam affichée
    QSize webcamSize_;
    // true signifie qu'on est en train de suivre la main
    bool mainDetected_;
    // true signifie qu'on a perdu l'element que l'on suivait
    bool perdu_;
    // Mis à true lors d'un changement dans le rectangle de detection dans detectionMain(), déclenche la suite de la détéction dans reload().
    bool detectionEnCours_;
    // Mis à true lorsqu'un tir du trébuchet est en cours, indique que l'on stoppe tout suivi.
    bool tirEnCours_;
    // Rectangle de détéction
    cv::Rect rectMain_;
    // Dernière abscisse de l'origine du rectangle de détection connue
    int lastX_;
    // Dernière ordonnée de l'origine du rectangle de détection connue
    int lastY_;
    // Permet de compter un certain nombre de frame après un changement dans le rectangle de détection pendant lesquels on essaye de detecter un mouvement vers le bas.
    int cpt_;
    // Permet de vérifier si le mouvement vers le bas de detection est continue sur plusieurs frames. Permet une mailleure stabilité de la detection
    int continuiteDetection_;
    // Sert à gérer le reload de l'image affichée toutes les  ms.
    QTimer *timer;
    // Variable contenant l'angle actuel du trebuchet.
    double angle_;
    // Variable contenant la puissance actuel du trebuchet (visuellement l'inclinaison du bras)
    double puissance_;
    // Pointeur vers le trebuchet servant à modifier sa direction et l'inclinaison du bras
    Element* trebuchet_;
    // Permet de déclencher un tir
    Tir* tir_;
};

#endif // WEBCAM_H
