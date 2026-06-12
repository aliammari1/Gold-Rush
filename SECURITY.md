# Security Policy

Gold Rush is a local, single-player desktop game written in C. The main
classes of issue worth reporting are **memory-safety bugs** (buffer
overflows, use-after-free, out-of-bounds access) and crashes triggered by
malformed assets.

## Reporting a vulnerability

Please **do not** open a public issue for a security problem. Instead, use
GitHub's private
[security advisory](https://github.com/aliammari1/Gold-Rush/security/advisories/new)
form to report it privately.

Include:

- affected commit or release,
- a description and, if possible, a minimal reproduction,
- your OS, compiler, and SDL version.

We aim to acknowledge reports within a few days. Fixes are validated with
the CI static analysis (cppcheck, CodeQL) and the sanitizer test target
(`make -C tests sanitize`).

## Supported versions

The latest commit on `master` is supported. Older tags receive fixes only
on a best-effort basis.
