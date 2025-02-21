#
# https://github.com/Xilinx/embeddedsw/tree/master/XilinxProcessorIPLib/drivers/rfdc
#
# include $(BASE_DIR)/rules/Rules.global.make


LIB_NAME = librfdc-mao.so


#############
#  Source
#############

INC += -Iinclude

SRC += xrfdc.c
SRC += xrfdc_clock.c
SRC += xrfdc_g.c
SRC += xrfdc_intr.c
SRC += xrfdc_mb.c
SRC += xrfdc_mixer.c
SRC += xrfdc_mts.c
SRC += xrfdc_sinit.c
# SRC += xrfdc_hw.c


############
#  CFLAGS
############

CFLAGS += -Wall
CFLAGS += $(INC)
CFLAGS += -DMETAL_INTERNAL


############
#  LDFLAGS
############

LDFLAGS += -Wl,-soname,$(LIB_NAME).1
LDFLAGS += -Llib
LDFLAGS += -lmetal


#################
# make command
#################

DEP_CFLAGS = $(filter-out -g, $(CFLAGS))
DEPEND_CMD = $(CC) $(DEP_CFLAGS) -M $<

OBJS = $(SRC:.c=.o)
DEPS = $(SRC:.c=.c.d)


all: $(LIB_NAME).1.1
	$(STRIP) $(LIB_NAME).1.1
	@cp -af $(LIB_NAME)* $(BASE_DIR)
	@cp -af ./lib/libmetal* $(BASE_DIR)
	@cp -af ./lib/libsysfs* $(BASE_DIR)

## following include must be after "all:"
-include $(DEPS)

$(LIB_NAME).1.1: $(OBJS)
	@echo "==============================================================================="
	@echo "LIB_NAME = $(LIB_NAME).1.1"
	@echo "CC       = $(CC)"
	@echo "==============================================================================="
	$(CC) -shared $(LDFLAGS) -o $@ $^
	$(LN) -sf $(LIB_NAME).1.1 $(LIB_NAME).1
	$(LN) -sf $(LIB_NAME).1 $(LIB_NAME)

%.o: %.c
	$(CC) -fPIC $(CFLAGS) -c $< -o $@

ifneq ($(MAKECMDGOALS), clean)
%.c.d: %.c
	@echo Generating depend file $(subst $(BASE_DIR)/,,$(@))
	@echo "$@ \\"        >  $@
	@echo -n "$(dir $<)" >> $@
	@$(DEPEND_CMD)       >> $@ || $(RM) $@
endif

config:

clean:
	@echo "clean $(LIB_NAME).1.1 ..."
	@$(RM) $(LIB_NAME).1.1 $(LIB_NAME).1 $(LIB_NAME)
	@$(RM) $(OBJS) $(DEPS)

.PHONY: config clean
