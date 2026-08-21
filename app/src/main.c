#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(demo, LOG_LEVEL_DBG);

#define STACK_SIZE 1024

#define PRIO_A 5
#define PRIO_B 5

#define LOW_PRIO 7
#define MED_PRIO 5
#define HIGH_PRIO 3
#define COOP_PRIO (-1)

volatile int counter = 0;

#define INCREMENTS 1000000
K_MUTEX_DEFINE(counter_mutex);

void incrementer_thread(char *p1, void *p2, void *p3)
{
    for (int i = INCREMENTS; i > 0; i--) {
        k_mutex_lock(&counter_mutex, K_FOREVER);
        counter++;
        k_mutex_unlock(&counter_mutex);
    }
    printk("Thread %s: counter = %d\n", p1, counter);
}


K_THREAD_DEFINE(incrementer1, STACK_SIZE, incrementer_thread,
                "Incrementer 1", NULL, NULL, HIGH_PRIO, 0, 0);
K_THREAD_DEFINE(incrementer2, STACK_SIZE, incrementer_thread,
                "Incrementer 2", NULL, NULL, HIGH_PRIO, 0, 0);
#if 0
void t_low_fn(void *p1, void *p2, void *p3)
{
    while (1) {
        printk("T_LOW is running\n");
        k_msleep(300);
    }
}
void t_med_fn(void *p1, void *p2, void *p3)
{
    while (1) {
        printk("T_MED is running\n");
        k_msleep(200);
    }
}
void t_high_fn(void *p1, void *p2, void *p3)
{
    while (1) {
        printk("T_HIGH is running\n");
        k_msleep(100);
    }
}

void t_coop_fn(void *p1, void *p2, void *p3)
{
    for (int i = 0; i < 5; i++) {
        printk("T_COOP is running (%d)\n", i);
        k_busy_wait(100000);
    }
    k_yield();
    printk("T_COOP is exiting\n");
}

K_THREAD_DEFINE(t_low, STACK_SIZE, t_low_fn,
                NULL, NULL, NULL, LOW_PRIO, 0, 0);
K_THREAD_DEFINE(t_med, STACK_SIZE, t_med_fn,
                NULL, NULL, NULL, MED_PRIO, 0, 0);
K_THREAD_DEFINE(t_high, STACK_SIZE, t_high_fn,
                NULL, NULL, NULL, HIGH_PRIO, 0, 0);
K_THREAD_DEFINE(t_coop, STACK_SIZE, t_coop_fn,
                NULL, NULL, NULL, COOP_PRIO, 0, 0);

void thread_a_fn(void *p1, void *p2, void *p3)
{
    while (1) {
        k_msleep(200);
    }
}

void thread_b_fn(void *p1, void *p2, void *p3)
{
    while (1) {
        k_msleep(300);
    }
}

K_THREAD_DEFINE(thread_a, STACK_SIZE, thread_a_fn,
                NULL, NULL, NULL, PRIO_A, 0, 0);
K_THREAD_DEFINE(thread_b, STACK_SIZE, thread_b_fn,
                NULL, NULL, NULL, PRIO_B, 0, 0);
#endif

int main(void)
{
    return 0;
}

