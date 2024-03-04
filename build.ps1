param(
    [switch]$r,
    [switch]$d,
)

# activate emscripten variables
emsdk_env.bat


# setup and run cmake and make
If ($r)
{
    emcmake cmake . -DCMAKE_BUILD_TYPE=Release
    Write-Output "Building for release"
}
ElseIf ($d)
{
    emcmake cmake . -DCMAKE_BUILD_TYPE=Debug
    Write-Output "Building for debug"
}
Else
{
    Write-Output "No flag specified"
    Break
}

emmake make index

Write-Output "Copying files to /test"
# cp -R target/. test/
Copy-Item -Path target\* -Destination test\

Write-Output "Done."