# Copyright AllSeen Alliance. All rights reserved.
#
#    Permission to use, copy, modify, and/or distribute this software for any
#    purpose with or without fee is hereby granted, provided that the above
#    copyright notice and this permission notice appear in all copies.
#
#    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
#    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
#    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
#    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
#    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
#    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
#    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

ALLJOYN_DIST := ../..
#ALLJOYN_DIST := ../../../build/linux/x86/debug/dist

ALLJOYN_LIB := $(ALLJOYN_DIST)/lib/liballjoyn.a

CXXFLAGS = -Wall -pipe -std=c++98 -fno-rtti -fno-exceptions -Wno-long-long -Wno-deprecated -g -DQCC_OS_LINUX -DQCC_OS_GROUP_POSIX

LIBS = -lalljoyn -lstdc++ -lcrypto -lpthread -lrt 

.PHONY: default clean

default: chat

clean:
	rm -f chat.o chat

chat: chat.o $(ALLJOYN_LIB)
	$(CXX) -o $@ chat.o -L$(ALLJOYN_DIST)/lib $(LIBS)

chat.o: chat.cc $(ALLJOYN_LIB)
	$(CXX) -c $(CXXFLAGS) -I$(ALLJOYN_DIST)/inc -o $@ chat.cc

