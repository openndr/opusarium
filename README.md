# Opusarium

[![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)
[![Release: Not released yet](https://img.shields.io/badge/release-Not_released_yet-blue.svg)](https://github.com/openndr/opusarium)

### What is the Opusarium
Opusarium is the C based scheduling framework for high-load tasks.

This framework constructs the isolated computing ecosystem which consisted of the following features.
- Processor reserved scheduler for parallel tasks.
- Customized memory management unit using huge-pages.
- Direct mapped IO memory region for the userspace.

It's compatible with C11 standards and supports Linux kernel which above 4.15.
