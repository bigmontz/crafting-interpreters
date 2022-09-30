.DEFAULT_GOAL = help

.PHONY: all
all: java-build ## Build and test the interpreters

.PHONY: java-build
java-build: ## Build the Java Interpreter
	mvn -f ./java/pom.xml package

.PHONY: java-run 
java-run: ## Run the Java Interpreter
	java -jar ./java/target/lox-0.0.0-SNAPSHOT.jar

# based on: http://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
help: ## Shows this message
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'
