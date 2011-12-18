#! /bin/sh

prince                                \
  doc/html/index.html                 \
  doc/html/task-install.html          \
  doc/html/task-login.html            \
  doc/html/task-import.html           \
  doc/html/task-usages.html           \
  doc/html/task-interval-search.html  \
  doc/html/task-db-setup.html         \
  doc/html/task-user-adm.html         \
  doc/html/iface-base.html            \
  doc/html/iface-import.html          \
  doc/html/iface-measure.html         \
  doc/html/iface-division.html        \
  doc/html/iface-system.html          \
  doc/html/iface-measure-adm.html     \
  doc/html/iface-system-adm.html      \
  doc/html/iface-submission.html      \
  doc/html/iface-planned.html         \
  doc/html/iface-usages.html          \
  doc/html/iface-summary.html         \
  doc/html/menu-main.html             \
  doc/html/bar-main.html              \
  doc/html/bar-interval.html          \
  doc/html/iface-login.html           \
  doc/html/iface-interval-search.html \
  doc/html/iface-log.html             \
  doc/html/iface-palette.html         \
  doc/html/iface-user-adm.html        \
  -o out.pdf                          \
  -s doc/html/style/print.css         \
  --fileroot=.                        \
  --javascript                        \
  --script doc/print.js
