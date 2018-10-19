#include <sys/cdefs.h>

#include <sys/param.h>
#include <sys/conf.h>
#include <sys/device.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/systm.h>
#include <sys/md5.h>
#include <sys/sha1.h>
#include <sys/kmem.h>
#include <sys/ioccom.h>

#include <uvm/uvm.h> 

#define BUFFER_LEN 100
#define KREVDEC _IO('K', 3)
#define KREVFLAG _IO('K', 2)
#define KREVINC _IO('K', 1)
#define YOULOSE "Reverse the challenge first"
#define LEN 28

int check_flag(void);
void get_flag_ready(void);
void md5hash(void);
void sha1hash(void);
int lol(int, int);

dev_type_open(chall2_open);
dev_type_close(chall2_close);
dev_type_mmap(chall2_mmap);
dev_type_read(chall2_read);
dev_type_ioctl(chall2_ioctl);
dev_type_write(chall2_write);

static struct cdevsw chall2_cdevsw = {
	.d_open = chall2_open,
	.d_close = chall2_close,
	.d_read = chall2_read,
	.d_write = chall2_write,
	.d_ioctl = chall2_ioctl,
	.d_stop = nostop,
	.d_tty = notty,
	.d_poll = nopoll,
	.d_mmap = chall2_mmap,
	.d_kqfilter = nokqfilter,
	.d_discard = nodiscard,
	.d_flag = D_OTHER
};

struct chall2_softc {
	int refcnt;
	char *buffer;
	char *buffer2;
	char *input_finale;
	char *final_flag;
	int buf_len;
	int xor_ctr;
	int flag_ready;
	char md5string[33];
	char sha1string[41];

};

static struct chall2_softc sc;

int
chall2_open(dev_t self __unused, int flag __unused, int mode __unused,
           struct lwp *l __unused)
{
	if (sc.refcnt > 0)
		return EBUSY;
	++sc.refcnt;
	sc.flag_ready = -1;
	sc.buf_len = BUFFER_LEN;
	sc.buffer = (char *)uvm_km_alloc(kernel_map, BUFFER_LEN * sizeof(char),
					0,UVM_KMF_WIRED | UVM_KMF_ZERO);
	sc.buffer2 = (char *)kmem_zalloc(BUFFER_LEN, KM_SLEEP);
	sc.input_finale = (char *)uvm_km_alloc(kernel_map, BUFFER_LEN * sizeof(char),
					0,UVM_KMF_WIRED | UVM_KMF_ZERO);
	sc.final_flag = (char *)uvm_km_alloc(kernel_map, BUFFER_LEN * sizeof(char),
					0,UVM_KMF_WIRED | UVM_KMF_ZERO);
	return 0;
}

int
chall2_close(dev_t self __unused, int flag __unused, int mode __unused,
            struct lwp *l __unused)
{
	--sc.refcnt;
	return 0;
}

int
chall2_write(dev_t self, struct uio *uio, int flags)
{
    if (sc.buffer2)
	kmem_free(sc.buffer2, sc.buf_len);
    sc.buf_len = uio->uio_iov->iov_len;
    sc.buffer2 = (char *)kmem_alloc(sc.buf_len, KM_SLEEP);
    uiomove(sc.buffer2, sc.buf_len, uio);
    return 0;
}

int lol(int x, int n) 
{
    int m;
    if (n == 0) return 1;
    if (n % 2 == 0) {
        m = lol(x, n / 2);
        return m * m;
    } else return x * lol(x, n - 1);
}

void md5hash(void){
	unsigned char digest[16];
	struct MD5Context context;
	MD5Init(&context);
	MD5Update(&context, sc.sha1string, strlen(sc.sha1string));
	MD5Final(digest, &context);
	for(int i = 0; i < 16; ++i)
    		snprintf(&sc.md5string[i*2],5, "%02x", (unsigned int)digest[i]);
}

void sha1hash(void) {
	unsigned char digest[20];
	SHA1_CTX context;
	SHA1Init(&context);
	SHA1Update(&context,sc.input_finale, strlen(sc.input_finale));
	SHA1Final(digest, &context);
	for(int i = 0; i < 20; ++i)
    		snprintf(&sc.sha1string[i*2],5, "%02x", (unsigned int)digest[i]);
}

