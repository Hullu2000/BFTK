ri: uninstall install

install:
	mkdir /usr/share/BFTK
	cp ./C/* /usr/share/BFTK
	cp ./bftk /usr/bin

uninstall:
	rm -r /usr/share/BFTK
	rm /usr/bin/bftk

get:
	cp /usr/share/BFTK/* ./C
	cp /usr/bin/bftk .