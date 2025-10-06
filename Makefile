CFLAGS=-Wall -Wextra -Werror
MAC_OS_SDK=/Applications/Xcode_16_4.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk

build: dictionary

install: dictionary
	cp dictionary /usr/local/bin/dictionary

uninstall:
	rm -f /usr/local/bin/dictionary

run: dictionary
	./dictionary

dictionary: main.c
	$(CC) $(CFLAGS) -isysroot $(MAC_OS_SDK) -framework CoreFoundation -framework CoreServices main.c -o dictionary

clean:
	rm -f *.o
	rm -f dictionary
	rm -f dictionary.dSYM/
