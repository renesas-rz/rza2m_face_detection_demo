mkdir -p caltechfaces
cd caltechfaces
wget http://www.vision.caltech.edu/Image_Datasets/Caltech_10K_WebFaces/Caltech_WebFaces.tar
7za x Caltech_WebFaces.tar
rm Caltech_WebFaces.tar
wget http://www.vision.caltech.edu/Image_Datasets/Caltech_10K_WebFaces/WebFaces_GroundThruth.txt
