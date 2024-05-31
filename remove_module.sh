#!/bin/bash

module_path=$1


if [[ -z "$module_path" ]]; then
    echo "No path provided"
    exit 1
fi

if [[ ! -d $module_path ]]; then
    echo "Path doesn't exist"
    exit 1
fi


echo "Removing $module_path..."
# remove submodule entry from .git/config 
git submodule deinit -f $module_path

# remove submodule directory from .git/modules
rm -rf .git/modules/$module_path

# remove submodule entry from .gitmodules and remove the submodule itself
git rm -f $module_path
