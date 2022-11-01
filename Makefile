.DEFAULT_GOAL = help
DIR := c
C_TEST_SOURCES := $(wildcard $(DIR)/*_test.c)
C_MAIN := c/main.c
C_APPLICATION_SOURCES := $(filter-out $(wildcard $(DIR)/*_test.c),$(wildcard $(DIR)/*.c))
C_SOURCES := $(filter-out $(C_MAIN),$(C_APPLICATION_SOURCES))
JAVA_BASE_PACKAGE_DIR := java/src/main/java/com/craftinginterpreters/lox
RUN_PARAMS=''

.PHONY: all
all: java-build c-build ## Build and test the interpreters

.PHONY: java-build
java-build: ## Build the Java Interpreter
	mvn -f ./java/pom.xml package

.PHONY: java-run 
java-run: ## Run the Java Interpreter
	java -jar ./java/target/lox-0.0.0-SNAPSHOT.jar $(RUN_PARAMS)

.PHONY: java-tool-run 
java-tool-run: ## Run the Java Tool
	java -cp ./java/target/lox-0.0.0-SNAPSHOT.jar com.craftinginterpreters.tool.GenerateAst $(JAVA_BASE_PACKAGE_DIR)

.PHONY: java-astrpnprinter-run 
java-astrpnprinter-run : ## Run the Java Tool
	java -cp ./java/target/lox-0.0.0-SNAPSHOT.jar com.craftinginterpreters.lox.AstRPNPrinter


.PHONY: c-clean
c-clean: ## Clean the C Interpreter files
	test -s c/target && rm -fr c/target
	mkdir c/target

.PHONY: c-test
c-test: $(C_SOURCES) $(C_TEST_SOURCES) c-clean ## Test the C Interpreter
	$(foreach test,$(C_TEST_SOURCES), gcc -Werror -o c/target/test $(test) $(C_SOURCES); chmod +X c/target/test; ./c/target/test)


.PHONY: c-build 
c-build: $(C_APPLICATION_SOURCES) c-test c-clean ## Build the C Interpreter
	gcc -o c/target/lox $(C_APPLICATION_SOURCES)
	chmod +X c/target/lox

.PHONY: c-run 
c-run: ## Run the C Interpreter
	./c/target/lox

# based on: http://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
help: ## Shows this message
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'
