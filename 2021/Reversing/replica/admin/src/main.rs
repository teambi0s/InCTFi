use std::env;

#[derive(PartialEq)]
pub struct TreeNode {
    pub value: u8,
    pub left: Option<Box<TreeNode>>,
    pub right: Option<Box<TreeNode>>,
}

impl TreeNode {
    pub fn new(value: u8, left: Option<Box<TreeNode>>, right: Option<Box<TreeNode>>) -> Self {
        TreeNode { value, left, right }
    }
}

pub struct Tree {
    root: Option<TreeNode>,
}

impl Tree {
    pub fn new(root: Option<TreeNode>) -> Self {
        Tree { root }
    }

    pub fn pre_iter(&self) -> PreorderIter {
        PreorderIter::new(self.root.as_ref())
    }

    pub fn some_iter(&self) -> SomeorderIter {
        SomeorderIter::new(self.root.as_ref())
    }
}

pub struct PreorderIter<'a> {
    stack: Vec<&'a TreeNode>,
}

impl<'a> PreorderIter<'a> {
    pub fn new(root: Option<&'a TreeNode>) -> Self {
        if let Some(node) = root {
            PreorderIter { stack: vec![node] }
        } else {
            PreorderIter { stack: vec![] }
        }
    }
}

impl<'a> Iterator for PreorderIter<'a> {
    type Item = &'a TreeNode;

    fn next(&mut self) -> Option<Self::Item> {
        if let Some(node) = self.stack.pop() {
            if let Some(right) = &node.right {
                self.stack.push(&right)
            }

            if let Some(left) = &node.left {
                self.stack.push(&left)
            }

            return Some(node);
        }

        None
    }
}

pub struct SomeorderIter<'a> {
    stack: Vec<&'a TreeNode>,
}

impl<'a> SomeorderIter<'a> {
    pub fn new(root: Option<&'a TreeNode>) -> Self {
        if let Some(node) = root {
            SomeorderIter { stack: vec![node] }
        } else {
            SomeorderIter { stack: vec![] }
        }
    }
}

impl<'a> Iterator for SomeorderIter<'a> {
    type Item = &'a TreeNode;

    fn next(&mut self) -> Option<Self::Item> {
        if let Some(node) = self.stack.pop() {
            if let Some(left) = &node.left {
                self.stack.push(&left)
            }

            if let Some(right) = &node.right {
                self.stack.push(&right)
            }

            return Some(node);
        }
        None
    }
}

fn create_tree(input: &[u8]) -> Tree {
    let a = TreeNode::new(input[0], None, None);
    let b = TreeNode::new(input[1], None, None);
    let c = TreeNode::new(input[2], None, None);
    let d = TreeNode::new(input[3], None, None);
    let e = TreeNode::new(input[4], None, None);
    let f = TreeNode::new(input[5], None, None);
    let g = TreeNode::new(input[6], None, None);
    let h = TreeNode::new(input[7], None, None);
    let i = TreeNode::new(input[8], None, None);
    let j = TreeNode::new(input[9], None, None);
    let k = TreeNode::new(input[10], Some(Box::from(a)), Some(Box::from(b)));
    let l = TreeNode::new(input[11], None, None);
    let m = TreeNode::new(input[12], Some(Box::from(c)), Some(Box::from(d)));
    let n = TreeNode::new(input[13], None, None);
    let o = TreeNode::new(input[14], Some(Box::from(e)), Some(Box::from(f)));
    let p = TreeNode::new(input[15], None, None);
    let q = TreeNode::new(input[16], Some(Box::from(g)), Some(Box::from(h)));
    let r = TreeNode::new(input[17], Some(Box::from(i)), Some(Box::from(j)));
    let s = TreeNode::new(input[18], Some(Box::from(k)), Some(Box::from(l)));
    let t = TreeNode::new(input[19], Some(Box::from(m)), Some(Box::from(n)));
    let u = TreeNode::new(input[20], Some(Box::from(o)), Some(Box::from(p)));
    let v = TreeNode::new(input[21], Some(Box::from(q)), Some(Box::from(r)));
    let w = TreeNode::new(input[22], Some(Box::from(s)), Some(Box::from(t)));
    let x = TreeNode::new(input[23], Some(Box::from(u)), Some(Box::from(v)));
    let y = TreeNode::new(input[24], Some(Box::from(w)), Some(Box::from(x)));

    Tree::new(Some(y))
}

fn main() -> Result<(), ()> {
    let some = vec![
        48, 107, 101, 100, 116, 90, 54, 102, 89, 79, 51, 97, 88, 52, 108, 80, 78, 77, 83, 103, 81,
        98, 82, 119, 104,
    ];

    println!("m41n r3pl1c4");
    println!("------------");
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        return Err(());
    }

    let input: Vec<u8> = Vec::from(args[1].as_bytes());

    if input.len() < 25 {
        return Err(());
    }

    let tree = create_tree(&input);
    for (i, node) in tree.some_iter().enumerate() {
        if node.value != some[i] {
            return Err(());
        }
    }

    let flag: Vec<u8> = tree
        .pre_iter()
        .map(
            |TreeNode {
                 value,
                 left: _,
                 right: _,
             }| (value),
        )
        .cloned()
        .collect();
    println!("yup: inctf{{{}}}", String::from_utf8_lossy(&flag));
    Ok(())
}
