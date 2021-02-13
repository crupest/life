$musicDirectory = 'D:\CloudMusic'
$ncmdumpPath = 'D:\ncmdump-windows-amd64.exe'

pushd $musicDirectory
Write-Host "Enter $musicDirectory"

foreach ($file in Get-ChildItem $musicDirectory) {
    if (($file.Extension -eq '.ncm') -and (Get-ChildItem $musicDirectory | Where-Object { ($_.BaseName -eq $file.BaseName) -and ($_.Extension -eq '.mp3' -or $_.Extension -eq '.flac') }).Length -eq 0) {
        Write-Host "Convert $($file.Name) ..."
        & $ncmdumpPath $file.Name
    }
}

Write-Host "Exit $musicDirectory"
popd
