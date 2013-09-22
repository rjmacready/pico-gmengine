
main: src/main.c main-lisp.a src/scripts.c src/pixels.c src/circles.c
	$(CC) `ecl-config --cflags` -o $@ $^ \
	      `ecl-config --ldflags` -lecl -lSDL -lSDL_image -lSDL_ttf

main-lisp.a: src/main-lisp.lisp
	ecl -norc \
	    -eval '(require :asdf)' \
	    -eval '(push "./" asdf:*central-registry*)' \
	    -eval '(asdf:make-build :main-lisp :type :static-library :move-here "./$@")' \
	    -eval '(quit)'

clean:
	rm -f main main-lisp.a
