SRCS=$(wildcard *.rst)

PDFS=$(SRCS:.rst=.pdf)

all: $(PDFS)

%.pdf : %.rst
	bin/rst2pdf \
		--stylesheets="default.json"\
		--stylesheet-path=".styles"\
		$< -o $@

bootstrap.py:
	wget http://svn.zope.org/*checkout*/zc.buildout/trunk/bootstrap/bootstrap.py

bin/buildout: bootstrap.py
	python2.7 bootstrap.py --distribute

buildout: bin/buildout buildout.cfg
	bin/buildout -v

clean:
	rm -f *.pdf
