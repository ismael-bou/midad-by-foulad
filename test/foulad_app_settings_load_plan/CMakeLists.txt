add_executable(FouladAppSettingsLoadPlanTest
  FouladAppSettingsLoadPlanTest.cpp
  ${REPO_ROOT}/src/FouladAppSettingsLoadPlan.cpp
)

target_include_directories(FouladAppSettingsLoadPlanTest PRIVATE
  ${REPO_ROOT}/src
)

target_link_libraries(FouladAppSettingsLoadPlanTest PRIVATE
  crosspoint_test_common
  GTest::gtest_main
)

gtest_discover_tests(FouladAppSettingsLoadPlanTest)
