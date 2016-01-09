all:
	@make -C arch/x86
	@make -C utils
clean:
	@echo "CLEAN arch/x86"
	@make -C arch/x86 clean
	@echo "CLEAN utils"
	@make -C utils clean
