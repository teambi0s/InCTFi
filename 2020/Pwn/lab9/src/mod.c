/**
 * mod.c - InCTFi 2020
 *
 */
#include <linux/module.h>       /* Specifically, a module */
#include <linux/kernel.h>       /* We're doing kernel work */
#include <linux/proc_fs.h>      /* Necessary because we use the proc fs */
#include <linux/uaccess.h>        /* for copy_from_user */
#include <linux/vmalloc.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <asm/page.h>
#include <linux/err.h>

#include <linux/init.h>
#include <linux/skbuff.h>
#include <linux/delay.h>
#include <asm/page.h>
#include <asm/xen/page.h>

#define MAJOR_NUM 100
#define DEVICE_NAME "mod"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("teambi0s <amritabi0s1@gmail.com>");
MODULE_DESCRIPTION("kpwn");

#undef PRINTK
#ifdef KDEBUG
#define PRINTK(fmt, args...) printk(KERN_DEBUG "mod: " fmt, ##args)
#else
#define PRINTK(fmt, args...) /* not debugging: nothing */
#endif

#define BOX_SIZE 0x1000

#define IOCTL_LOCK_BOX 0x1337
#define IOCTL_UNLOCK_BOX 0x1338
#define IOCTL_SET_BOX 0x1339
#define IOCTL_RESIZE_BOX 0x133a

#define ENC_BOX struct encBox
struct encBox {
  size_t boxSize;
  size_t boxKey;
  char * boxPtr;
};

static int crypt_box(ENC_BOX *box) {

  int i;
  for (i = 0; i < BOX_SIZE / sizeof(size_t); i += 1)
    ((size_t *)box->boxPtr)[i] ^= box->boxKey;

  PRINTK("[*] decrypting/encrypting box with : %p\n", box->boxKey);
  return BOX_SIZE;
}

static int box_validate(ENC_BOX * box, char *attr) {
  size_t key = 0;

  if (box->boxKey == 0) return -EINVAL;
  if (copy_from_user(&key, (char *)attr, sizeof(size_t)))
      return -EFAULT;
  if(box->boxKey != key)
    return -EINVAL;
  return 0;
}

static int box_lock(ENC_BOX * box, char *attr) {

  ssize_t err = 0;
  err = box_validate(box, (char *) attr);
  if(err) return err;
  return crypt_box(box);
}

static int box_unlock(ENC_BOX * box, char *attr) {

  ssize_t err = 0;
  err = box_validate(box, (char *) attr);
  if(err) return err;
  return crypt_box(box);
}


static int box_set(ENC_BOX * box, char *attr) {
  size_t key = 0;
  if (copy_from_user(&key, (char *)attr, sizeof(size_t)))
      return -EFAULT;

  box->boxKey = key;
  PRINTK("[*] set box key : %p\n", box->boxKey);
  return 0;
}

static int box_resize(ENC_BOX * box, char *attr) {
  size_t size = 0;
  ssize_t err = 0;
  char * ptr;
  if (copy_from_user(&size, (char *)attr, sizeof(size_t)))
      return -EFAULT;
  box->boxSize = size;
  err = box_validate(box, ((char *)attr + sizeof(size_t)));
  if(err) {
    box->boxSize = 0;
    return err;
  }
  ptr = (char *) kzalloc(size, GFP_KERNEL);
  if (!ptr) { 
    box->boxSize = 0;
    return -ENOMEM;
  }
  box->boxPtr = ptr;
  PRINTK("[*] box_resize: size(%p) : ptr(%p)\n", box->boxSize, box->boxPtr);
  return 0;
}

static long device_ioctl(struct file *file, unsigned int ioctl_num,
                         unsigned long ioctl_param) {

  ssize_t err = 0;
  ENC_BOX * box = file->private_data;
  PRINTK("[*] ioctl(%x)\n", ioctl_num, file);

  switch (ioctl_num) {
  case IOCTL_LOCK_BOX:
    err = box_lock(box, (char *)ioctl_param);
    break;
  case IOCTL_UNLOCK_BOX:
    err = box_unlock(box, (char *)ioctl_param);
    break;
  case IOCTL_SET_BOX:
    err = box_set(box, (char *)ioctl_param);
    break;
  case IOCTL_RESIZE_BOX:
    err = box_resize(box, (char *)ioctl_param);
    break;
  default:
    err = -EINVAL;
  }
  return err;
}

static int device_mmap(struct file  *file, struct vm_area_struct *vma) {
  size_t vma_size = vma->vm_end - vma->vm_start;
  size_t offset = vma->vm_pgoff << PAGE_SHIFT;

  ENC_BOX * box = (ENC_BOX *)file->private_data;
  PRINTK("[*] mmap : size(%x) , offset(%x), box_size(%x)\n", vma_size, offset, box->boxSize);
  if (vma_size <= box->boxSize && offset <= box->boxSize && vma_size + offset <= box->boxSize ) {
    PRINTK("[*] mapping page : kernel(%p) -> user(%p)\n", box->boxPtr, vma->vm_start);
    if(remap_pfn_range( vma, vma->vm_start, virt_to_pfn(box->boxPtr),
                        vma_size, vma->vm_page_prot))
      {
        PRINTK("mmap failed\n");
        return -EAGAIN;
      }
  }
  return 0;
}

static int device_open(struct inode *inode, struct file *file) {

  ENC_BOX * box = (ENC_BOX *)kzalloc(sizeof(ENC_BOX), GFP_KERNEL);
  if (!box) return -ENOMEM;
  box->boxSize = BOX_SIZE;
  box->boxPtr = kzalloc(BOX_SIZE, GFP_KERNEL);
  box->boxKey = 0;
  if (!box->boxPtr) {
    kfree(box);
    return -ENOMEM;
  }
  file->private_data = box;
  PRINTK("[*] Device Opened box_ptr(%p)\n",box->boxPtr);
  return 0;
}

static int device_release(struct inode *inode, struct file *file) { return 0; }

struct file_operations Fops = {
    .unlocked_ioctl = device_ioctl,
    .mmap = device_mmap, 
    .open = device_open,
    .release = device_release,
};

int init_module() {
  int ret_val;
  ret_val = register_chrdev(MAJOR_NUM, DEVICE_NAME, &Fops);
  if (ret_val < 0) {
    printk(KERN_ALERT "%s failed with %d\n",
           "Sorry, registering the character device ", ret_val);
    return ret_val;
  }
  PRINTK("[*] Module initialized\n");
  return 0;
}

void cleanup_module() {
  unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
  PRINTK("[*] Module removed\n");
}
