/*---------------------------------------------------------------------------*
 *  xixlog.i - LIBERO dialog interpreter for xixlog.c.                       *
 *  Generated by LIBERO 2.30 on 19 Nov, 1999,  9:55.                         *
 *  Schema file used: smtschm.c.                                             *
 *---------------------------------------------------------------------------*/
    if (agent_lookup (AGENT_NAME))
        return (0);                     /*  Agent already declared           */
    if ((agent = agent_declare (AGENT_NAME)) == NULL)
        return (-1);                    /*  Could not declare agent          */

#if (defined (SINGLE_THREADED))
    agent-> tcb_size     = 0;           /*  No context block                 */
    agent-> max_threads  = 1;           /*    and max. 1 thread              */
#else
    agent-> tcb_size     = sizeof (TCB);
#endif
    agent-> stack_size   = 0;
    agent-> initialise   = initialise_the_thread;
    agent-> maxevent     = 23;
    agent-> maxmodule    = 30;
    agent-> maxstate     = 8;
    agent-> priority     = SMT_PRIORITY_NORMAL;
    agent-> LR_defaults  = 7;
    agent-> LR_nextst    = &_LR_nextst [0][0];
    agent-> LR_action    = &_LR_action [0][0];
    agent-> LR_offset    = _LR_offset;
    agent-> LR_vector    = _LR_vector;
    agent-> LR_module    = _LR_module;
    agent-> LR_mname     = _LR_mname;
    agent-> LR_sname     = _LR_sname;
    agent-> LR_ename     = _LR_ename;