cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(2dgamesclasses VERSION 2.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

IF (WIN32)
  message(NOTICE "\n")
  message(NOTICE "********************** IMPORTANT NOTICE ****************************\n")
  message(NOTICE "Make sure you have enabled Developer Mode in your system settings!")
  message(NOTICE "To enable Developer Mode go to Settings -> Update & Security -> For developers -> Developer Mode ON")
  message(NOTICE "\n********************************************************************")
  message(NOTICE "\n")
ENDIF()

# ---- Zależności ----
# Ta komenda wejdzie do 'thirdparty' i wykona tamtejszy CMakeLists.txt
add_subdirectory(thirdparty)

# ---- Pliki głównego projektu ----
# Ta komenda wejdzie do 'src' i wykona tamtejszy CMakeLists.txt
add_subdirectory(src)