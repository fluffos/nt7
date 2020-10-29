// action.c
// Written by Lonely@nitan.org

// #pragma save_binary

#include <ansi.h>
#include <function.h>

nosave mixed busy, interrupt;
nosave mapping override;

varargs void start_busy(mixed new_busy, mixed new_interrupt)
{
        object me, ob;
        int    rdc_busy, avd_busy, add_busy;
        int    opp_flag = 0;

        if( !new_busy ) {
                busy = 0;
                return;
        }

        if( !intp(new_busy) && !functionp(new_busy) )
                error("action: Invalid busy action type.\n");

        if( !objectp(me = this_object()) )
                return;

        /*
        if( previous_object() &&
            sscanf(base_name(previous_object()), "/kungfu/skill/%*s") ) {
                start_perform_busy(new_busy);
                return;
        }
        */

        if( intp(new_busy) ) {
                if( functionp(busy) )
                        //error("action: busy conflit.\n");
                        return;

                if( new_busy > 300 ) new_busy = 300;
                rdc_busy = 0;
                avd_busy = 0;
                add_busy = 0;

                // 战斗状态下忙乱及化解忙乱才起作用
                if( me->is_fighting() && previous_object() &&
                    sscanf(base_name(previous_object()), "/kungfu/skill/%*s") ) {
                        avd_busy = me->query_all_buff("avoid_busy");
                        rdc_busy = me->query_all_buff("reduce_busy");
                        if( rdc_busy > 90 ) rdc_busy = 90;
                        if( avd_busy > 90 ) avd_busy = 90;

                        if( objectp(ob = query_temp("last_opponent") ) &&
                            me->is_fighting(ob) ) {
                                add_busy = ob->query_all_buff("add_busy", ob);
                                add_busy = add_busy * (100 - query("reborn/times")*10)/100;
                                if( add_busy > 90 ) add_busy = 90;
                                if( query("reborn/times") > query("reborn/times", ob) )
                                        opp_flag = 1;
                        }
                }

                if( add_busy > 0 )
                        //new_busy += random(add_busy + 1);
                        new_busy += range_random(add_busy/2, add_busy);

                if( new_busy > 1 && random(100) < avd_busy && random(10) < 5 )
                        new_busy = 0;

                if( new_busy > 1 && rdc_busy > 0 )
                {
                        //new_busy -= random(rdc_busy + 1);
                        new_busy -= range_random(rdc_busy/2, rdc_busy);
                        if( new_busy < 1 ) new_busy = 1;
                }

                if( new_busy > 0 && opp_flag > 0 )
                        new_busy = random(new_busy);

                if( new_busy > 1 && playerp(me) &&
                    random(10) < 4 && (query("character") == "狡黠多变" || query("character") == "国士无双") )
                        new_busy--;

                if( new_busy > 0 && playerp(me) && random(10) < 3 && query("special_skill/taxue", me) )
                        new_busy--;
        }

        busy = new_busy;
        if( !intp(new_interrupt) && !functionp(new_interrupt) )
                error("action: Invalid busy action interrupt handler type.\n");

        interrupt = new_interrupt;
        set_heart_beat(1);
}

nomask mixed query_busy() { return busy; }
nomask int is_busy() { return busy != 0; }
nomask void stop_busy() { busy = 0; }

// This is called by heart_beat() instead of attack() when a ppl is busy
// doing something else.
void continue_action()
{
        if( intp(busy) && (busy > 0) ) {
                busy--;
                return;
        } else if( !( functionp(busy) & FP_OWNER_DESTED )) {
                if( !evaluate(busy, this_object()) ) {
                        busy = 0;
                        interrupt = 0;
                }
        } else {
                busy = 0;
                interrupt = 0;
        }
}

void interrupt_me(object who, mixed how)
{
        mixed bak;

        bak = busy;
        busy = 0;

        if( !bak ) return;

        if (intp(bak) && intp(interrupt))
        {
                if (bak < interrupt || who != this_object())
                        return;

                if (intp(how) && how > 0)
                {
                        // reduce busy
                        bak -= how;
                        if (bak < 0) bak = 0;
                }
        } else if( !( functionp(interrupt) & FP_OWNER_DESTED) ) {
                if( evaluate(interrupt, this_object(), who, how) ) {
                        bak = 0;
                        interrupt = 0;
                }
        } else {
                bak = 0;
                interrupt = 0;
        }

        busy = bak;
}

// This function is for temporary conditions's recovery call_outs, bcz
// such recovery function call_out might be destroyed if some wizard
// destructed the object that is reponsible of it, so we let users launch
// the call_out themself. Thus we can make sure the recovery call_out.
//
// Because this could cause a serious security problem, so we need highest
// security check here.
int start_call_out(function fun, int delay)
{
        if( wiz_level(this_object()) > 0 || 1 )
                // I won't bind the function because it will
                // cause a serious security problem.
                call_out("eval_function", delay, fun);
        else
                // if this_object() doesn't be a wizard, I will
                // bind the function, then the player doesn't
                // occur error when the function's owner be
                // destructed.
                call_out("eval_function", delay, bind(fun, this_object()));
        return 1;
}

protected void eval_function(function fun)
{
        if( (functionp(fun) & FP_OWNER_DESTED) )
                return;

        evaluate(fun);
}

// I would let some function override the old function,
// such as the player unconcious/die ...
// It also cause a security problem, so I must check here
nomask int set_override(string index, function fun)
{
        if( !previous_object() ||
                geteuid(previous_object()) != ROOT_UID )
                return 0;

        if( !override )
                override = ([]);

        override[index] = bind(fun, this_object());
        return 1;
}

// only root & (admin) can called me
nomask mixed query_override(string index)
{
        if( !is_root(previous_object()) )
                return 0;

        if( !index ) return override;
        if( !override ) return 0;
        return override[index];
}

// others call me to run the override function, when I return
// zero, the caller will run old execution continue.
nomask int run_override(string index)
{
        function fun;

        if( !override || ! functionp(fun = override[index]) )
                return 0;

        map_delete(override, index);
        if( !sizeof(override) ) override = 0;
        return (*fun)(this_object());
}

// remove override function
nomask void delete_override(string index)
{
        if( !override ) return;
        map_delete(override, index);
        if( !sizeof(override) ) override = 0;
}
