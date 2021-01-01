include $(OPENCM3_DIR)/mk/genlink-config.mk

.PHONY: CPPFLAGS
CPPFLAGS:
	@echo $(CPPFLAGS) $(ARCH_FLAGS)