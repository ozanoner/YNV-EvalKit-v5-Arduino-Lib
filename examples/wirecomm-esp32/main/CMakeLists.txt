idf_component_register(SRCS "mcu_comm.cpp" "i2c_conn.cpp" "main.cpp"
                    INCLUDE_DIRS ".")

target_compile_features(${COMPONENT_LIB} PRIVATE cxx_std_17)
target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-missing-field-initializers)
