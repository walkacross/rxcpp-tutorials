function(load_rxcpp root_dir release_ver )
    # envpool destination dir
    set(LIBRARY_NAME "RxCpp")
    set(LIBRARY_DIR ${root_dir}/third_party/${LIBRARY_NAME})

    # debug message
    message( STATUS "Fetching library dependence to project." )

    # already download
    if( EXISTS ${LIBRARY_DIR} )
        # build libencrypt
        message( STATUS "${LIBRARY_DIR} exists, building..." )
        add_subdirectory( ${LIBRARY_DIR} )
    else()
        # Download libencrypt to third party folder
        message( STATUS "${LIBRARY_DIR} does not exist,to download from URL")
        set(GIT_REPOSITORY_PATH "https://github.com/ReactiveX/RxCpp")

        include( FetchContent )
        FetchContent_Declare(
                ${LIBRARY_NAME}
                GIT_REPOSITORY ${GIT_REPOSITORY_PATH} # temp git repo
                # cn-proxy
                # GIT_REPOSITORY "https://${git_token}@ghproxy.com/https://github.com/walkacross/libencrypt.git"
                GIT_TAG ${release_ver}
                SOURCE_DIR ${LIBRARY_DIR}
        )
        FetchContent_MakeAvailable( ${LIBRARY_NAME} )
    endif()

    # debug message
    message( STATUS "** load_${LIBRARY_NAME} - done. **" )
endfunction()