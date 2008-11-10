set(synergytray_SRCS
   main.cpp
   synergytray.cpp
   mainview.cpp
   synergymanager.cpp
   synergyserver.cpp
   synergyclient.cpp
   iconloader.cpp
   networkutils.cpp
   processutils.cpp
 )

kde4_add_ui_files(synergytray_SRCS
    mainview.ui
    config_client.ui
    config_server.ui
    config_settings.ui
)

kde4_add_kcfg_files(synergytray_SRCS settings.kcfgc )

kde4_add_executable(synergytray ${synergytray_SRCS})

target_link_libraries(synergytray ${KDE4_KDEUI_LIBS} )

install(TARGETS synergytray DESTINATION ${BIN_INSTALL_DIR} )


########### install files ###############

install( FILES synergytray.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES synergytray.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
#install( FILES synergytrayui.rc  DESTINATION  ${DATA_INSTALL_DIR}/synergytray )
