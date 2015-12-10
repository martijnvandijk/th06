#!/bin/bash
mkdir -p PDF
rsync -rv --include '*/' --include '*.pdf' --exclude '*' --prune-empty-dirs LaTeX/ PDF/ 
