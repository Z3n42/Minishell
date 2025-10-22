<div align="center">

# 🐚 Minishell

### As beautiful as a shell

<p>
  <img src="https://img.shields.io/badge/Score-96%2F100-success?style=for-the-badge&logo=42" alt="42 Score"/>
  <img src="https://img.shields.io/badge/Team-2_Developers-blue?style=for-the-badge" alt="Team"/>
  <img src="https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="Language"/>
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" alt="License"/>
  <img src="https://img.shields.io/badge/42-Urduliz-000000?style=for-the-badge&logo=42&logoColor=white" alt="42 Urduliz"/>
</p>

*A minimalist UNIX shell implementation that interprets commands, handles pipes, redirections, environment variables, and signal management - recreating the essence of bash.*

[Installation](#%EF%B8%8F-installation) • [Usage](#-usage) • [Features](#-features) • [Architecture](#-architecture)

</div>

---

## 📋 Table of Contents

- [About the Project](#-about-the-project)
- [Team](#-team)
- [Installation](#%EF%B8%8F-installation)
- [Usage](#-usage)
- [Features](#-features)
- [Architecture](#-architecture)
- [Implementation Details](#-implementation-details)
- [Built-in Commands](#-built-in-commands)
- [Project Structure](#-project-structure)
- [Testing](#-testing)
- [What We Learned](#-what-we-learned)
- [License](#-license)

---

## 🎯 About the Project

**Minishell** is a project that involves creating a simplified UNIX shell from scratch. The goal is to understand how shells work internally - from tokenizing input to executing processes with proper signal handling and redirection management.

### Why Minishell?

This project provides hands-on experience with:
- **Process Management** - `fork()`, `execve()`, `wait()`
- **Pipe Management** - Inter-process communication
- **File Descriptors** - `dup2()`, redirection handling
- **Signal Handling** - `SIGINT`, `SIGQUIT` behavior
- **Environment Management** - Variable expansion and modification
- **Parsing** - Lexical analysis and syntax validation
- **Memory Management** - Complex allocation/deallocation patterns

The challenge is to replicate bash behavior while maintaining clean, norm-compliant code.

---

## 👥 Team

This project was developed collaboratively by:

- **[Z3n42](https://github.com/Z3n42)** (ingonzal)
- **[ibanezinigo](https://github.com/ibanezinigo)** (iibanez-)

Working in a team added complexity in code integration, consistent style, and collaborative problem-solving.

---

## 🛠️ Installation

### Prerequisites

- **GCC** or **Clang** compiler
- **Make**
- **readline** library (`brew install readline` on macOS)
- Unix-based system (Linux, macOS)

### Clone and Compile

```bash
# Clone the repository
git clone https://github.com/Z3n42/minishell.git
cd minishell

# Compile the shell
make

# Clean object files
make clean

# Clean everything
make fclean

# Recompile
make re
```

After running `make`, you'll have the `minishell` executable.

---

## 🚀 Usage

### Starting Minishell

```bash
./minishell
```

You'll see a prompt similar to bash:

```
minishell$
```

### Basic Commands

```bash
minishell$ echo Hello World
Hello World

minishell$ pwd
/home/user/minishell

minishell$ ls -la | grep minishell
```

### Exiting

```bash
minishell$ exit
```

Or press `Ctrl+D`.

---

## ✨ Features

### Core Functionality

#### 1. Command Execution

```bash
# Search in PATH
minishell$ ls -la

# Absolute path
minishell$ /bin/echo "Direct path"

# Relative path
minishell$ ./minishell
```

#### 2. Pipes

```bash
minishell$ cat file.txt | grep "pattern" | wc -l

minishell$ ls -l | awk '{print $9}' | sort
```

**Implementation**: Creates pipes between processes, redirecting stdout/stdin accordingly.

#### 3. Redirections

```bash
# Input redirection
minishell$ cat < input.txt

# Output redirection (truncate)
minishell$ echo "test" > output.txt

# Output redirection (append)
minishell$ echo "more" >> output.txt

# Here-document
minishell$ cat << EOF
> line 1
> line 2
> EOF
```

#### 4. Environment Variables

```bash
# Expansion
minishell$ echo $HOME
/home/user

# Setting
minishell$ export VAR=value

# Unsetting
minishell$ unset VAR

# Exit status
minishell$ ls
minishell$ echo $?
0
```

#### 5. Quotes

```bash
# Single quotes (literal)
minishell$ echo 'Hello $USER'
Hello $USER

# Double quotes (expand variables)
minishell$ echo "Hello $USER"
Hello ingonzal
```

#### 6. Signals

- **Ctrl+C**: Interrupts current command, shows new prompt
- **Ctrl+D**: Exits shell (EOF)
- **Ctrl+\**: Does nothing (ignored)

### Built-in Commands

| Command | Description | Options |
|---------|-------------|---------|
| `echo` | Print arguments | `-n` (no newline) |
| `cd` | Change directory | `~`, `-`, relative/absolute paths |
| `pwd` | Print working directory | None |
| `export` | Set environment variable | None |
| `unset` | Remove environment variable | None |
| `env` | Print environment | None |
| `exit` | Exit shell | None |

---

## 🏗️ Architecture

The implementation follows a **modular pipeline architecture**:

```
Input → Lexer → Parser → Syntax Checker → Executor
```

### Processing Flow

```
1. readline()        → Get user input
2. ft_lexer()        → Tokenize input
3. ft_parser()       → Build command structure
4. ft_syntax()       → Validate syntax
5. ft_execute()      → Execute commands
```

### Module Breakdown

#### 1. Lexer (Tokenization)

**Location**: `lexer/lexer.c`

**Function**: `t_list *ft_lexer(char *readl)`

**Purpose**: Converts raw input string into tokens (linked list).

```c
Input:  "ls -la | grep test"
Output: ["ls"] -> ["-la"] -> ["|"] -> ["grep"] -> ["test"]
```

**Key Features**:
- Quote handling (`'`, `"`)
- Special character detection (`|`, `<`, `>`, `;`, `&`)
- Whitespace trimming
- Token extraction with `ft_reduce()`

**Implementation**:
```c
t_list *ft_lexer(char *readl)
{
    t_list *start = NULL;
    char *str = ft_strcpy(readl);

    while (ft_strcontainstext(str))
    {
        // Skip whitespace
        // Extract token with quote handling
        // Add to linked list
    }

    return (start);
}
```

#### 2. Parser (Command Structuring)

**Location**: `parser/ft_parser.c`

**Function**: `t_list **ft_parser(t_list *lexer)`

**Purpose**: Converts token list into command array (separated by pipes).

```c
Tokens:  ["ls"] -> ["-la"] -> ["|"] -> ["grep"] -> ["test"]
Output:  [ ["ls", "-la"], ["grep", "test"] ]
```

**Structure**:
- Splits on pipe `|` operator
- Creates array of command lists
- Each command is a linked list of tokens

#### 3. Syntax Checker

**Location**: `syntax/ft_syntax.c`, `syntax/ft_syntaxchecker.c`

**Function**: `int ft_syntax(t_list *lexer)`

**Purpose**: Validates syntax before execution.

**Checks**:
- Unclosed quotes
- Invalid pipe placement
- Invalid redirection syntax
- Empty commands

#### 4. Executor (Execution Engine)

**Location**: `executor/ft_executor.c`

**Function**: `int ft_execute(t_list **lcommands, t_execution *exe)`

**Purpose**: Executes parsed commands with pipes and redirections.

**Process**:
```c
1. Create pipes between commands
2. For each command:
   - Handle redirections (input/output)
   - Check if builtin
   - Fork if not builtin
   - Execute in child process
3. Wait for all processes
4. Clean up pipes and memory
```

---

## 💻 Implementation Details

### Data Structures

#### t_list (Token/Command Node)

```c
typedef struct s_list
{
    char         *token;    // Command or argument
    struct s_list *next;    // Next token
}   t_list;
```

**Usage**: Linked list for tokens and command arguments.

#### t_execution (Execution Context)

```c
typedef struct s_execution
{
    t_list  *envp;          // Environment variables
    int     **pipes;        // Pipe file descriptors
    int     *pids;          // Process IDs
    int     total_f;        // Fork count
    int     in_redi;        // Input redirection type
    int     redi;           // Output redirection type
    char    *inputfile;     // Input filename
    char    *inputpath;     // Input file path
    char    *outputfile;    // Output filename
}   t_execution;
```

**Usage**: Maintains state across command execution.

#### g_global (Global State)

```c
typedef struct s_global
{
    int errnor;     // Last exit status ($?)
    int pid;        // Current process PID
}   t_global;
```

**Note**: Only one global variable allowed per project requirements.

### Key Algorithms

#### 1. Lexer Quote Handling

```c
void ft_quote(char *str, int *i, char *quote, char *token)
{
    while ((ft_isspace(str[*i]) == 0 && str[*i] != '|' && str[*i] != '<'
        && str[*i] != '>' && str[*i] != ';' && str[*i] != '&'
        && str[*i] != '\0') || *quote != '\0')
    {
        token[*i] = str[*i];

        // Toggle quote state
        if (str[*i] == *quote)
            *quote = '\0';
        else if ((str[*i] == '"' || str[*i] == '\'') && *quote == '\0')
            *quote = str[*i];

        *i = *i + 1;
    }
}
```

**Logic**: Tracks quote state, continues token extraction inside quotes.

#### 2. Executor Logic

```c
void ft_execute_aux_2(t_list *command, t_execution *exe, int i)
{
    ft_str_to_lower(command->token);
    ft_clean_quote(command, exe->envp);

    // Check for builtins (no fork needed)
    if (ft_strequals(command->token, "cd"))
        ft_cd(command, exe);
    else if (ft_strequals(command->token, "export"))
        ft_export(command, exe);
    else if (ft_strequals(command->token, "unset"))
        ft_unset(command, exe);
    else if (ft_strequals(command->token, "exit"))
        ft_exit(command);
    else
        ft_execute_not_builtin(command, exe, i);
}
```

**Builtins**: Execute in parent process (no fork) to modify shell state.

**External commands**: Fork and execute with `execve()`.

#### 3. Pipe Creation

```c
void ft_create_pipes(t_list **lcommands, t_execution *exe)
{
    int command_count = 0;

    while (lcommands[command_count])
        command_count++;

    exe->pipes = malloc(sizeof(int *) * (command_count - 1));

    for (int i = 0; i < command_count - 1; i++)
    {
        exe->pipes[i] = malloc(sizeof(int) * 2);
        pipe(exe->pipes[i]);  // Create pipe
    }
}
```

**Logic**: Creates (n-1) pipes for n commands.

#### 4. Fork and Execute

```c
void ft_execute_not_builtin(t_list *command, t_execution *exe, int i)
{
    exe->total_f++;
    g_global.pid = fork();

    if (g_global.pid == 0)  // Child process
    {
        ft_default_pipes(exe, i);     // Set up pipe connections
        ft_dup_output(exe);            // Handle output redirection
        ft_dup_input(exe);             // Handle input redirection
        ft_close_pipes(exe->pipes, exe); // Close unused pipes

        // Special handling for certain builtins in child
        if (ft_strequals(command->token, "echo"))
            ft_echo(command);
        else if (ft_strequals(command->token, "pwd"))
            ft_pwd();
        else if (ft_strequals(command->token, "env"))
            ft_env(exe);
        else
            ft_execute_fork(command, exe);  // External command

        exit(0);
    }
}
```

**Note**: `echo`, `pwd`, `env` executed in child but don't need `execve()`.

#### 5. Redirection Handling

**Input Redirection** (`<`):
```c
int ft_check_input(t_list *command, t_execution *exe)
{
    // Find '<' token
    // Open file for reading
    // Store in exe->inputfile
    // Remove redirection tokens from command
}
```

**Output Redirection** (`>`, `>>`):
```c
t_list *ft_output(t_list *command, t_execution *exe)
{
    // Find '>' or '>>' token
    // Open file with O_TRUNC or O_APPEND
    // Store in exe->outputfile
    // Remove redirection tokens
}
```

**Here-document** (`<<`):
```c
// Read lines until delimiter
// Store in temporary file or pipe
```

#### 6. Variable Expansion

```c
void ft_clean_quote(t_list *command, t_list *envp)
{
    // Iterate through command tokens
    // Find $ followed by variable name
    // Replace with environment value
    // Handle $? (exit status)
    // Remove quotes
}
```

---

## 🔧 Built-in Commands

### echo

```c
void ft_echo(t_list *command)
{
    int n = 0;  // -n flag
    t_list *node = command->next;

    // Check for -n flag
    while (node && node->token[0] == '-' && has_only_n(node->token))
    {
        n = 1;
        node = node->next;
    }

    // Print arguments
    while (node)
    {
        write(1, node->token, ft_strlen(node->token));
        if (node->next)
            write(1, " ", 1);
        node = node->next;
    }

    if (!n)
        write(1, "\n", 1);
}
```

**Features**:
- `-n`: No trailing newline
- Multiple `-n` flags handled
- Space-separated arguments

### cd

```c
void ft_cd(t_list *command, t_execution *exe)
{
    char newpath[5000];
    int result;

    if (!command->next)
        result = chdir(ft_getenv(exe->envp, "HOME"));
    else if (ft_strequals(command->next->token, "~"))
        result = chdir(ft_getenv(exe->envp, "HOME"));
    else if (ft_strequals(command->next->token, "-"))
        result = chdir(ft_getenv(exe->envp, "OLDPWD"));
    else
        result = chdir(command->next->token);

    if (result == 0)
    {
        ft_change_env(exe, "OLDPWD", ft_getenv(exe->envp, "PWD"));
        getcwd(newpath, 5000);
        ft_change_env(exe, "PWD", newpath);
    }
}
```

**Features**:
- No args → go to `$HOME`
- `~` → go to `$HOME`
- `-` → go to `$OLDPWD`
- Updates `PWD` and `OLDPWD`

### pwd

```c
void ft_pwd(void)
{
    char *result = malloc(2500);
    getcwd(result, 2500);
    write(1, result, ft_strlen(result));
    write(1, "\n", 1);
    free(result);
}
```

### export

```c
void ft_export(t_list *command, t_execution *exe)
{
    // No args → print all variables
    if (!command->next)
        print_export_format(exe->envp);
    else
    {
        // Parse VAR=value
        // Add or update in environment list
    }
}
```

### unset

```c
void ft_unset(t_list *command, t_execution *exe)
{
    // Find variable in environment list
    // Remove node
    ft_del_node(exe->envp, command->next->token);
}
```

### env

```c
void ft_env(t_execution *exe)
{
    t_list *node = exe->envp;

    while (node)
    {
        write(1, node->token, ft_strlen(node->token));
        write(1, "\n", 1);
        node = node->next;
    }
}
```

### exit

```c
void ft_exit(t_list *command)
{
    // Print "exit"
    write(1, "exit\n", 5);

    // Optional: parse exit code
    if (command->next && is_numeric(command->next->token))
        exit(ft_atoi(command->next->token));

    exit(g_global.errnor);
}
```

---

## 📁 Project Structure

```
minishell/
├── 📄 Makefile                  # Build configuration
├── 📂 Subjects/                 # Project documentation
│   ├── en.Minishell.pdf
│   ├── es.Minishell.pdf
│   └── comandos a probar.rtf
├── 📂 includes/                 # Header files
│   ├── builtin.h               # Builtin command prototypes
│   ├── definitions.h           # Type definitions
│   ├── executor.h              # Executor prototypes
│   ├── lexer.h                 # Lexer prototypes
│   ├── list.h                  # List manipulation
│   ├── parser.h                # Parser prototypes
│   ├── syntax.h                # Syntax checker prototypes
│   └── utils.h                 # Utility functions
├── 📂 builtin/                  # Built-in commands (7 files)
│   ├── ft_cd.c
│   ├── ft_echo.c
│   ├── ft_env.c
│   ├── ft_exit.c
│   ├── ft_export.c
│   ├── ft_pwd.c
│   └── ft_unset.c
├── 📂 executor/                 # Execution engine (7 files)
│   ├── ft_executor.c           # Main execution logic
│   ├── ft_executor_utils.c     # Helper functions
│   ├── ft_executor_utils_2.c   # Additional helpers
│   ├── ft_dup.c                # File descriptor duplication
│   ├── ft_input.c              # Input redirection
│   ├── ft_output.c             # Output redirection
│   └── ft_clean_quotes.c       # Quote removal & expansion
├── 📂 lexer/                    # Tokenization (1 file)
│   └── lexer.c
├── 📂 parser/                   # Command parsing (1 file)
│   └── ft_parser.c
├── 📂 syntax/                   # Syntax validation (2 files)
│   ├── ft_syntax.c
│   └── ft_syntaxchecker.c
├── 📂 shel/                     # Main shell loop (1 file)
│   └── ft_shell.c
├── 📂 list/                     # Linked list utilities (10 files)
│   ├── ft_del_node.c
│   ├── ft_freelist.c
│   ├── ft_freelist2d.c
│   ├── ft_get_last_node.c
│   ├── ft_list_size.c
│   ├── ft_list_to_char_table.c
│   ├── ft_lst_new.c
│   ├── ft_lstadd_back.c
│   ├── ft_node_position.c
│   └── ft_words_to_list.c
└── 📂 utils/                    # Utility functions (24 files)
    ├── ft_append_ctostr.c
    ├── ft_append_tostr.c
    ├── ft_atoi.c
    ├── ft_free_chartable.c
    ├── ft_getenv.c
    ├── ft_isalnum.c
    ├── ft_isalpha.c
    ├── ft_isdigit.c
    ├── ft_isspace.c
    ├── ft_itoa.c
    ├── ft_split.c
    ├── ft_str_to_lower.c
    ├── ft_strcat.c
    ├── ft_strcontainstext.c
    ├── ft_strcpy.c
    ├── ft_strcut_toend.c
    ├── ft_strequals.c
    ├── ft_strisalnum.c
    ├── ft_strlen.c
    ├── ft_strstartwith.c
    └── ft_substr.c
```

### Module Summary

| Module | Files | Purpose |
|--------|-------|---------|
| **builtin** | 7 | Built-in command implementations |
| **executor** | 7 | Process execution and redirection |
| **lexer** | 1 | Tokenization |
| **parser** | 1 | Command structuring |
| **syntax** | 2 | Syntax validation |
| **shel** | 1 | Main loop with readline |
| **list** | 10 | Linked list operations |
| **utils** | 24 | String and utility functions |
| **includes** | 8 | Header files |

**Total**: 63 files (11 directories)

---

## 🧪 Testing

### Basic Command Testing

```bash
# Simple commands
minishell$ ls
minishell$ pwd
minishell$ echo test

# With arguments
minishell$ ls -la /tmp
minishell$ echo -n "no newline"

# Environment
minishell$ export VAR=value
minishell$ echo $VAR
value
minishell$ unset VAR
```

### Pipe Testing

```bash
# Single pipe
minishell$ ls | wc -l

# Multiple pipes
minishell$ cat file | grep pattern | sort | uniq

# Complex pipeline
minishell$ ls -la | awk '{print $9}' | grep .c | wc -l
```

### Redirection Testing

```bash
# Input
minishell$ cat < input.txt

# Output
minishell$ echo "test" > output.txt
minishell$ cat output.txt

# Append
minishell$ echo "more" >> output.txt

# Combined
minishell$ cat < input.txt > output.txt

# Here-document
minishell$ cat << EOF
> line1
> line2
> EOF
```

### Quote Testing

```bash
# Single quotes (literal)
minishell$ echo 'Hello $USER'
Hello $USER

# Double quotes (expand)
minishell$ echo "Hello $USER"
Hello ingonzal

# Mixed
minishell$ echo "Hello '$USER'"
Hello 'ingonzal'
```

### Signal Testing

```bash
# Ctrl+C during command
minishell$ sleep 100
^C
minishell$

# Ctrl+C at prompt
minishell$^C
minishell$

# Ctrl+D (EOF)
minishell$ ^D
(shell exits)
```

### Edge Cases

```bash
# Empty command
minishell$

# Only spaces
minishell$

# Unclosed quote (should show error)
minishell$ echo "unclosed

# Invalid pipe
minishell$ | ls

# Multiple redirections
minishell$ echo test > file1 > file2
```

### Test Script

```bash
#!/bin/bash

# Compare minishell vs bash behavior
echo "=== Testing: ls | wc -l ==="
./minishell << EOF
ls | wc -l
exit
EOF

echo "=== Testing: redirections ==="
./minishell << EOF
echo test > /tmp/test1
cat < /tmp/test1
rm /tmp/test1
exit
EOF
```

---

## 💡 What We Learned

Through this project, the team gained understanding of:

- ✅ **Process Management**: `fork()`, `execve()`, `wait()`, `waitpid()`
- ✅ **Pipe Management**: `pipe()`, inter-process communication
- ✅ **File Descriptors**: `dup2()`, redirection, closing unused FDs
- ✅ **Signal Handling**: `signal()`, `sigaction()`, `Ctrl+C/D/\` behavior
- ✅ **Environment Variables**: `getenv()`, `setenv()`, variable expansion
- ✅ **Lexical Analysis**: Tokenization, quote handling
- ✅ **Syntax Parsing**: Building command structures
- ✅ **Memory Management**: Complex allocation patterns, leak prevention
- ✅ **Readline Library**: History, line editing
- ✅ **Team Collaboration**: Code integration, consistent style

### Key Challenges

1. **Quote Handling**: Properly parsing nested quotes and escapes
2. **Pipe Chaining**: Connecting multiple commands with proper FD management
3. **Redirection Precedence**: Handling multiple `<` or `>` in same command
4. **Signal Management**: Correct behavior for `Ctrl+C` in different contexts
5. **Builtin vs External**: Deciding when to fork
6. **Memory Leaks**: Tracking allocations across complex control flow
7. **Here-document**: Implementing `<<` delimiter behavior
8. **Environment Modification**: Builtins that change shell state (`cd`, `export`)
9. **$? Expansion**: Tracking and expanding exit status
10. **Tokenizer Edge Cases**: Handling special characters in quotes

### Design Decisions

**Why linked lists for tokens?**
- Dynamic sizing without reallocation
- Easy insertion/deletion for parsing
- Natural iteration pattern

**Why separate lexer/parser/executor?**
- Clear separation of concerns
- Easier debugging and testing
- Modular code organization

**Why fork for most commands?**
- Isolation of process execution
- Prevents shell corruption on crashes
- Required for `execve()` behavior

**Why execute builtins without fork (except in pipes)?**
- `cd`, `export`, `unset` must modify parent shell
- Forking would lose environment changes

**Why one global variable?**
- Project requirement (max 1 global)
- Used for exit status and signal PID
- Accessible across signal handlers

---

## 📏 Requirements

### Mandatory Features

- ✅ Display prompt when waiting for command
- ✅ Working command history (readline)
- ✅ Search and launch executables (PATH, relative, absolute)
- ✅ 7 builtin commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- ✅ Single quotes `'` (inhibit all interpretation)
- ✅ Double quotes `"` (inhibit all except `$`)
- ✅ Redirections: `<`, `>`, `<<`, `>>`
- ✅ Pipes `|`
- ✅ Environment variable expansion (`$VAR`, `$?`)
- ✅ Signal handling: `Ctrl+C`, `Ctrl+D`, `Ctrl+\`
- ✅ No more than 1 global variable
- ✅ No memory leaks (except readline)

### Not Implemented

- ❌ Backslash `\` escaping
- ❌ Semicolon `;` separator
- ❌ Logical operators `&&`, `||`
- ❌ Wildcards `*`
- ❌ Parenthesis for priorities

---

## 📄 License

MIT License - See LICENSE file for details.

This project is part of the 42 School curriculum. Feel free to use and learn from this code, but please don't copy it for your own 42 projects. Understanding comes from doing it yourself! 🚀

---

## 🔗 Related Projects

This project builds upon:

- **[libft](https://github.com/Z3n42/42_libft)** - Not used (custom utils instead)
- **[get_next_line](https://github.com/Z3n42/get_next_line)** - Not used (readline instead)
- **[ft_printf](https://github.com/Z3n42/ft_printf)** - Not used (printf allowed)

Skills learned here apply to:
- **Philosophers** - Process synchronization
- **Pipex** - Pipe and redirection handling
- Future shell/system projects

---

<div align="center">

**Made with ☕ by [Z3n42](https://github.com/Z3n42) & [ibanezinigo](https://github.com/ibanezinigo)**

*42 Urduliz | Circle 3*

[![42 Profile](https://img.shields.io/badge/42_Intra-ingonzal-000000?style=flat&logo=42&logoColor=white)](https://profile.intra.42.fr/users/ingonzal)
[![42 Profile](https://img.shields.io/badge/42_Intra-iibanez--000000?style=flat&logo=42&logoColor=white)](https://profile.intra.42.fr/users/iibanez-)

</div>
