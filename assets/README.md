This folder is for storing resources such as binaries, scripts, images, sounds, fonts etc. that the app uses. This folder gets copied by CMake to the installation destination when building the executable.

If there are multiple files under `assets` with the same filename include the parent folder name to resolve ambiguities in the code.