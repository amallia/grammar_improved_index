all: clean libcompact

doc:
	@echo " [DOC] Generating documentation"
	@doxygen

libcompact: 
	@echo " [MSG] Entering directory src"
	@CPPFLAGS="$(CPPFLAGS)" make --no-print-directory -C src

clean:
	@echo " [MSG] Entering directory src"
	@make --no-print-directory -C src clean
	@echo " [CLN] Cleaning docs folder"
	@rm -rf docs/*
	@touch docs/delete_me
	@echo " [CLN] Cleaning lib folder"
	@rm -f lib/*
	@touch lib/delete_me
	@echo " [CLN] Cleaning includes folder"
	@rm -f includes/*
	@mkdir -p includes
	@touch includes/delete_me


