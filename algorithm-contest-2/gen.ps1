Push-Location solution

foreach ($problem in 1..5) {
    clang-cl "$problem.cpp" /O2 "-fsanitize=address,undefined"
}

Pop-Location

Remove-Item -Recurse output

mkdir .\output

$time_output = @()

foreach ($problem in 1..5) {
    mkdir output/$problem
    foreach ($genfile in Get-ChildItem "generator/$problem") {
        if ($genfile.Name -match "(.+)\.in") {
            $genfile_id = $Matches[1]
            Copy-Item $genfile output/$problem
        }
        elseif ($genfile.Name -match "(.+)\.cpp") {
            $genfile_id = $Matches[1]
            Push-Location "generator/$problem"
            clang-cl $genfile.Name /O2 "-fsanitize=address,undefined"
            Pop-Location
            & "./generator/$problem/$genfile_id.exe" > "./output/$problem/$genfile_id.in"
        }
        $time = (Measure-Command {
                Get-Content "./output/$problem/$genfile_id.in" | & "./solution/$problem.exe"  > "./output/$problem/$genfile_id.out"
            }).TotalSeconds

        $time_output += "Problem $problem test point $genfile_id time: $time s."
    }
}

foreach ($line in $time_output) {
    Write-Output $line
}
