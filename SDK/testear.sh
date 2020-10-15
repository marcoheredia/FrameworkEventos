#!/bin/bash
cp -r ./components/proyecto/ $IDF_PATH/components/
echo "Archivos de test copiados al directorio de ESP-IDF"
echo "Ejecutar: cd $IDF_PATH/tools/unit-test-app/"
echo "Ejecutar: make -j9 TEST_COMPONENTS='proyecto' flash monitor"