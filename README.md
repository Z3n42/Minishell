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

[Installation](#%EF%B8%8F-installation) • [Usage](#-usage) • [Features](#-features) • [Architecture](#%EF%B8%8F-architecture) • [Testing](#-testing)

</div>

---

## 📋 Table of Contents

- [About the Project](#-about-the-project)
- [Team](#-team)
- [Installation](#%EF%B8%8F-installation)
- [Usage](#-usage)
- [Features](#-features)
- [Architecture](#%EF%B8%8F-architecture)
- [Implementation Details](#-implementation-details)
- [Built-in Commands](#-built-in-commands)
- [Project Structure](#-project-structure)
- [Testing](#-testing)
- [What We Learned](#-what-we-learned)
- [Requirements](#-requirements)
- [License](#-license)

---

## 🎯 About the Project

**Minishell** is a project that involves creating a simplified UNIX shell from scratch. The goal is to understand how shells work internally - from tokenizing input to executing processes with proper signal handling and redirection management.

### Why Minishell?

<table>
<tr>
<td width="50%" valign="top">

### 🔄 Process Management
- **fork()** for process creation
- **execve()** for command execution
- **wait()/waitpid()** for synchronization
- Child/parent process coordination

</td>
<td width="50%" valign="top">

### 🔗 I/O Management
- **Pipe management** with pipe()
- **File descriptor** manipulation (dup2)
- Redirection handling (`<`, `>`, `>>`, `<<`)
- Inter-process communication

</td>
</tr>
<tr>
<td width="50%" valign="top">

### 🎯 Shell Features
- **7 built-in commands** implementation
- **Environment variable** expansion (`$VAR`, `$?`)
- Quote handling (single `'`, double `"`)
- Signal management (SIGINT, SIGQUIT)

</td>
<td width="50%" valign="top">

### 🏗️ Software Architecture
- **Lexical analysis** and tokenization
- **Syntax parsing** and validation
- **Modular pipeline** architecture
- Clean code organization (63 files)

</td>
</tr>
</table>

The challenge is to replicate bash behavior while maintaining clean, norm-compliant code.

---

## 👥 Team

This project was developed collaboratively by:

<table>
<tr>
<th>Developer</th>
<th>GitHub</th>
<th>42 Login</th>
</tr>
<tr>
<td><b>Z3n42</b></td>
<td><a href="https://github.com/Z3n42">@Z3n42</a></td>
<td>ingonzal</td>
</tr>
<tr>
<td><b>ibanezinigo</b></td>
<td><a href="https://github.com/ibanezinigo">@ibanezinigo</a></td>
<td>iibanez-</td>
</tr>
</table>

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

After running `make`, you'll have the `minishell` executable ready to use.

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

Or press `Ctrl+D` (EOF).

---

## ✨ Features

### Core Functionality

<table>
<tr>
<td width="50%" valign="top">

#### 1. Command Execution

```bash
# Search in PATH
minishell$ ls -la

# Absolute path
minishell$ /bin/echo "Direct"

# Relative path
minishell$ ./minishell
```

**Implementation**: PATH parsing, executable search, execve() wrapper.

</td>
<td width="50%" valign="top">

#### 2. Pipes

```bash
# Single pipe
minishell$ cat file | grep pattern

# Multiple pipes
minishell$ ls | grep .c | wc -l
```

**Implementation**: Creates pipes between processes, redirecting stdout/stdin.

</td>
</tr>
<tr>
<td width="50%" valign="top">

#### 3. Redirections

```bash
# Input
minishell$ cat < input.txt

# Output (truncate)
minishell$ echo "test" > output.txt

# Append
minishell$ echo "more" >> output.txt

# Here-document
minishell$ cat << EOF
> line 1
> EOF
```

**Implementation**: `open()`, `dup2()`, file descriptor management.

</td>
<td width="50%" valign="top">

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

**Implementation**: Environment list, `$` expansion, `$?` tracking.

</td>
</tr>
<tr>
<td width="50%" valign="top">

#### 5. Quotes

```bash
# Single (literal)
minishell$ echo 'Hello $USER'
Hello $USER

# Double (expand)
minishell$ echo "Hello $USER"
Hello ingonzal
```

**Implementation**: Quote state tracking, selective expansion.

</td>
<td width="50%" valign="top">

#### 6. Signals

- **Ctrl+C**: Interrupt, new prompt
- **Ctrl+D**: EOF, exit shell
- **Ctrl+\**: Ignored

**Implementation**: `signal()`, `sigaction()`, handler registration.

</td>
</tr>
</table>

### Built-in Commands

| Command | Description | Options | Execution |
|---------|-------------|---------|-----------|
| `echo` | Print arguments | `-n` (no newline) | Child (in pipes) / Parent |
| `cd` | Change directory | `~`, `-`, paths | Parent only |
| `pwd` | Print working dir | None | Child (in pipes) / Parent |
| `export` | Set env variable | None | Parent only |
| `unset` | Remove env variable | None | Parent only |
| `env` | Print environment | None | Child (in pipes) / Parent |
| `exit` | Exit shell | Optional code | Parent only |

---

## 🏗️ Architecture

The implementation follows a **modular pipeline architecture**:

```
┌─────────────────────────────────────────────────────────────┐
│                   Minishell Pipeline                         │
└─────────────────────────────────────────────────────────────┘
                           │
                           ▼
                  ┌────────────────┐
                  │  1. readline() │
                  │  Get user input │
                  └────────────────┘
                           │
                           ▼
                  ┌────────────────┐
                  │  2. ft_lexer() │
                  │  Tokenize input │
                  └────────────────┘
                           │
              ┌────────────┴────────────┐
              │ Tokens (linked list)    │
              │ ["ls"] -> ["-la"] -> .. │
              └────────────┬────────────┘
                           ▼
                 ┌─────────────────┐
                 │ 3. ft_parser()  │
                 │ Build commands  │
                 └─────────────────┘
                           │
              ┌────────────┴────────────┐
              │ Command array           │
              │ [["ls","-la"], ...]     │
              └────────────┬────────────┘
                           ▼
                 ┌─────────────────┐
                 │ 4. ft_syntax()  │
                 │ Validate syntax │
                 └─────────────────┘
                           │
                    Valid? ├─No─→ Error message
                           │
                          Yes
                           ▼
                ┌──────────────────┐
                │ 5. ft_execute()  │
                │ Execute commands │
                └──────────────────┘
                           │
        ┌──────────────────┼──────────────────┐
        ▼                  ▼                  ▼
   Create pipes      Handle forks      Wait processes
```

### Module Breakdown

<details>
<summary><b>1. Lexer (Tokenization)</b></summary>

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
        // Skip leading whitespace
        // Extract token with ft_reduce()
        // Handle quote state
        // Add to linked list
        // Move to next token
    }

    return (start);
}
```

**Quote Handling Algorithm**:
```c
void ft_quote(char *str, int *i, char *quote, char *token)
{
    while ((ft_isspace(str[*i]) == 0 && str[*i] != '|' 
        && str[*i] != '<' && str[*i] != '>' && str[*i] != ';' 
        && str[*i] != '&' && str[*i] != '\0') || *quote != '\0')
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

</details>

<details>
<summary><b>2. Parser (Command Structuring)</b></summary>

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
- Returns NULL-terminated array

**Implementation Logic**:
1. Count number of pipes → determine array size
2. Allocate command array
3. Iterate through tokens, split on `|`
4. Build linked list for each command

</details>

<details>
<summary><b>3. Syntax Checker</b></summary>

**Location**: `syntax/ft_syntax.c`, `syntax/ft_syntaxchecker.c`

**Function**: `int ft_syntax(t_list *lexer)`

**Purpose**: Validates syntax before execution.

**Checks Performed**:
- Unclosed quotes (single/double)
- Invalid pipe placement (start/end, consecutive)
- Invalid redirection syntax
- Empty commands
- Missing filenames for redirections

**Return Values**:
- `0`: Valid syntax
- `1`: Syntax error detected

</details>

<details>
<summary><b>4. Executor (Execution Engine)</b></summary>

**Location**: `executor/ft_executor.c`

**Function**: `int ft_execute(t_list **lcommands, t_execution *exe)`

**Purpose**: Executes parsed commands with pipes and redirections.

**Execution Process**:
```c
1. Create pipes between commands (n-1 pipes for n commands)
2. For each command:
   - Handle redirections (input/output)
   - Check if builtin command
   - If builtin (non-piped): execute in parent
   - If external or piped builtin: fork and execute
3. Close all pipe file descriptors in parent
4. Wait for all child processes
5. Clean up allocated memory
```

**Fork Decision Table**:

| Command Type | Alone | In Pipeline |
|--------------|-------|-------------|
| `cd`, `export`, `unset`, `exit` | Parent (no fork) | N/A (error/parent) |
| `echo`, `pwd`, `env` | Parent (no fork) | Child (fork) |
| External commands | Child (fork) | Child (fork) |

</details>

---

## 💻 Implementation Details

### Data Structures

<details>
<summary><b>t_list - Token/Command Node</b></summary>

```c
typedef struct s_list
{
    char         *token;    // Command or argument string
    struct s_list *next;    // Pointer to next token
}   t_list;
```

**Usage**: 
- Linked list for tokens from lexer
- Linked list for command arguments in parser
- Dynamic sizing without reallocation

**Operations**:
- `ft_lst_new()`: Create new node
- `ft_lstadd_back()`: Append to list
- `ft_freelist()`: Deallocate entire list

</details>

<details>
<summary><b>t_execution - Execution Context</b></summary>

```c
typedef struct s_execution
{
    t_list  *envp;          // Environment variables (linked list)
    int     **pipes;        // Array of pipe FD pairs
    int     *pids;          // Array of child process IDs
    int     total_f;        // Total fork count
    int     in_redi;        // Input redirection type
    int     redi;           // Output redirection type
    char    *inputfile;     // Input filename
    char    *inputpath;     // Input file path
    char    *outputfile;    // Output filename
}   t_execution;
```

**Purpose**: Maintains state across command execution.

**Key Fields**:
- `envp`: Linked list of "VAR=value" strings
- `pipes`: 2D array, each row is [read_fd, write_fd]
- `total_f`: Tracks number of forks for waitpid loop
- `in_redi`/`redi`: Flags for redirection types

</details>

<details>
<summary><b>g_global - Global State</b></summary>

```c
typedef struct s_global
{
    int errnor;     // Last exit status ($?)
    int pid;        // Current process PID
}   t_global;

t_global g_global;  // Only global variable allowed
```

**Purpose**: 
- Track exit status for `$?` expansion
- Store PID for signal handlers

**Note**: Project allows maximum 1 global variable.

</details>

### Key Algorithms

<details>
<summary><b>Pipe Creation and Management</b></summary>

```c
void ft_create_pipes(t_list **lcommands, t_execution *exe)
{
    int command_count = 0;

    // Count commands
    while (lcommands[command_count])
        command_count++;

    // Allocate pipe array (n-1 pipes for n commands)
    exe->pipes = malloc(sizeof(int *) * (command_count - 1));

    // Create each pipe
    for (int i = 0; i < command_count - 1; i++)
    {
        exe->pipes[i] = malloc(sizeof(int) * 2);
        pipe(exe->pipes[i]);  // pipes[i][0] = read, pipes[i][1] = write
    }
}
```

**Pipe Layout for 3 Commands** (cmd1 | cmd2 | cmd3):
```
                pipe[0]              pipe[1]
cmd1 stdout → [write] → [read] cmd2 stdout → [write] → [read] cmd3
```

</details>

<details>
<summary><b>Fork and Execute Logic</b></summary>

```c
void ft_execute_not_builtin(t_list *command, t_execution *exe, int i)
{
    exe->total_f++;
    g_global.pid = fork();

    if (g_global.pid == 0)  // Child process
    {
        ft_default_pipes(exe, i);     // Connect pipes
        ft_dup_output(exe);            // Handle > or >>
        ft_dup_input(exe);             // Handle <
        ft_close_pipes(exe->pipes, exe); // Close unused FDs

        // Some builtins execute in child when piped
        if (ft_strequals(command->token, "echo"))
            ft_echo(command);
        else if (ft_strequals(command->token, "pwd"))
            ft_pwd();
        else if (ft_strequals(command->token, "env"))
            ft_env(exe);
        else
            ft_execute_fork(command, exe);  // execve() for external

        exit(0);
    }
    // Parent continues to next command
}
```

**Why some builtins in child?**
- `echo`, `pwd`, `env`: read-only, safe in child
- `cd`, `export`, `unset`: modify parent state, must run in parent

</details>

<details>
<summary><b>Pipe Connection (ft_default_pipes)</b></summary>

```c
void ft_default_pipes(t_execution *exe, int command_index)
{
    // If not first command: read from previous pipe
    if (command_index > 0)
        dup2(exe->pipes[command_index - 1][0], STDIN_FILENO);

    // If not last command: write to next pipe
    if (command_index < total_commands - 1)
        dup2(exe->pipes[command_index][1], STDOUT_FILENO);
}
```

**Example**: `cmd1 | cmd2 | cmd3`
- cmd1: stdout → pipe[0][1]
- cmd2: stdin ← pipe[0][0], stdout → pipe[1][1]
- cmd3: stdin ← pipe[1][0]

</details>

<details>
<summary><b>Redirection Handling</b></summary>

**Input Redirection** (`<`):
```c
int ft_check_input(t_list *command, t_execution *exe)
{
    t_list *node = command;

    // Find '<' token
    while (node && !ft_strequals(node->token, "<"))
        node = node->next;

    if (node && node->next)
    {
        exe->inputfile = node->next->token;
        int fd = open(exe->inputfile, O_RDONLY);

        if (fd < 0)
            return (-1);  // File error

        // Remove '<' and filename from command
        ft_del_node(command, "<");
        ft_del_node(command, exe->inputfile);
    }

    return (0);
}

void ft_dup_input(t_execution *exe)
{
    if (exe->inputfile)
    {
        int fd = open(exe->inputfile, O_RDONLY);
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
}
```

**Output Redirection** (`>`, `>>`):
```c
t_list *ft_output(t_list *command, t_execution *exe)
{
    t_list *node = command;

    // Find '>' or '>>' token
    while (node)
    {
        if (ft_strequals(node->token, ">"))
            exe->redi = O_TRUNC;
        else if (ft_strequals(node->token, ">>"))
            exe->redi = O_APPEND;

        if (exe->redi && node->next)
        {
            exe->outputfile = node->next->token;
            // Remove redirection tokens
            ft_del_node(command, node->token);
            ft_del_node(command, exe->outputfile);
            break;
        }
        node = node->next;
    }

    return (command);
}

void ft_dup_output(t_execution *exe)
{
    if (exe->outputfile)
    {
        int fd = open(exe->outputfile, O_WRONLY | O_CREAT | exe->redi, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}
```

</details>

<details>
<summary><b>Variable Expansion</b></summary>

```c
void ft_clean_quote(t_list *command, t_list *envp)
{
    t_list *node = command;

    while (node)
    {
        char *token = node->token;
        char *result = malloc(5000);
        int in_single_quote = 0;
        int i = 0, j = 0;

        while (token[i])
        {
            // Handle quote state
            if (token[i] == '\'' && !in_double_quote)
                in_single_quote = !in_single_quote;

            // Expand $ if not in single quotes
            if (token[i] == '$' && !in_single_quote)
            {
                // Handle $?
                if (token[i + 1] == '?')
                {
                    char *status = ft_itoa(g_global.errnor);
                    ft_strcat(result, status);
                    free(status);
                    i += 2;
                    continue;
                }

                // Extract variable name
                char *varname = extract_varname(&token[i + 1]);
                char *value = ft_getenv(envp, varname);

                if (value)
                    ft_strcat(result, value);

                i += ft_strlen(varname) + 1;
                free(varname);
            }
            else if (token[i] != '\'' && token[i] != '"')
                result[j++] = token[i++];
            else
                i++;  // Skip quotes
        }

        result[j] = '\0';
        free(node->token);
        node->token = result;
        node = node->next;
    }
}
```

**Expansion Rules**:
- `$VAR` → value from environment
- `$?` → last exit status (g_global.errnor)
- Inside `'` → no expansion
- Inside `"` → expand $VAR and $?

</details>

---

## 🔧 Built-in Commands

<details>
<summary><b>echo - Print Arguments</b></summary>

```c
void ft_echo(t_list *command)
{
    int n = 0;  // -n flag status
    t_list *node = command->next;

    // Check for -n flag(s)
    while (node && node->token[0] == '-' && has_only_n(node->token))
    {
        n = 1;
        node = node->next;
    }

    // Print arguments with spaces
    while (node)
    {
        write(1, node->token, ft_strlen(node->token));
        if (node->next)
            write(1, " ", 1);
        node = node->next;
    }

    // Print newline unless -n
    if (!n)
        write(1, "\n", 1);
}
```

**Features**:
- `-n`: No trailing newline
- Multiple `-n` flags handled correctly
- Space-separated arguments

</details>

<details>
<summary><b>cd - Change Directory</b></summary>

```c
void ft_cd(t_list *command, t_execution *exe)
{
    char newpath[5000];
    int result;

    // No arguments → go to $HOME
    if (!command->next)
        result = chdir(ft_getenv(exe->envp, "HOME"));

    // ~ → go to $HOME
    else if (ft_strequals(command->next->token, "~"))
        result = chdir(ft_getenv(exe->envp, "HOME"));

    // - → go to $OLDPWD
    else if (ft_strequals(command->next->token, "-"))
        result = chdir(ft_getenv(exe->envp, "OLDPWD"));

    // Relative or absolute path
    else
        result = chdir(command->next->token);

    // Update PWD and OLDPWD if successful
    if (result == 0)
    {
        ft_change_env(exe, "OLDPWD", ft_getenv(exe->envp, "PWD"));
        getcwd(newpath, 5000);
        ft_change_env(exe, "PWD", newpath);
    }
    else
    {
        // Print error message
        write(2, "cd: ", 4);
        write(2, command->next->token, ft_strlen(command->next->token));
        write(2, ": No such file or directory\n", 29);
    }
}
```

**Features**:
- No args / `~` → `$HOME`
- `-` → `$OLDPWD`
- Updates `PWD` and `OLDPWD`
- Error handling for invalid paths

</details>

<details>
<summary><b>pwd - Print Working Directory</b></summary>

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

**Simple implementation**: Uses `getcwd()` system call.

</details>

<details>
<summary><b>export - Set Environment Variable</b></summary>

```c
void ft_export(t_list *command, t_execution *exe)
{
    // No arguments → print all variables in export format
    if (!command->next)
    {
        t_list *node = exe->envp;
        while (node)
        {
            write(1, "declare -x ", 11);
            write(1, node->token, ft_strlen(node->token));
            write(1, "\n", 1);
            node = node->next;
        }
    }
    else
    {
        // Parse VAR=value
        char *var_value = command->next->token;
        char *equals = ft_strchr(var_value, '=');

        if (equals)
        {
            // Split into var and value
            *equals = '\0';
            char *var = var_value;
            char *value = equals + 1;

            // Update or add to environment
            ft_change_env(exe, var, value);
        }
    }
}
```

**Features**:
- No args: print all in `declare -x VAR=value` format
- With args: set variable
- Updates existing or adds new

</details>

<details>
<summary><b>unset - Remove Environment Variable</b></summary>

```c
void ft_unset(t_list *command, t_execution *exe)
{
    if (command->next)
    {
        // Find and remove node from environment list
        ft_del_node(exe->envp, command->next->token);
    }
}
```

**Simple implementation**: Removes node from linked list.

</details>

<details>
<summary><b>env - Print Environment</b></summary>

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

**Output format**: `VAR=value\n` for each variable.

</details>

<details>
<summary><b>exit - Exit Shell</b></summary>

```c
void ft_exit(t_list *command)
{
    // Print "exit" message
    write(1, "exit\n", 5);

    // Optional: parse exit code argument
    if (command->next && is_numeric(command->next->token))
        exit(ft_atoi(command->next->token));

    // Default: exit with last status
    exit(g_global.errnor);
}
```

**Features**:
- Prints "exit" message
- Optional numeric argument
- Defaults to last exit status

</details>

---

## 📁 Project Structure

```
minishell/
├── 📄 Makefile                  # Build configuration
├── 📂 Subjects/                 # Project documentation (3 files)
│   ├── en.Minishell.pdf
│   ├── es.Minishell.pdf
│   └── comandos a probar.rtf
│
├── 📂 includes/                 # Header files (8 files)
│   ├── builtin.h               # Builtin command prototypes
│   ├── definitions.h           # Type definitions (t_list, t_execution, g_global)
│   ├── executor.h              # Executor prototypes
│   ├── lexer.h                 # Lexer prototypes
│   ├── list.h                  # List manipulation functions
│   ├── parser.h                # Parser prototypes
│   ├── syntax.h                # Syntax checker prototypes
│   └── utils.h                 # Utility functions
│
├── 📂 builtin/                  # Built-in commands (7 files)
│   ├── ft_cd.c                 # Change directory implementation
│   ├── ft_echo.c               # Echo with -n flag
│   ├── ft_env.c                # Print environment
│   ├── ft_exit.c               # Exit shell
│   ├── ft_export.c             # Set environment variable
│   ├── ft_pwd.c                # Print working directory
│   └── ft_unset.c              # Remove environment variable
│
├── 📂 executor/                 # Execution engine (7 files)
│   ├── ft_executor.c           # Main execution logic, process management
│   ├── ft_executor_utils.c     # Helper functions for execution
│   ├── ft_executor_utils_2.c   # Additional execution helpers
│   ├── ft_dup.c                # File descriptor duplication (dup2 wrappers)
│   ├── ft_input.c              # Input redirection handling (<, <<)
│   ├── ft_output.c             # Output redirection handling (>, >>)
│   └── ft_clean_quotes.c       # Quote removal & variable expansion
│
├── 📂 lexer/                    # Tokenization (1 file)
│   └── lexer.c                 # Token extraction, quote handling
│
├── 📂 parser/                   # Command parsing (1 file)
│   └── ft_parser.c             # Pipe-separated command structuring
│
├── 📂 syntax/                   # Syntax validation (2 files)
│   ├── ft_syntax.c             # Main syntax checker
│   └── ft_syntaxchecker.c      # Specific syntax rules
│
├── 📂 shel/                     # Main shell loop (1 file)
│   └── ft_shell.c              # readline loop, signal setup
│
├── 📂 list/                     # Linked list utilities (10 files)
│   ├── ft_del_node.c           # Delete node by value
│   ├── ft_freelist.c           # Deallocate entire list
│   ├── ft_freelist2d.c         # Deallocate 2D array of lists
│   ├── ft_get_last_node.c      # Get tail of list
│   ├── ft_list_size.c          # Count nodes
│   ├── ft_list_to_char_table.c # Convert list to array
│   ├── ft_lst_new.c            # Create new node
│   ├── ft_lstadd_back.c        # Append to end
│   ├── ft_node_position.c      # Find node index
│   └── ft_words_to_list.c      # Split string to list
│
└── 📂 utils/                    # Utility functions (24 files)
    ├── ft_append_ctostr.c      # Append char to string
    ├── ft_append_tostr.c       # Append string to string
    ├── ft_atoi.c               # String to integer
    ├── ft_free_chartable.c     # Free 2D char array
    ├── ft_getenv.c             # Get environment variable
    ├── ft_isalnum.c            # Check alphanumeric
    ├── ft_isalpha.c            # Check alphabetic
    ├── ft_isdigit.c            # Check digit
    ├── ft_isspace.c            # Check whitespace
    ├── ft_itoa.c               # Integer to string
    ├── ft_split.c              # Split string by delimiter
    ├── ft_str_to_lower.c       # Convert to lowercase
    ├── ft_strcat.c             # Concatenate strings
    ├── ft_strcontainstext.c    # Check if non-whitespace
    ├── ft_strcpy.c             # Copy string
    ├── ft_strcut_toend.c       # Substring from index
    ├── ft_strequals.c          # Compare strings
    ├── ft_strisalnum.c         # Check all alphanumeric
    ├── ft_strlen.c             # String length
    ├── ft_strstartwith.c       # Check prefix
    └── ft_substr.c             # Extract substring
```

### Module Summary

<table>
<tr>
<th>Module</th>
<th>Files</th>
<th>Purpose</th>
</tr>
<tr>
<td><b>builtin</b></td>
<td>7</td>
<td>Built-in command implementations (echo, cd, pwd, export, unset, env, exit)</td>
</tr>
<tr>
<td><b>executor</b></td>
<td>7</td>
<td>Process execution, fork management, pipe setup, redirections</td>
</tr>
<tr>
<td><b>lexer</b></td>
<td>1</td>
<td>Tokenization with quote and special character handling</td>
</tr>
<tr>
<td><b>parser</b></td>
<td>1</td>
<td>Command array construction from tokens (pipe separation)</td>
</tr>
<tr>
<td><b>syntax</b></td>
<td>2</td>
<td>Syntax validation (quotes, pipes, redirections)</td>
</tr>
<tr>
<td><b>shel</b></td>
<td>1</td>
<td>Main loop with readline, signal handlers</td>
</tr>
<tr>
<td><b>list</b></td>
<td>10</td>
<td>Linked list operations (create, add, delete, iterate)</td>
</tr>
<tr>
<td><b>utils</b></td>
<td>24</td>
<td>String manipulation and utility functions</td>
</tr>
<tr>
<td><b>includes</b></td>
<td>8</td>
<td>Header files with prototypes and definitions</td>
</tr>
</table>

**Total**: 63 files across 11 directories

---

## 🧪 Testing

### Test Categories

<table>
<tr>
<th>Category</th>
<th>Test Cases</th>
<th>Expected Behavior</th>
</tr>
<tr>
<td><b>Simple Commands</b></td>
<td><code>ls</code>, <code>pwd</code>, <code>echo test</code></td>
<td>Execute and display output</td>
</tr>
<tr>
<td><b>Commands with Args</b></td>
<td><code>ls -la /tmp</code>, <code>echo -n "test"</code></td>
<td>Parse and pass arguments correctly</td>
</tr>
<tr>
<td><b>Pipes (Single)</b></td>
<td><code>ls | wc -l</code></td>
<td>Connect stdout to stdin</td>
</tr>
<tr>
<td><b>Pipes (Multiple)</b></td>
<td><code>cat file | grep pat | sort | uniq</code></td>
<td>Chain multiple pipes</td>
</tr>
<tr>
<td><b>Input Redir</b></td>
<td><code>cat < input.txt</code></td>
<td>Read from file</td>
</tr>
<tr>
<td><b>Output Redir</b></td>
<td><code>echo test > out.txt</code></td>
<td>Write to file (truncate)</td>
</tr>
<tr>
<td><b>Append Redir</b></td>
<td><code>echo more >> out.txt</code></td>
<td>Append to file</td>
</tr>
<tr>
<td><b>Here-document</b></td>
<td><code>cat << EOF</code></td>
<td>Read until delimiter</td>
</tr>
<tr>
<td><b>Environment</b></td>
<td><code>echo $HOME</code>, <code>export VAR=val</code></td>
<td>Expand and set variables</td>
</tr>
<tr>
<td><b>Quotes</b></td>
<td><code>echo 'test'</code>, <code>echo "test $USER"</code></td>
<td>Literal vs expansion</td>
</tr>
<tr>
<td><b>Signals</b></td>
<td>Ctrl+C, Ctrl+D, Ctrl+\</td>
<td>Proper handling</td>
</tr>
<tr>
<td><b>Exit Status</b></td>
<td><code>ls && echo $?</code></td>
<td>Track last exit code</td>
</tr>
</table>

### Detailed Test Examples

<details>
<summary><b>Basic Command Testing</b></summary>

```bash
# Simple commands
minishell$ ls
minishell$ pwd
minishell$ echo test

# With arguments
minishell$ ls -la /tmp
minishell$ echo -n "no newline"

# PATH resolution
minishell$ cat file.txt
minishell$ /bin/ls
```

</details>

<details>
<summary><b>Pipe Testing</b></summary>

```bash
# Single pipe
minishell$ ls | wc -l

# Multiple pipes
minishell$ cat file | grep pattern | sort | uniq

# Complex pipeline
minishell$ ls -la | awk '{print $9}' | grep .c | wc -l

# Builtin in pipe
minishell$ echo test | cat
minishell$ pwd | cat
```

</details>

<details>
<summary><b>Redirection Testing</b></summary>

```bash
# Input
minishell$ cat < input.txt

# Output (truncate)
minishell$ echo "test" > output.txt
minishell$ cat output.txt
test

# Append
minishell$ echo "more" >> output.txt
minishell$ cat output.txt
test
more

# Combined
minishell$ cat < input.txt > output.txt

# Here-document
minishell$ cat << EOF
> line1
> line2
> EOF
line1
line2
```

</details>

<details>
<summary><b>Environment Variable Testing</b></summary>

```bash
# Expansion
minishell$ echo $HOME
/home/user

# Setting
minishell$ export VAR=value
minishell$ echo $VAR
value

# Unsetting
minishell$ unset VAR
minishell$ echo $VAR

(empty)

# Exit status
minishell$ ls /nonexistent
ls: cannot access '/nonexistent': No such file or directory
minishell$ echo $?
2
```

</details>

<details>
<summary><b>Quote Testing</b></summary>

```bash
# Single quotes (literal)
minishell$ echo 'Hello $USER'
Hello $USER

# Double quotes (expand variables)
minishell$ echo "Hello $USER"
Hello ingonzal

# Mixed
minishell$ echo "Hello '$USER'"
Hello 'ingonzal'

# Spaces preserved
minishell$ echo "Hello    World"
Hello    World
```

</details>

<details>
<summary><b>Signal Testing</b></summary>

```bash
# Ctrl+C during command
minishell$ sleep 100
^C
minishell$

# Ctrl+C at prompt
minishell$ ^C
minishell$

# Ctrl+D (EOF) to exit
minishell$ ^D
(shell exits)

# Ctrl+\ (should be ignored)
minishell$ ^\
minishell$
```

</details>

<details>
<summary><b>Edge Cases and Error Handling</b></summary>

```bash
# Empty command
minishell$ 
minishell$

# Only spaces
minishell$     
minishell$

# Unclosed quote (should show error)
minishell$ echo "unclosed
Error: unclosed quote

# Invalid pipe
minishell$ | ls
Error: invalid pipe syntax

# Multiple redirections
minishell$ echo test > file1 > file2
(overwrites file2, bash behavior)

# Invalid file
minishell$ cat < nonexistent.txt
cat: nonexistent.txt: No such file or directory

# Permission error
minishell$ cat < /etc/shadow
cat: /etc/shadow: Permission denied
```

</details>

### Comparison Test Script

```bash
#!/bin/bash

# Compare minishell vs bash behavior

echo "=== Test 1: Basic commands ==="
echo "ls | wc -l" | ./minishell
echo "ls | wc -l" | bash

echo "\n=== Test 2: Redirections ==="
echo "echo test > /tmp/test1 && cat < /tmp/test1" | ./minishell
echo "echo test > /tmp/test2 && cat < /tmp/test2" | bash

echo "\n=== Test 3: Environment ==="
echo "export VAR=value && echo \$VAR" | ./minishell
echo "export VAR=value && echo \$VAR" | bash

echo "\n=== Test 4: Quotes ==="
echo "echo 'single quote \$USER'" | ./minishell
echo "echo 'single quote \$USER'" | bash
```

---

## 💡 What We Learned

Through this project, the team gained understanding of:

- ✅ **Process Management**: `fork()`, `execve()`, `wait()`, `waitpid()`, process lifecycle
- ✅ **Pipe Management**: `pipe()`, inter-process communication, FD chaining
- ✅ **File Descriptors**: `dup2()`, redirection, closing unused FDs to prevent leaks
- ✅ **Signal Handling**: `signal()`, `sigaction()`, proper `Ctrl+C/D/\` behavior
- ✅ **Environment Variables**: `getenv()`, `setenv()`, variable expansion, `$?` tracking
- ✅ **Lexical Analysis**: Tokenization, quote state machines, special character detection
- ✅ **Syntax Parsing**: Building command structures from flat token lists
- ✅ **Memory Management**: Complex allocation patterns, preventing leaks in error paths
- ✅ **Readline Library**: History management, line editing capabilities
- ✅ **Team Collaboration**: Code integration strategies, consistent style, git workflow

### Key Challenges

<table>
<tr>
<th>Challenge</th>
<th>Solution Implemented</th>
</tr>
<tr>
<td><b>Quote Handling</b></td>
<td>State machine in lexer: track quote type, continue token extraction inside quotes</td>
</tr>
<tr>
<td><b>Pipe Chaining</b></td>
<td>Create n-1 pipes for n commands, use dup2() to connect stdin/stdout, close all in parent</td>
</tr>
<tr>
<td><b>Redirection Precedence</b></td>
<td>Process redirections left-to-right, last one wins (bash behavior)</td>
</tr>
<tr>
<td><b>Signal Management</b></td>
<td>Different handlers for parent (prompt) vs child (running command)</td>
</tr>
<tr>
<td><b>Builtin vs External</b></td>
<td>Execute state-modifying builtins (cd, export) in parent, others can fork</td>
</tr>
<tr>
<td><b>Memory Leaks</b></td>
<td>Systematic free() in error paths, valgrind testing, cleanup functions</td>
</tr>
<tr>
<td><b>Here-document</b></td>
<td>Read lines until delimiter matches, store in temp file or pipe</td>
</tr>
<tr>
<td><b>Environment Mod</b></td>
<td>Maintain linked list of VAR=value strings, modify in place for cd/export</td>
</tr>
<tr>
<td><b>$? Expansion</b></td>
<td>Store in global, update after each command, replace during variable expansion</td>
</tr>
<tr>
<td><b>Tokenizer Edge Cases</b></td>
<td>Handle special chars inside quotes, consecutive delimiters, empty tokens</td>
</tr>
</table>

### Design Decisions

**Why linked lists for tokens?**
- Dynamic sizing without reallocation
- Easy insertion/deletion during parsing
- Natural iteration pattern with next pointers

**Why separate lexer/parser/executor modules?**
- Clear separation of concerns
- Easier debugging (isolate where error occurs)
- Modular testing
- Clean code organization

**Why fork for most commands?**
- Isolation: child crashes don't kill shell
- Required for `execve()` (replaces process image)
- Separate process groups for signal handling

**Why execute some builtins without fork?**
- `cd`, `export`, `unset`: must modify parent shell state
- Forking would lose environment changes in child

**Why only one global variable?**
- Project requirement (42 norm: max 1 global)
- Used for exit status and current PID
- Accessible from signal handlers

**Why array of pipes instead of single pipe?**
- Multiple commands need multiple pipes
- `cmd1 | cmd2 | cmd3` requires 2 pipes
- Array structure: `pipes[i][0]` = read, `pipes[i][1]` = write

---

## 📏 Requirements

### Mandatory Features

- ✅ Display prompt when waiting for command
- ✅ Working command history (readline library)
- ✅ Search and launch executables (PATH, relative, absolute paths)
- ✅ 7 builtin commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- ✅ Single quotes `'` (inhibit all interpretation)
- ✅ Double quotes `"` (inhibit all except `$`)
- ✅ Redirections: `<`, `>`, `<<`, `>>`
- ✅ Pipes `|` (unlimited chaining)
- ✅ Environment variable expansion (`$VAR`, `$?`)
- ✅ Signal handling: `Ctrl+C`, `Ctrl+D`, `Ctrl+\`
- ✅ No more than 1 global variable
- ✅ No memory leaks (except readline-related)

### Not Implemented

- ❌ Backslash `\` escaping
- ❌ Semicolon `;` separator
- ❌ Logical operators `&&`, `||`
- ❌ Wildcards `*`
- ❌ Parenthesis for command grouping

### Allowed Functions

- `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`
- `malloc`, `free`, `write`, `open`, `read`, `close`
- `fork`, `wait`, `waitpid`, `wait3`, `wait4`
- `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`
- `exit`, `getcwd`, `chdir`
- `stat`, `lstat`, `fstat`, `unlink`
- `execve`, `dup`, `dup2`, `pipe`
- `opendir`, `readdir`, `closedir`
- `strerror`, `perror`
- `isatty`, `ttyname`, `ttyslot`, `ioctl`
- `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

---

## 📄 License

MIT License - See LICENSE file for details.

This project is part of the 42 School curriculum. Feel free to use and learn from this code, but please don't copy it for your own 42 projects. Understanding comes from doing it yourself! 🚀

---

## 🔗 Related Projects

This project builds upon:

- **[libft](https://github.com/Z3n42/42_libft)** - Not used (custom utils implemented)
- **[get_next_line](https://github.com/Z3n42/get_next_line)** - Not used (readline used instead)
- **[ft_printf](https://github.com/Z3n42/ft_printf)** - Not used (printf allowed)

Skills learned here apply to:
- **Philosophers** - Process synchronization and management
- **Pipex** - Pipe and redirection handling
- Future shell and system-level projects

---

<div align="center">

**Made with ☕ by [Z3n42](https://github.com/Z3n42) & [ibanezinigo](https://github.com/ibanezinigo)**

*42 Urduliz | Circle 3*

[![42 Profile](https://img.shields.io/badge/42_Intra-ingonzal-000000?style=flat&logo=42&logoColor=white)](https://profile.intra.42.fr/users/ingonzal)
[![42 Profile](https://img.shields.io/badge/42_Intra-iibanez--000000?style=flat&logo=42&logoColor=white)](https://profile.intra.42.fr/users/iibanez-)

</div>
