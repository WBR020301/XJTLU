set(CMAKE_CXX_STANDARD 17)
set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ${BUILD_SHARED_LIBS})

# 添加 mdflib 静态库
add_library(mdflib STATIC
    # 添加所有的 .cpp 文件
    ${CMAKE_SOURCE_DIR}/mdflib/src/at4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/bigbuffer.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/blockproperty.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/ca4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/canmessage.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/cc4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/cg4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/cgrange.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/ch4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/channelobserver.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/cn4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/cryptoutil.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/datablock.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/datalistblock.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/dbchelper.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/dg4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/dgrange.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/di4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/dl4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/dt4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/dv4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/dz4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/etag.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/ev4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/expatxml.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/fh4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/hd4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/hl4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/iattachment.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/iblock.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/ichannelarray.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/ichannelconversion.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/ichannel.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/ichannelgroup.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/ichannelhierarchy.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/ichannelobserver.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/idatagroup.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/idblock.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/ievent.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/ifilehistory.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/iheader.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/imetadata.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/isampleobserver.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/isamplereduction.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/isourceinformation.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/ixmlfile.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/ixmlnode.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/ld4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/littlebuffer.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/md4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/mdf4file.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/mdf4timestamp.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/mdf4writer.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/mdfblock.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/mdfbuslogger.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/mdfconverter.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/mdffactory.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/mdffile.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/mdfhelper.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/mdflogstream.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/mdfreader.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/mdfwriter.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/platform.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/rd4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/readcache.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/ri4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/rv4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/sd4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/si4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/sr4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/timestamp.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/tx4block.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/vlsddata.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/writexml.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/xmlnode.cpp
    ${CMAKE_SOURCE_DIR}/mdflib/src/zlibutil.cpp
)

set(CMAKE_POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})

find_package(ZLIB REQUIRED)
target_link_libraries(mdflib PRIVATE ZLIB::ZLIB)

find_package(expat CONFIG REQUIRED)
target_link_libraries(mdflib PRIVATE expat::expat)
# Specify include directories for mdflib
target_include_directories(mdflib PUBLIC ${CMAKE_SOURCE_DIR}/mdflib/include)

