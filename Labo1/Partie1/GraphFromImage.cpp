#include "GraphFromImage.h"

GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
    /* A IMPLEMENTER */
    /*???????????????*/
}

bool GraphFromImage::memePixel(int x1, int y1, int x2, int y2) const{
    unsigned char   rouge1, bleu1, vert1,
                    rouge2, bleu2, vert2;
    
    image.get_pixel(x1, y1, rouge1, bleu1, vert1);
    image.get_pixel(x2, y2, rouge2, bleu2, vert2);
    
    return (rouge1 == rouge2 && bleu1 == bleu2 && vert1 == vert2);
}

GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
    Iterable list;
    int colonne = x(v);
    int ligne   = y(v);
    
    
    //Pixel du dessus
    //Afin d'éviter tout probleme, il est nécessaire d'effectuer le test dans cet 
    //ordre precis (bord image puis pixel identique
    if(ligne != 0 && memePixel(colonne, ligne, colonne, ligne - 1)){
        list.push_back(idx(colonne, ligne - 1));
    }
    
    // Pixel de gauche
    if(colonne != 0 && memePixel(colonne,ligne, colonne - 1, ligne)){
        list.push_back(idx(colonne - 1, ligne));
    }
    
    // Pixel de droite
    if(colonne != image.width() && memePixel(colonne, ligne, colonne + 1, ligne)){
        list.push_back(idx(colonne + 1, ligne));
    }
    
    // Pixel du bas
    if(ligne != image.height() && memePixel(colonne, ligne, colonne, ligne + 1)){
        list.push_back(idx(colonne, ligne + 1));
    }
    return list;
}

int GraphFromImage::idx(int x, int y) const {
    return (y * image.width()) + x;
}

int GraphFromImage::x(int idx) const {
    return idx % image.width();
}

int GraphFromImage::y(int idx) const {
    return idx / image.width();
}

int GraphFromImage::V() const {
    return image.width() * image.height();
}
