.PHONY: clean dist

dist: clean
	tar -hzcf "$(CURDIR).tar.gz" matrix/* makefile

clean:
	$(MAKE) -C matrix clean
