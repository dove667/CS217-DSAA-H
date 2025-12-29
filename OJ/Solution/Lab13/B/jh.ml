let n, m = Scanf.scanf "%d %d\n" (fun n m -> n, m)
let adj = Array.make n []
let () =
  for i = 0 to m-1 do
    Scanf.scanf "%d %d\n" (fun i j ->
        adj.(i-1) <- (j-1) :: adj.(i-1);
        adj.(j-1) <- (i-1) :: adj.(j-1))
  done

let q = Queue.create ()
let inf = 1000000000
let dist = Array.make n inf
let () =
  Queue.push (0, 0) q;
  while not (Queue.is_empty q) do
    let (x, d) = Queue.pop q in
    if dist.(x) = inf then
      begin
        dist.(x) <- d;
        List.iter (fun y -> Queue.push (y, d+1) q) adj.(x)
      end
  done
let maxdist = Array.fold_left max 0 dist

let rec log2floor = function
  | -1 -> -2
  | 0 -> -1
  | n -> 1+log2floor (n/2)
let log2ceil n = 1+log2floor (n-1)

let () =
  Printf.printf "%d\n" (if maxdist = inf then -1 else log2ceil maxdist + 1)
