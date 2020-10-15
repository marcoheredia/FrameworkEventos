#!/bin/bash
python json_a_c.py --c_file fw_config ./config.json
mv ./fw_config.c ./main/fw_config.c
mv ./fw_config.h ./main/fw_config.h
echo "Se crearon los archivos de configuracion"