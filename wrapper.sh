#!/usr/bin/env bash
folder="./${1:-"test"}/"
echo "using folder: $folder"

echo "setting up environment/build for consistency"
source ../.geant4
cmake ..
make

echo "storing current git state"
git status > "git_status_output"
git diff > "git_diff_output"
git log -1 > "git_log_output"

echo "Storing the files used to run the script"
mkdir -p "./$folder/"

files=("run.mac"
       "gps.in"
       "git_status_output"
       "git_diff_output"
       "git_log_output")
for f in "${files[@]}"; do
    mv "./$f" "./$folder/$f"
done

echo "Running the script"
./GREENER ./$folder/


# TODO make a script to display the image, place that in the folder
# TODO also store the files that geometry.in points to