int
check_flag()
{
	if(*sc.buffer == 0 || *sc.buffer2 == 0 ){
		printf("Supply necessary inputs\n");
		return -1;
	}
    char *fin = kmem_zalloc(0x50,KM_SLEEP);
    int xor_check = sc.xor_ctr;
    char *ptr1, *ptr2, *ptr3;
    int len1 = strlen(sc.buffer);
    *(sc.buffer + len1) = '\0';
    len1 = strlen(sc.buffer);
    int len2 = strlen(sc.buffer2);
    ptr1 = sc.buffer;
    ptr2 = sc.buffer2;
    ptr3 = fin;
    for (size_t i = 0; i < len1+1; i++)
    {
        char b = ((int)*(ptr1 + i) ^ (int)*(ptr2 + (i % len2)));
        *(ptr3 + (len1 - i -1)) = b;
    }
	snprintf(sc.input_finale, strlen(fin)+1 , "%s", fin);
    const char *keymap = "#v(2fx]PJZF[wY48E=,5hyAkL>s3?m|~;pS_WNgIjOuU0Q.$G7+eCl^d1rq9XKDa):BcHn&zTob}<Mi*!R{6t-V";
    char *part = kmem_zalloc(8,KM_SLEEP);
    int digits[7];
    int sum;
    char *final_str = kmem_zalloc(0x50, KM_SLEEP);
    if (strlen(fin) % 7 != 0)
    {   
        printf("Something went wrong\n");
    }
    else {
    	size_t fin_ctr = 0;
        for(size_t ctr = 0; ctr < strlen(fin); ctr+=7)
        {
            snprintf(part, 8, "%s", fin + ctr);
            sum = 0;
            for(size_t ctr2 = 0;  ctr2 < strlen(part);  ctr2++)
            {
                digits[ctr2] = (int)*(part + ctr2) - 97;
            }
            
            for(size_t ctr3 = 0;  ctr3 < strlen(part);  ctr3++)
            {
                if (digits[ctr3] == 0 || digits[ctr3] == 1)
                {
                    sum += digits[ctr3] * lol(2, ctr3);
                }
                else {
                    sc.xor_ctr = 0;
                }
            }
            if (sum < 87) {
                char last = keymap[sum];
                *(final_str + fin_ctr) = last;
            }
            else {
                *(final_str + fin_ctr) = '@';
            }
	    fin_ctr++;
        }
    }
    if (strchr(final_str, '@') != NULL) {
        printf("I am not Satisfied\n");
    }
    else {
        char *chk = kmem_zalloc(0x50,KM_SLEEP);
        char solution[8] = { 114, 121, 127, 99, 107, 33, 109, 0};
        char *after_xor = kmem_zalloc(50, KM_SLEEP);
        for(size_t ii = 0; ii < strlen(final_str); ii++)
        {   
            *(chk + (strlen(final_str) - ii - 1)) = *(final_str + ii) + sc.xor_ctr;
        }
		++xor_check;
        xor_check = (xor_check+1)* xor_check;
        --xor_check;
        xor_check = xor_check-1 + xor_check * xor_check+1;
        ++xor_check;
        ++xor_check;
        if(sc.xor_ctr < 33 && sc.xor_ctr > 0 && xor_check == 93332)
        {	
            for(size_t ii = 0; ii < strlen(solution); ii++)
            {
                *(after_xor + ii) = *(solution + ii) ^ sc.xor_ctr;
            }
            int result = strncmp(chk, after_xor, strlen(after_xor));
			kmem_free(fin,0x50);
			kmem_free(chk,0x50);
			kmem_free(after_xor,50);
			kmem_free(final_str,0x50);
			kmem_free(part,8);
            return result;
        }
        else
            printf("NOPE\n");
			kmem_free(fin,0x50);
			kmem_free(chk,0x50);
			kmem_free(after_xor,50);
			kmem_free(final_str,0x50);
			kmem_free(part,8);
			return -1;
        }
	kmem_free(fin,0x50);
	kmem_free(final_str,0x50);
	kmem_free(part,8);

	return -1;
}


int
chall2_ioctl(dev_t dev, u_long cmd, void *addr, int flag, struct lwp *l)
{
	int	error = 0;

	switch(cmd) {
		case KREVINC:
			sc.xor_ctr++;
			break;
		case KREVDEC:
			sc.xor_ctr--;
			break;
		case KREVFLAG:
			sc.flag_ready = check_flag();
			break;
		default:
			printf("You need some sleep :) ");
			error = EINVAL; 
	}

	return error;
}

void
get_flag_ready()
{
	char xor_pack[40] = {20, 21, 3, 72, 27, 22, 82, 70, 8, 55, 1, 79, 121, 17, 21, 67, 21, 3, 81, 86, 70, 118, 25, 84, 123, 119, 85, 107, 29, 118, 109, 66, 5, 98, 68, 18, 14, 86, 79, 25};
	int check;
	sha1hash();
	md5hash();
	check = strncmp(sc.md5string, "73c80af68cb7422131787bdae99e180f", strlen(sc.md5string));
	if(check == 0)
	{
		for(size_t i = 0; i < strlen(sc.sha1string); i++)
		{
			*(sc.final_flag + i) = (int)*(sc.sha1string + i) ^ (int)*(xor_pack + i) ^ (int)sc.xor_ctr;
		}
	} else {
		printf("This really shouldn't happen\n");
	}
}


int
chall2_read(dev_t self __unused, struct uio *uio, int flags __unused)
{
	char line[80];
	int e;
	if (sc.flag_ready != 0) {
		snprintf(line, strlen(YOULOSE)+1 , "%s", YOULOSE);
		if ((e = uiomove(line, LEN, uio)))
			return e;
	}
	else {
		get_flag_ready();
		snprintf(line, strlen(sc.final_flag)+1 , "%s", sc.final_flag);
		if ((e = uiomove(line, strlen(sc.final_flag)+1, uio)))
			return e;
	}
	return 0;
}

paddr_t
chall2_mmap(dev_t dev, off_t off, int prot)
{
	paddr_t pa;

	if (off & PAGE_MASK)
                panic("mmap: offset not page aligned");
	if (pmap_extract(pmap_kernel(), (vaddr_t)sc.buffer, &pa))
		return atop(pa);

	return -1;
}

MODULE(MODULE_CLASS_MISC, chall2, NULL);

static int
chall2_modcmd(modcmd_t cmd, void *arg __unused)
{
	/* The major should be verified and changed if needed to avoid
	 * conflicts with other devices. */
	int cmajor = 211, bmajor = -1;

	switch (cmd) {
	case MODULE_CMD_INIT:
		printf("chall2 module loaded.\n");
		if (devsw_attach("chall2", NULL, &bmajor, &chall2_cdevsw,
				&cmajor))
			return ENXIO;	
		return 0;
	case MODULE_CMD_FINI:
		if (sc.refcnt > 0)
			return EBUSY;
		devsw_detach(NULL, &chall2_cdevsw);
		printf("chall2 module unloaded.\n");
		return 0;
	default:
		return ENOTTY;
	}
	return 0;
}
