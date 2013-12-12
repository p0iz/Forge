# Generic asset handling headers

set(AssetHeaders
  AssetLibrary.hpp
  AssetTraits.hpp
)

add_library(Asset ${AssetHeaders})
set_target_properties(Asset PROPERTIES LINKER_LANGUAGE "CXX")
