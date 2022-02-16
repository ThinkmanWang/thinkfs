#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define THINKFS_ROOT "thinkfs"
static struct proc_dir_entry *thinkfs_root = NULL;

static int hello_proc_show(struct seq_file *m, void *v) {
    seq_printf(m, "Hello World!\n");
    return 0;
}

static int hello_proc_open(struct inode *inode, struct  file *file) {
    return single_open(file, hello_proc_show, NULL);
}

static const struct proc_ops hello_proc_fops = {
    .proc_open = hello_proc_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init hello_proc_init(void) {
    thinkfs_root = proc_mkdir(THINKFS_ROOT, NULL);
    if (NULL == thinkfs_root) {
        printk("cannot mkdir thinkfs");
        return -ENOMEM;
    }

    proc_create("thinkfs", 0, thinkfs_root, &hello_proc_fops);
    return 0;
}

static void __exit hello_proc_exit(void) {
    remove_proc_entry("thinkfs", thinkfs_root);
    remove_proc_entry(THINKFS_ROOT, NULL);
}

MODULE_LICENSE("GPL");
module_init(hello_proc_init);
module_exit(hello_proc_exit);
