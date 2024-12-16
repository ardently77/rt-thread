#include <am.h>
#include <klib.h>
#include <rtthread.h>

void wrapper_function();

typedef struct ex_thread {
  rt_base_t from;
  rt_base_t to;
}Ex_Thread;


static Context* ev_handler(Event e, Context *c) {
  rt_thread_t pcb = rt_thread_self();
  Ex_Thread *thread = (Ex_Thread *)pcb->user_data;
  switch (e.event) {
    case EVENT_YIELD: if(thread->from) *((Context**)thread->from) = c; c = *(Context **)thread->to; break;
    case EVENT_IRQ_TIMER: return c; break;
    default: printf("Unhandled event ID = %d\n", e.event); assert(0);
  }
  return c;
}

void __am_cte_init() {
  cte_init(ev_handler);
}

void rt_hw_context_switch_to(rt_ubase_t to) {

  Ex_Thread root;
  Ex_Thread *thread = &root;
  thread->to = to;
  thread->from = 0;
  rt_thread_t pcb = rt_thread_self();
  rt_ubase_t s_pcb = pcb->user_data;
  pcb->user_data = (rt_base_t)thread;
  yield();
  pcb->user_data = s_pcb;
  
}

void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to) {

  Ex_Thread root;
  Ex_Thread *thread = &root;
  thread->from = from;
  thread->to = to;
  rt_thread_t pcb = rt_thread_self();
  rt_ubase_t s_pcb = pcb->user_data;
  pcb->user_data = (rt_base_t)thread;
  yield();
  pcb->user_data = s_pcb;

}

void rt_hw_context_switch_interrupt(void *context, rt_ubase_t from, rt_ubase_t to, struct rt_thread *to_thread) {
  assert(0);
}

rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter, rt_uint8_t *stack_addr, void *texit) {

  stack_addr = (rt_uint8_t *)(((uintptr_t)stack_addr + (sizeof(uintptr_t) - 1)) & ~(sizeof(uintptr_t) - 1));
  // rt_uint64_t *stk = (rt_uint64_t *)stack_addr;

  // stk--;
  // *stk = (rt_uint64_t)tentry;
  // stk--;
  // *stk = (rt_uint64_t)parameter;
  // stk--;
  // *stk = (rt_uint64_t)texit;
  rt_ubase_t *stk = (rt_ubase_t *)stack_addr;

  stk--;
  *stk = (rt_ubase_t)tentry;
  stk--;
  *stk = (rt_ubase_t)parameter;
  stk--;
  *stk = (rt_ubase_t)texit;

  Context *cp = kcontext((Area) {.end = (rt_uint8_t *)stk}, wrapper_function, stk);
   
  return (rt_uint8_t *)cp;

  //assert(0);
  //return NULL;
}

void wrapper_function(uintptr_t *stack_ptr) {

  rt_ubase_t *sp = (rt_ubase_t *)stack_ptr; 
 
  void (*texit)(void) = (void (*)(void))*sp; 
  sp++;

  void *parameter = (void *)*sp;
  sp++; 

  void (*tentry)(void *) = (void (*)(void *))*sp;
  sp++;

  tentry(parameter);

  texit();

}
