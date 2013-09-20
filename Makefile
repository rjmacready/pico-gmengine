
out/main: src/main.c out/main-lisp.a src/scripts.c
	$(CC) `ecl-config --cflags` -o $@ $^ \
	      `ecl-config --ldflags` -lecl -lSDL

out/main-lisp.a: src/main-lisp.lisp
	ecl -norc \
	    -eval '(require :asdf)' \
	    -eval '(push "./" asdf:*central-registry*)' \
	    -eval '(asdf:make-build :main-lisp :type :static-library :move-here "./$@")' \
	    -eval '(quit)'

clean:
	rm -f out/*
