

target := exec

include_path := src		\
				src/others \
				include

include := $(foreach item,$(include_path),-I$(item))


compile_flags := -g -w $(include)


c_srcs := $(shell find src -name *.c)

c_srcs_obj := $(dir $(subst src,obj,$(c_srcs)))

$(foreach item,$(c_srcs_obj),$(shell mkdir -p $(item)))

c_srcs_i := $(patsubst src/%.c,obj/%.i,$(c_srcs))
c_srcs_s := $(patsubst src/%.c,obj/%.s,$(c_srcs))
c_srcs_o := $(patsubst src/%.c,obj/%.o,$(c_srcs))

obj/%.i : src/%.c
	mkdir -p $(dir $@)
	gcc -E $^ -o $@  $(compile_flags)


obj/%.s : src/%.c
	mkdir -p $(dir $@)
	gcc -S $^ -o $@ $(compile_flags) 


obj/%.o : src/%.c
	mkdir -p $(dir $@)
	gcc -c $^ -o $@ $(compile_flags)


lib_srcs := $(filter-out %main.c, $(shell find src -name *.c))
lib_objs := $(patsubst src/%.c,objs/%.o,$(lib_srcs))



objs/%.o : src/%.c
	mkdir -p $(dir $@)
	gcc -c $^ -o $@ $(include)


lib/libmyma.a : $(lib_objs)
	mkdir -p $(dir $@)
	ar -r $@ $^

slib : lib/libmyma.a


all : $(c_srcs_i)
all : $(c_srcs_s)
all : $(c_srcs_o)
all : bin/$(target)


objs/main.o : src/main.c
	@mkdir -p $(dir $@)
	@gcc -c $< -o $@ $(include)
	

lib_path := lib

link_lib := myma

L_opt := $(lib_path:%=-L%)
l_opt := $(link_lib:%=-l%)


exe : slib
exe : objs/main.o
	@gcc $^ -o $@ $(L_opt) $(l_opt)


sall:exe


bin/$(target) : $(c_srcs_o)
	@mkdir -p  $(dir $@)
	@gcc $^ -o $@ $(include)

run : bin/$(target)
	@./$<

test :
	$(error no test)


debug :
	@echo $(C_OBJS)


C_SRCS := $(shell find src -name "*.c")
C_OBJS := $(patsubst src/%.c,obj/%.o,$(C_SRCS))
INCLUDE_DIR := include
I_INCLUDE_DIR := $(INCLUDE_DIR:%=-I%)

SO_OBJS := $(filter-out obj/main.o,$(C_OBJS))


SO_DIR := solib
SO_LIBS := mat

L_SO_DIR := $(SO_DIR:%=-L%)
l_SO_LIBS := $(SO_LIBS:%=-l%)
OPT := $(SO_DIR:%=-Wl,-rpath=%)

work : obj/main.o
	@gcc $< -o $@ $(L_SO_DIR) $(l_SO_LIBS) $(OPT)

compile_opt := -g  -fPIC $(I_INCLUDE_DIR)

obj/%.o : src/%.c
	@mkdir -p $(dir $@)
	@gcc -c $^ -o $@ $(compile_opt)

compile : $(C_OBJS)

solib/libmat.so : $(SO_OBJS)
	@mkdir -p $(dir $@)
	@gcc -shared $^ -o $@

so : solib/libmat.so


	

PHONY : debug


clean :
	rm -rf obj
	rm -rf bin

tee :
	B := "123"
	ifneq($(B),"123")
		@echo "11111"
	else
		@echo "2222"
	endif
