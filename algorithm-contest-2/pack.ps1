foreach ($problem in 1..5) {
    Push-Location "output/$problem"
    7z a -tzip "$problem.zip" *
    Move-Item "$problem.zip" ..
    Pop-Location
}
