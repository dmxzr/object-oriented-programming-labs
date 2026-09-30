# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -fprofile-arcs -ftest-coverage
LDFLAGS = -lgtest -lgtest_main -pthread -fprofile-arcs -ftest-coverage

# Директории
SRC_DIR = src
LIB_DIR = lib
COVERAGE_DIR = coverage

# Файлы
LIB_SRC = $(wildcard $(SRC_DIR)/*.cpp)
LIB_HEADERS = $(wildcard $(LIB_DIR)/*.hpp)
MAIN_SRC = main.cpp
TEST_SRC = gtest.cpp

# Цели
MAIN_TARGET = main
TEST_TARGET = run_tests

.PHONY: all clean run test coverage

# Сборка всех целей
all: $(MAIN_TARGET) $(TEST_TARGET)

# Сборка и линковка основного приложения
$(MAIN_TARGET): $(LIB_SRC) $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Сборка и линковка тестов
$(TEST_TARGET): $(LIB_SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Запуск основного приложения
run: $(MAIN_TARGET)
	./$(MAIN_TARGET)

# Запуск тестов
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Генерация отчёта покрытия кода
coverage: $(TEST_TARGET)
	mkdir -p $(COVERAGE_DIR)
	./$(TEST_TARGET)
	gcovr -r . --exclude "CMakeFiles" --exclude $(COVERAGE_DIR) --html-details -o $(COVERAGE_DIR)/coverage.html

# Очистка собранных файлов
clean:
	rm -f $(MAIN_TARGET) $(TEST_TARGET)
	rm -rf $(COVERAGE_DIR)
	rm -f *.gcda *.gcno *.gcov
