EAGLE=/Applications/EAGLE/EAGLE.app/Contents/MacOS/EAGLE 

all: motor.brd
	rm -f top.png bottom.png vias.png cutout.png board.png
	$(EAGLE) -C "display none top vias;\
	             export image 'top.png' monochrome 1500;\
	             display none milling;\
	             export image 'cutout.png' monochrome 1500;\
	             export image 'mask.png' monochrome 500;\
	             display all -milling;\
	             export image 'board.png' 500;\
	             quit" motor.brd
