MAME = /Users/mike/mame0276-arm64/mame
MAME_DIR= $(dir $(MAME))
LOCAL_PATH=$(dir $(abspath $(lastword $(MAKEFILE_LIST))))

all:	test

test:	test.c semigraphics.c semigraphics.h
	zcc +pc6001 -Wall --generic-console -subtype=rom -otest -create-app test.c semigraphics.c

clean:
	rm -rf test*.bin test

run: test
	cd $(MAME_DIR) && $(MAME) pc6001 $(mame_args) -cart1 $(LOCAL_PATH)/test.bin -aviwrite semigraphics.avi
