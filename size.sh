#!/bin/bash

# Calculate total size of src/ and res/
size_src=$(du -sb src/ 2>/dev/null | awk '{print $1}')
size_res=$(du -sb res/ 2>/dev/null | awk '{print $1}')

# Add them together
total_size=$((size_src + size_res))

# Print the result
echo "Total size (bytes): $total_size"

# Optional: print in human-readable format
echo "Total size (human-readable): $(numfmt --to=iec $total_size)"
