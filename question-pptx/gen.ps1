foreach ($i in 1..10) {
    py ./main.py
    mv test.pptx "$i.pptx"
}
