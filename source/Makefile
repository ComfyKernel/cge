DIRS := $(patsubst %/,%,$(shell ls -dR $(wildcard */)))

all:
	@$(foreach DIR,$(DIRS),$(MAKE) -C $(DIR);)
