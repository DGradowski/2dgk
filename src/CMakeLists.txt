# Automatycznie znajdź wszystkie pliki .cpp w tym katalogu (src/)
file(GLOB SRC_FILES "*.cpp")

# Stwórz plik wykonywalny (target) o nazwie '2dgamesclasses' 
# (używam nazwy z Twojego 'project()')
add_executable(2dgamesclasses ${SRC_FILES})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
				   COMMAND ${CMAKE_COMMAND} -E create_symlink 
				   ${CMAKE_SOURCE_DIR}/res 
				   ${CMAKE_CURRENT_BINARY_DIR}/res)

# --- Ścieżki do nagłówków ---
# To jest kluczowa linijka! Mówi ona celowi '2dgamesclasses', 
# aby szukał plików .h w katalogu 'include' w głównym folderze projektu.
# ${PROJECT_SOURCE_DIR} to zmienna CMake wskazująca na katalog 
# z głównym plikiem CMakeLists.txt
target_include_directories(2dgamesclasses PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# --- Linkowanie bibliotek ---
# Połącz swój program z bibliotekami SFML
target_link_libraries(2dgamesclasses PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    sfml-network
)

# Przeniesiona logika dla Windows
if(WIN32)
    target_link_libraries(2dgamesclasses PRIVATE sfml-main)
endif()