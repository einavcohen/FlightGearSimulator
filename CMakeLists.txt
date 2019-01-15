cmake_minimum_required(VERSION 3.12)
project(new_milestone_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(new_milestone_2 main.cpp FileCacheManager.cpp FileCacheManager.h ClientHandler.h CacheManager.h Searchable.h Searcher.h SearcherSolver.h StructSearchResult.h SearchableMatrix.cpp SearchableMatrix.h BFS.cpp BFS.h)