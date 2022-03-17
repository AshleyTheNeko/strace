##
## EPITECH PROJECT, 2021
## strace
## File description:
## Makefile
##

SHELL	=	/bin/sh
CC	=	gcc
RM	= 	rm -rf

MAIN	=	src/main.c

SRC	=	src/strace.c

OBJ	=	$(addsuffix .o, $(basename $(SRC)))

LDFLAGS	=
CFLAGS	=	-Wall -Wextra
CPPFLAGS=	-I include

OK	=	\e[32m
RED	=	\e[91m
END	=	\e[0m

T_PRUNE	=

SRC_T	=	tests/unit_tests.c

T_NAME	=	unit_tests
NAME	=	strace
PHONY	:=	all
DEBUG	=	0

define center_text
	echo -e "$(OK)>>>>\t$1$(END)"
endef

ifeq ($(DEBUG), 1)
	CFLAGS += -g
endif

all: $(NAME)

$(NAME): $(SRC) $(MAIN)
	@$(call center_text,$(NAME))
	$(eval OBJ += $(MAIN:.c=.o))
	@$(MAKE) -s $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) && \
	echo -e "$(OK)[DONE]\t$(NAME)$(END)" || \
	echo -e "$(RED)[FAILURE]\t$(NAME)$(END)"

%.o: %.c
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $< && \
	echo -e "$(OK)[OK]\t$<$(END)" || \
	echo -e "$(RED)[FAILURE]\t$<$(END)"

PHONY += rm_prompt
rm_prompt:
	@$(call center_text,Clean)

PHONY += clean
clean: rm_prompt
	@$(RM) $(OBJ) $(MAIN:.c=.o)
	@echo -e "$(RED)$(NAME) : Removed object files.$(END)"

PHONY += fclean
fclean: clean rm_prompt
	@$(RM) $(NAME)
	@echo -e "$(RED)$(NAME) : Removed $(NAME).$(END)"

PHONY += tclean
tclean: rm_prompt
	@find ./ -name "*.gcno" -delete -o -name "*.gcda" -delete
	@$(RM) $(T_NAME)
	@echo -e "$(RED)Tests : Cleaned gc** and ./$(T_NAME).$(END)"

PHONY += fltclean
fltclean: fclean tclean

PHONY += re
re: fltclean all

PHONY += tests_run
tests_run: fltclean $(SRC) $(SRC_T)
	@$(call center_text,$(T_NAME))
	@$(eval CFLAGS += --coverage)
	@$(eval LDFLAGS += -l criterion --coverage)
	@$(eval OBJ += $(addsuffix .o, $(basename $(SRC_T))))
	@$(eval OBJ := $(filter-out $(T_PRUNE:.c=.o),$(OBJ)))
	@$(eval SRC := $(filter-out $(T_PRUNE),$(SRC)))
	@$(MAKE) -s $(OBJ) CFLAGS="$(CFLAGS)"
	@$(CC) -o $(T_NAME) $(OBJ) $(LDFLAGS) && \
	(echo -e "$(OK)[DONE]\t$(T_NAME)$(END)";\
	echo -e "$(OK)[EXECUTING TESTS]$(END)"; ./$(T_NAME)) || \
	echo -e "$(RED)[FAILURE]\t$(T_NAME)$(END)"

.PHONY: $(PHONY)
