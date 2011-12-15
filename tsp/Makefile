ataskaita.pdf: ataskaita.rst
	bin/rst2pdf ataskaita.rst -o ataskaita.pdf

bootstrap.py:
	wget http://svn.zope.org/*checkout*/zc.buildout/trunk/bootstrap/bootstrap.py

bin/buildout: bootstrap.py
	python2.7 bootstrap.py --distribute

buildout: bin/buildout buildout.cfg
	bin/buildout -v

show:
	xdg-open ataskaita.pdf
