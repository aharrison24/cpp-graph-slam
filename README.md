# graph-slam

A toy project for experimenting with modern CMake and C++17 features.

## Using pre-commit hooks
This project uses the [pre-commit](https://pre-commit.com/) tool to perform
linting checks. Install them as follows:

```bash
# Install pre-commit tool
pip3 install pre-commit

cd <src-dir>

# Install pre-commit linters
pre-commit install --install-hooks

# Install git commit linter
pre-commit install --hook-type commit-msg
```
