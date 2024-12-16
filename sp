src/scheduler_up.c:204:    to_thread->stat = RT_THREAD_RUNNING;
src/scheduler_up.c:208:    rt_hw_context_switch_to((rt_ubase_t)&to_thread->sp);
src/scheduler_up.c:277:                to_thread->stat = RT_THREAD_RUNNING | (to_thread->stat & ~RT_THREAD_STAT_MASK);
src/scheduler_up.c:285:                         RT_NAME_MAX, to_thread->parent.name, to_thread->sp,
src/scheduler_up.c:299:                            (rt_ubase_t)&to_thread->sp);
src/scheduler_up.c:330:                            (rt_ubase_t)&to_thread->sp, from_thread, to_thread);
src/scheduler_mp.c:229:    to_thread->oncpu = rt_hw_cpu_id();
src/scheduler_mp.c:232:    to_thread->stat = RT_THREAD_RUNNING;
src/scheduler_mp.c:235:    rt_hw_context_switch_to((rt_ubase_t)&to_thread->sp, to_thread);
src/scheduler_mp.c:336:            to_thread->oncpu = cpu_id;
src/scheduler_mp.c:345:                to_thread->stat = RT_THREAD_RUNNING | (to_thread->stat & ~RT_THREAD_STAT_MASK);
src/scheduler_mp.c:353:                         RT_NAME_MAX, to_thread->parent.name, to_thread->sp,
src/scheduler_mp.c:363:                        (rt_ubase_t)&to_thread->sp, to_thread);
src/scheduler_mp.c:470:            to_thread->oncpu = cpu_id;
src/scheduler_mp.c:480:                to_thread->stat = RT_THREAD_RUNNING | (to_thread->stat & ~RT_THREAD_STAT_MASK);
src/scheduler_mp.c:494:                        (rt_ubase_t)&to_thread->sp, to_thread);
