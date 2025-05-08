#!/bin/bash
# Simple wrapper to call Piper TTS
MODEL="$3"
MODEL_FILE="$4"
cat "$2"| piper/piper/piper --model $MODEL -f $MODEL_FILE  --output-raw |   ros2 run tts tts_publisher_node
