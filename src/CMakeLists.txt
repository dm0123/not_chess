# Main module
add_executable(not_chess)
target_sources(not_chess PRIVATE
  main.cpp
  include/game.hpp
  include/core/app.hpp

  include/core/settings.hpp
  include/core/scores.hpp
  include/core/asset_manager.hpp
  include/core/sound.hpp
  include/core/events.hpp
  include/core/screen.hpp
  include/core/input.hpp
  include/core/app_exception.hpp

  include/component.hpp
  include/entity.hpp

  include/sprite_component.hpp
  include/sound_component.hpp
  include/input_component.hpp
  include/grid_component.hpp
  include/screen_factory.hpp
  include/entities_factory.hpp
  include/position_component.hpp
  include/ai_component.hpp
  include/game_screen.hpp
  include/text_component.hpp
  include/pause_screen.hpp
  include/finished_screen.hpp

  implementation/app.cpp
  implementation/game.cpp
  implementation/input.cpp
  implementation/screen.cpp
  implementation/scores.cpp
  implementation/asset_manager.cpp
  implementation/sound.cpp
  implementation/settings.cpp
  implementation/entity.cpp
  implementation/screen_factory.cpp
  implementation/entities_factory.cpp
  implementation/game_screen.cpp
  implementation/text_component.cpp
  implementation/pause_screen.cpp
  implementation/finished_screen.cpp

  implementation/input_component.cpp
  implementation/sound_component.cpp
  implementation/sprite_component.cpp
  implementation/grid_component.cpp
  implementation/ai_component.cpp)

target_link_libraries(not_chess PRIVATE sfml-graphics sfml-audio)
target_include_directories(not_chess PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
set_target_properties(not_chess PROPERTIES CXX_STANDARD 17)
