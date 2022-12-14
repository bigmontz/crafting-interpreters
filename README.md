# My challenges resolutions from Crafting Interpreters

Repository with study material used while read Crafting Interpreters

The challenges will be implemented in branches name with the format: `${chapter_number}.${challenge_number}-${brief_description}`. Challenges part of the main flow be merged to the main branch using pull requests.

## Folders and Structure

### `/java`

The project with the Java implementation of the interpreter builded during the course.
This is the least performant and more straightforward version of the interpreter.

#### Dependency

```
java: 8
maven: 3.6.3
gnu make: 3.81
```

#### Commands

- `make java-build` builds the project
- `make java-run` runs the project

### `/c`

The project with the C implementation of the interpreter builded during the course.
This is the more performant version of the interpreter.

#### Dependency

```
gcc: 4.2.1
gnu make: 3.81
```
#### Commands

- `make c-build` builds the project
- `make c-run` runs the project

### `/elixir`

The project with the Elixir implementation of the interpreter builded during the course.
This is equivalent version of the Java, but implemented in Elixir. 

#### Dependency

```
elixir: 1.13.3 
mix: 1.13.3
```

#### Commands

The commands for this project are described at `elixir/README.md`
