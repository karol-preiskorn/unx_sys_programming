# Makefile for Unix Systems Programming Project
# This project demonstrates Unix/Linux system programming concepts including:
# - FIFO (Named Pipes)
# - Process Management (fork, exec)
# - Environment Variables

CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -g
SRCDIR := src
BINDIR := bin
DOCDIR := html

# Source files
SOURCES := $(wildcard $(SRCDIR)/*.c)
# Generate executable names from source files
EXECUTABLES := $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%,$(SOURCES))

# Default target
.PHONY: all
all: directories $(EXECUTABLES)

# Create bin directory if it doesn't exist
.PHONY: directories
directories:
	@mkdir -p $(BINDIR)

# Compile each C source file into an executable
$(BINDIR)/%: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<
	@echo "✓ Built $@"

# Run all programs
.PHONY: run
run: all
	@echo "📌 Running FIFO example..."
	@timeout 5 $(BINDIR)/fifo_pipe -r & \
	sleep 1 && \
	$(BINDIR)/fifo_pipe -w || true
	@wait

# Run FIFO pipe program
.PHONY: run-fifo
run-fifo: $(BINDIR)/fifo_pipe
	@echo "📌 Running FIFO example..."
	@timeout 5 $< -r & \
	sleep 1 && \
	$< -w || true
	@wait

# Run fork environment test
.PHONY: run-fork
run-fork: $(BINDIR)/fork_env_z1
	@echo "📌 Running fork environment test..."
	@$<

# Run example-1 program
.PHONY: run-example
run-example: $(BINDIR)/example-1
	@echo "📌 Running example-1..."
	@$<

# Clean build artifacts
.PHONY: clean
clean:
	@rm -rf $(BINDIR)
	@rm -f $(SRCDIR)/*.o
	@rm -f temp.fifo
	@echo "✓ Cleaned build artifacts"

# Clean all including documentation
.PHONY: clean-all
clean-all: clean
	@rm -rf $(DOCDIR) doxy.Doxyfile Makefile.bak latex/
	@echo "✓ Cleaned all artifacts including documentation"

# Display help
.PHONY: help
help:
	@echo "Unix Systems Programming - Makefile targets"
	@echo "=========================================="
	@echo ""
	@echo "Build targets:"
	@echo "  make all           - Build all programs (default)"
	@echo "  make clean         - Remove build artifacts"
	@echo "  make clean-all     - Remove all generated files"
	@echo ""
	@echo "Run targets:"
	@echo "  make run           - Run all example programs"
	@echo "  make run-fifo      - Run FIFO pipe example"
	@echo "  make run-fork      - Run fork environment test"
	@echo "  make run-example   - Run example-1 program"
	@echo ""
	@echo "Info targets:"
	@echo "  make help          - Display this help message"
	@echo "  make info          - Show source and executable files"
	@echo ""
	@echo "Project Programs:"
	@echo "  • fifo_pipe    - Named pipe (FIFO) communication example"
	@echo "  • fork_env_z1  - Fork process and environment variables test"
	@echo "  • example-1    - Basic example program"

# Display project information
.PHONY: info
info:
	@echo "📚 Project Information"
	@echo "======================="
	@echo "Source directory: $(SRCDIR)"
	@echo "Build directory:  $(BINDIR)"
	@echo ""
	@echo "Source files:"
	@for src in $(SOURCES); do echo "  • $$src"; done
	@echo ""
	@echo "Executables:"
	@for exe in $(EXECUTABLES); do echo "  • $$exe"; done

# Rebuild everything
.PHONY: rebuild
rebuild: clean all
	@echo "✓ Rebuild complete"

# Check syntax of all C files without building
.PHONY: check
check:
	@echo "🔍 Checking C source files..."
	@for src in $(SOURCES); do \
		echo "Checking $$src..."; \
		$(CC) -fsyntax-only $(CFLAGS) $$src || exit 1; \
	done
	@echo "✓ All files passed syntax check"

# Install (copy executables to system location)
.PHONY: install
install: all
	@echo "📦 Installing programs..."
	@mkdir -p /usr/local/bin
	@for exe in $(EXECUTABLES); do \
		install -m 755 $$exe /usr/local/bin/; \
		echo "✓ Installed $$(basename $$exe)"; \
	done

# Uninstall
.PHONY: uninstall
uninstall:
	@echo "🗑️  Uninstalling programs..."
	@for exe in $(EXECUTABLES); do \
		rm -f /usr/local/bin/$$(basename $$exe); \
		echo "✓ Removed $$(basename $$exe)"; \
	done

# Run all programs with detailed output
.PHONY: test
test: all
	@echo "🧪 Running tests..."
	@echo ""
	@echo "Test 1: Fork Environment"
	@echo "========================"
	@$(BINDIR)/fork_env_z1
	@echo ""
	@echo "✓ All tests completed"

# Verbose build - show compilation commands
.PHONY: verbose
verbose: CFLAGS += -v
verbose: all

.PHONY: .SILENT
.SILENT: help info
