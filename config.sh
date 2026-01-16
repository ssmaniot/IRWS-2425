#!/bin/sh
set -eu

if ! git rev-parse --show-toplevel >/dev/null 2>&1; then
  echo "Error: this is not a Git repository." >&2
  exit 1
fi

repo_root="$(git rev-parse --show-toplevel)"
cd "$repo_root"

HOOKS_DIR="githooks"

if [ ! -d "$HOOKS_DIR" ]; then
  echo "Error: '$HOOKS_DIR/' directory not found." >&2
  exit 1
fi

git config --local core.hooksPath "$HOOKS_DIR"

for hook in "$HOOKS_DIR"/*; do
  [ -f "$hook" ] && chmod +x "$hook"
done

echo "Configuration completed."
echo "Git hooks path set to '$HOOKS_DIR/' for this repository."
