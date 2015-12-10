#!/bin/bash
mkdir -p ../PDF
rsync -rv --include '*/' --include '*.pdf' --exclude '*' --prune-empty-dirs ../Source/ ../PDF/
mv ../PDF/*/*pdf ../PDF/
find ../PDF -type d -empty -print0 -exec rm -d "{}" \;
