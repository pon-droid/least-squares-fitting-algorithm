

CXX=$(CROSS)g++
LD=$(CROSS)ld
AR=$(CROSS)ar
PKG_CONFIG=$(CROSS)pkg-config

FILES=main.cpp

PKGS=sdl2
TITLE=least-squares-fitting-algo
OPT=opt

CFLAGS=-Wall -Wextra -pedantic -std=c++11 `$(PKG_CONFIG) --cflags $(PKGS)`
CRFLAGS=-Wall -Wextra -pedantic -O2 -std=c++11 `$(PKG_CONFIG) --cflags --static $(PKGS)`
LIBS=`$(PKG_CONFIG) --libs $(PKGS)`



debug: $(FILES)
	$(CXX) $(CFLAGS) -o $(TITLE) $(FILES) $(LIBS)

opt: $(FILES)
	$(CXX) $(CRFLAGS) -o $(TITLE)-opt  $(FILES) $(LIBS)

clean:
	rm $(TITLE)
