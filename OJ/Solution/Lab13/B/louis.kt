import java.util.Arrays
import kotlin.math.*

fun main () {
  val input = readLine()!!.split(" ");
  val n = input[0].toInt();
  val m = input[1].toInt();
  var nxt : Array<MutableList<Int>> = Array(n, { _ -> mutableListOf<Int>() } );
  for(i in 1 .. m ) {
    val input = readLine()!!.split(" ");
    val a = input[0].toInt()-1;
    val b = input[1].toInt()-1;
    nxt[a].add(b);
    nxt[b].add(a);
  }
  var stack = IntArray(n) {_ -> 0};
  var size = 1 ;
  var dist = IntArray(n) {_ -> -1};
  dist[0] = 0;
  var maxDist = 1;
  for(i in 0..n-1) {
    if( i <= size ) {
      for(el in nxt[stack[i]]) {
        if( dist[el] < 0) {
          dist[el] = dist[stack[i]]+1;
          maxDist = dist[el];
          stack[size] = el ;
          size ++;
        }
      }
    }
  }
  if(size == n) {
    println( ceil(log(maxDist.toDouble(),2.0)).toInt()+1);
  } else {
    println(-1);
  }
}

