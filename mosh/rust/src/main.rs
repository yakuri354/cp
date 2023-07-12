use core::cmp::min;

#[derive(Clone, Copy)]
struct Addr {
    x: usize,
    y: usize
}

enum TCell {
    Value(i64),
    Sum(Addr, Addr),
    Min(Addr, Addr)
}

type Table = Vec<Vec<TCell>>;

fn eval(t: &mut Table, addr: Addr) -> i64 {
    let val = match t[addr.x][addr.y] {
        TCell::Value(x) => x,
        TCell::Sum(a, b) => eval(t, a) + eval(t, b),
        TCell::Min(a, b) => min(eval(t, a), eval(t, b)),
    };

    t[addr.x][addr.y] = TCell::Value(val);

    val
}

fn main() {
    let s = "";
}
