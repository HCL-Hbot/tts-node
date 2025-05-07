#!/bin/bash
# Simple wrapper to call Piper TTS
MODEL="$3"
MODEL_FILE="$4"
cat "$2"| piper/piper/piper --model $MODEL -f $MODEL_FILE  --output-raw |  aplay -f S16_LE -c 1 -r 22050
