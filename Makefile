# Simple Gain LV2 Plugin Makefile

# Plugin name and URI
PLUGIN_NAME = simple_gain
PLUGIN_SO = $(PLUGIN_NAME).so

# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -fPIC -Wall -Wextra -O2
LDFLAGS = -shared -lm

# LV2 installation directory (can be overridden)
LV2_INSTALL_DIR ?= ~/.lv2

# Plugin bundle directory
BUNDLE_DIR = $(PLUGIN_NAME).lv2

# Source files
SOURCES = simple_gain.c
OBJECTS = $(SOURCES:.c=.o)

# TTL files
TTL_FILES = simple_gain.ttl manifest.ttl

# Default target
all: $(PLUGIN_SO)

# Build the shared library
$(PLUGIN_SO): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Install the plugin
install: $(PLUGIN_SO)
	mkdir -p $(LV2_INSTALL_DIR)/$(BUNDLE_DIR)
	cp $(PLUGIN_SO) $(LV2_INSTALL_DIR)/$(BUNDLE_DIR)/
	cp $(TTL_FILES) $(LV2_INSTALL_DIR)/$(BUNDLE_DIR)/

# Uninstall the plugin
uninstall:
	rm -rf $(LV2_INSTALL_DIR)/$(BUNDLE_DIR)

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(PLUGIN_SO)

# Clean everything including installed files
distclean: clean uninstall

# Create a bundle directory for testing
bundle: $(PLUGIN_SO)
	mkdir -p $(BUNDLE_DIR)
	cp $(PLUGIN_SO) $(BUNDLE_DIR)/
	cp $(TTL_FILES) $(BUNDLE_DIR)/

# Test the plugin with lv2ls (if available)
test: install
	@echo "Testing plugin installation..."
	@if command -v lv2ls >/dev/null 2>&1; then \
		echo "Checking if plugin is discoverable:"; \
		lv2ls | grep -i simple || echo "Plugin not found in lv2ls output"; \
	else \
		echo "lv2ls not available, skipping discovery test"; \
	fi

# Help target
help:
	@echo "Available targets:"
	@echo "  all       - Build the plugin (default)"
	@echo "  install   - Install the plugin to LV2_INSTALL_DIR (default: ~/.lv2)"
	@echo "  uninstall - Remove the installed plugin"
	@echo "  clean     - Remove build artifacts"
	@echo "  distclean - Clean and uninstall"
	@echo "  bundle    - Create a local bundle directory for testing"
	@echo "  test      - Install and test plugin discovery"
	@echo "  help      - Show this help message"
	@echo ""
	@echo "Variables:"
	@echo "  LV2_INSTALL_DIR - Installation directory (default: ~/.lv2)"
	@echo "  CC              - C compiler (default: gcc)"
	@echo "  CFLAGS          - Compiler flags"
	@echo "  LDFLAGS         - Linker flags"

.PHONY: all install uninstall clean distclean bundle test help
