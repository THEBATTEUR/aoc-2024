import java.io.File
import java.util.Scanner
import java.util.regex.Pattern
import kotlin.math.abs

fun main() {
    val file = File("input")
    val scanner = Scanner(file)
    var total = 0
    val left: ArrayList<Int> = arrayListOf()
    val right: ArrayList<Int> = arrayListOf()
    while (scanner.hasNextLine()) {
        val splittedLine = scanner.nextLine().split(Pattern.compile("\\s+"))
        left.add(Integer.parseInt(splittedLine[0]))
        right.add(Integer.parseInt(splittedLine[1]))
    }
    left.sort()
    right.sort()
    for (i in 0 until left.size) {
        total += abs(left[i] - right[i])
    }
    println("Final value: $total")
}