#-------------------------------------------------
exec=single

#-------------------------------------------------
src= \
$(exec).cpp

#-------------------------------------------------
# probably don't have to change below this line

#-------------------------------------------------
incs=../../libs/
cflags=-std=c++11 -Werror -Wall -O2 -I. -I$(incs)/acctlib -I$(incs)/etherlib -I$(incs)/utillib

#-------------------------------------------------
libs=../../libs/*.a
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    libs += -lcurl
endif
ifeq ($(UNAME_S),Darwin)
    libs += /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib/libcurl.tbd
endif

#-------------------------------------------------
product=objs/$(exec)

#-------------------------------------------------
all:
	@make app

app:
	@make $(product)
	mv $(product) ./bin/

objects = $(patsubst %.cpp,objs/%.o,$(src))

$(product): $(objects) $(libs)
	g++ -o $(product) $(objects) $(libs)
	@strip $(product)

$(objects): | objs

objs:
	@mkdir -p ./objs ./bin

objs/%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(cflags) -c $< -o $@

clean:
	-@$(RM) -fR ./bin objs 2> /dev/null
