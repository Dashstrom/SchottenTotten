#!/usr/bin/env bash

set -e

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
SCRIPT_DIR=$( dirname -- "${SCRIPT_DIR}" )
cd -- "${SCRIPT_DIR}"


if ! command -v pandoc 1> /dev/null 2> /dev/null; then
  >&2 echo -e "[ERROR] pandoc is missing, please run :\n\n    sudo apt install pandoc\n"
  exit 1
fi

if ! command -v rsvg-convert 1> /dev/null 2> /dev/null; then
  >&2 echo -e "[ERROR] rsvg-convert is missing, please run :\n\n    sudo apt install librsvg2-bin\n"
  exit 1
fi

if ! java -jar "${SCRIPT_DIR}/docs/plantuml-1.2023.9.jar" -testdot 1> /dev/null 2> /dev/null; then
  >&2 echo -e "[ERROR] Graphviz is missing, please run :\n\n    sudo apt install graphviz\n"
  exit 1
fi
echo '[INFO] Convert PLANTUML to PNG ...'
java -jar "${SCRIPT_DIR}/docs/plantuml-1.2023.9.jar" -charset UTF-8 "${SCRIPT_DIR}/docs/classes.puml"
echo '[INFO] Convert MD to PDF ...'
pandoc "${SCRIPT_DIR}/README.md" \
  -o "${SCRIPT_DIR}/docs/REPORT.pdf" \
  --template ${SCRIPT_DIR}/docs/eisvogel.latex \
  --listings \
  -V 'block-headings' \
  -V 'geometry:top=3cm' \
  -V 'geometry:bottom=3cm' \
  -V 'geometry:left=2cm' \
  -V 'geometry:right=2cm' \
  -V 'titlepage'  \
  -V 'title:Shotten Totten project report'  \
  -V 'author:Dashstrom' \
  -V 'author:Marin Bouanchaud' \
  -V 'author:ericluo-lab' \
  -V 'author:Soudarsane TILLAI' \
  -V 'author:Baptiste Buvron' \
  -V "logo:${SCRIPT_DIR}/docs/utc.png" \
  -V 'listings-disable-line-numbers' \
  -V 'date:2023-06-18'
echo "[INFO] Done, PDF available at ${SCRIPT_DIR}/docs/REPORT.pdf"
