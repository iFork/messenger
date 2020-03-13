cpp_files := $(wildcard *.cpp)

LIBS := -lPocoJSONd \
		-lPocoFoundationd \
		-lPocoXMLd\
		-lPocoUtild\
		-lPocoNetd\
		-pthread

all : clean run

run : $(cpp_files)
	@ctags -R
	@g++ $^ -o $@ $(LIBS) -std=c++11

clean:
	@rm -f run tags
