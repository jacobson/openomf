
SET(VORBIS_SEARCH_PATHS
    /usr/local/
    /usr
    /opt
)

FIND_PATH(VORBIS_INCLUDE_DIR vorbis/vorbisfile.h
    HINTS ${VORBIS_ROOT}
    PATH_SUFFIXES include
    PATHS ${VORBIS_SEARCH_PATHS}
)
FIND_LIBRARY(VORBIS_LIBRARY vorbis
    HINTS ${VORBIS_ROOT}
    PATH_SUFFIXES lib64 lib bin
    PATHS ${VORBIS_SEARCH_PATHS}
)
FIND_LIBRARY(VORBISFILE_LIBRARY vorbisfile
    HINTS ${VORBIS_ROOT}
    PATH_SUFFIXES lib64 lib bin
    PATHS ${VORBIS_SEARCH_PATHS}
)

IF(VORBIS_INCLUDE_DIR AND VORBIS_LIBRARY AND VORBISFILE_LIBRARY)
   SET(VORBIS_FOUND TRUE)
ENDIF (VORBIS_INCLUDE_DIR AND VORBIS_LIBRARY AND VORBISFILE_LIBRARY)


IF(VORBIS_FOUND)
    MESSAGE(STATUS "Found Vorbis: ${VORBIS_LIBRARY}")
    MESSAGE(STATUS "Found Vorbisfile: ${VORBISFILE_LIBRARY}")
ELSE(VORBIS_FOUND)
    MESSAGE(WARNING "Could not find Vorbis")
ENDIF(VORBIS_FOUND)
