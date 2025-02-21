# include $(BASE_DIR)/rules/Rules.global.make

APPS = dac_current adc_dsa
APPS = adc_dsa


############
#  CFLAGS
############

CFLAGS += -Wall
CFLAGS += -Wundef
CFLAGS += -Wno-format-truncation
CFLAGS += -O2
CFLAGS += -DMETAL_INTERNAL
CFLAGS += -Ilibrfdc
CFLAGS += -Ilibrfdc/include


############
#  LDFLAGS
############

LDFLAGS += -Llibrfdc
LDFLAGS += -Llibrfdc/lib
# LDFLAGS += -lsysfs
LDFLAGS += -lmetal
LDFLAGS += -lrfdc-mao


############
#  Build
############

all: $(APPS)
	# @cp -f $(APPS) $(BASE_DIR)

dac_current: dac_current.c
	$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@

adc_dsa: adc_dsa.c
	$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@

reg_tool: reg_tool.c
	$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@

clean:
	@$(RM) $(APPS)

.PHONY: clean
