include(/Users/alexey/Casino/build/unknown_f8dfd7-Debug/.qt/QtDeploySupport.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/Casino-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE Casino.app
)
