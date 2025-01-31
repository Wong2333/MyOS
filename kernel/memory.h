#ifndef __KERNEL_MEMORY_H
#define __KERNEL_MEMORY_H
#include "stdint.h"
#include "bitmap.h"

//核心数据结构，虚拟内存池，有一个位图与其管理的起始虚拟地址
struct virtual_addr {
   struct bitmap vaddr_bitmap;      // 虚拟地址用到的位图结构 
   uint32_t vaddr_start;            // 虚拟地址起始地址
};

extern struct pool kernel_pool, user_pool;
void mem_init(void);

#define	 PG_P_1	  1	// 页表项或页目录项存在属性位
#define	 PG_P_0	  0	// 页表项或页目录项存在属性位
#define	 PG_RW_R  0	// R/W 属性位值, 读/执行
#define	 PG_RW_W  2	// R/W 属性位值, 读/写/执行
#define	 PG_US_S  0	// U/S 属性位值, 系统级
#define	 PG_US_U  4	// U/S 属性位值, 用户级


/* 内存池标记,用于判断用哪个内存池 */
enum pool_flags {
   PF_KERNEL = 1,    // 内核内存池
   PF_USER = 2	     // 用户内存池
};
void* get_kernel_pages(uint32_t pg_cnt);//申请 内核页，并且直接完成内存映射,初始化内存全0
void* malloc_page(enum pool_flags pf, uint32_t pg_cnt);//申请 页 ，可以指定 内核页 还是 用户页
void malloc_init(void);
uint32_t* pte_ptr(uint32_t vaddr);//获取虚拟地址的 页项地址
uint32_t* pde_ptr(uint32_t vaddr);//获取虚拟地址的 页目录项地址
uint32_t addr_v2p(uint32_t vaddr);
void* get_user_pages(uint32_t pg_cnt);
void* get_a_page(enum pool_flags pf, uint32_t vaddr);


#endif

