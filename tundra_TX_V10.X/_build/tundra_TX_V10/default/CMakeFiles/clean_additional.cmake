# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "D:\\yiming\\00work\\tundra_TX_V10.X\\out\\tundra_TX_V10\\default.cmf"
  "D:\\yiming\\00work\\tundra_TX_V10.X\\out\\tundra_TX_V10\\default.hex"
  "D:\\yiming\\00work\\tundra_TX_V10.X\\out\\tundra_TX_V10\\default.hxl"
  "D:\\yiming\\00work\\tundra_TX_V10.X\\out\\tundra_TX_V10\\default.mum"
  "D:\\yiming\\00work\\tundra_TX_V10.X\\out\\tundra_TX_V10\\default.o"
  "D:\\yiming\\00work\\tundra_TX_V10.X\\out\\tundra_TX_V10\\default.sdb"
  "D:\\yiming\\00work\\tundra_TX_V10.X\\out\\tundra_TX_V10\\default.sym"
  )
endif()
