PARTIE III

[OK]Toutnoir est déjà un booléen, simplifiez if/return (image->toutnoir ==
[OK]true) en if/return (image->toutnoir)


[OK]ConstruitBNC : Cblanc : inutile de passer par une variable

[OK]AfficheSP : ras

[OK]EstNB : ras // découpez un peu plus en ligne, ça déborde

[OK]copie : pourquoi B et N sont copiés en .BBBB .NNNN et pas en B et N ????

aire :

[OK]MemeDessin :
[OK]evitez de faire "if non truc then long else court"  ---> if test then
[OK]court else long
[OK]      surtout sur un truc comme MD...
[OK]plante si i1 composée et i2  B ou N

[OK]Difference : quadratique
[OK]   plante si une imae coposee et l'autre simple

[OK]Rendmemoire : vous vous plantez d'un niveau de pointeur, free(img); ->
[OK]free(*img);

Lecture :          les char autres que .BN sont autorisés, et ils sont
ignorés

CSIP : na

Arrondit : na

[OK]Negatif : quadratique
[OK]       faire des free

Simplifie : na

Pixel : na

Alea :
