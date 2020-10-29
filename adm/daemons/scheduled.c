// This program is a part of NT MudLIB

#include <ansi.h>

#define EVENT_LOOP              0
#define EVENT_EUID              1
#define EVENT_CUR_TIME          2
#define EVENT_MAX_TIME          3
#define EVENT_OBJECT            4
#define EVENT_FUNCTION          5
#define EVENT_ARGUMENT          6
#ifdef DEBUG
#define monitor(x)              CHANNEL_D->do_channel(this_object(), "sys", x)
#else
#define monitor(x)
#endif

inherit F_DBASE;

nosave int last_update_time;
nosave int handle_id;
nosave mapping events = allocate_mapping(0);

int clean_up() { return 1; } 

void remove(string euid)
{
        if( !this_player() )
                return;

        if( sizeof(events) > 0 )
                error("排程精灵：目前正在执行排程系统，你不能摧毁排程精灵。\n");
}

int evaluate_event(int id)
{
        mixed event;

        if( undefinedp(event = events[id]) ) return 0;
        if( !event[EVENT_OBJECT] ) return 0;
        if( !event[EVENT_EUID] ) return 0;

        seteuid(event[EVENT_EUID]);

        if( functionp(event[EVENT_OBJECT]) )
        {
                monitor(sprintf("执行函数 %O", event[EVENT_OBJECT]));
                evaluate(event[EVENT_OBJECT]);
        } else {
                mixed args = ({ event[EVENT_FUNCTION] }) + event[EVENT_ARGUMENT..sizeof(event)-1];
                monitor(sprintf("执行 %O->%s", event[EVENT_OBJECT], event[EVENT_FUNCTION]));
                monitor(sprintf("call_other(%O, %O)", event[EVENT_OBJECT], args));
                call_other(event[EVENT_OBJECT], args);
        }

        seteuid(ROOT_UID);
        return 1;
}

mixed query_events()
{
        return events;
}

varargs int set_event(mixed time, int loop, mixed ob, mixed func, mixed args...)
{
        mixed event;

        if( !ob ) error("参数过少");
        if( functionp(ob) )
                event = ({ loop, geteuid(previous_object()), 0, time, ob });
        else
                event = ({ loop, geteuid(previous_object()), 0, time, ob, func }) + args;

        // Added by Lonely
        foreach( int id, mixed et in events )
                if( et[EVENT_LOOP] == event[EVENT_LOOP] &&
                    et[EVENT_EUID] == event[EVENT_EUID] &&
                    array_eqv(et[EVENT_MAX_TIME..sizeof(event)-1],
                    event[EVENT_MAX_TIME..sizeof(event)-1]) )
                        map_delete(events, id);

        events[handle_id] = event;

        // if( event[EVENT_LOOP] ) evaluate_event(handle_id);
        return handle_id++;
}

void delete_event(int handle)
{
        if( !undefinedp(events[handle]) )
                map_delete(events, handle);
}

void delete_events()
{
        events = allocate_mapping(0);
}

void check_event()
{
        foreach( int id, mixed event in events )
                if( !event[EVENT_OBJECT] )
                        // 删除已遗失物件或函式指标的事件
                        map_delete(events, id);
}

mixed query_event(int handle)
{
        return events[handle];
}

void heart_beat()
{
        int i;

        if( !sizeof(events) ) return;
        if( !last_update_time ) last_update_time = time();

        i = time() - last_update_time;  // 记算每次心跳之时间差
        last_update_time = time();      // 记录最后一次心跳时间

        foreach( int id, mixed event in events ) {
                if( undefinedp(events[id]) ) continue; 
                if( !event[EVENT_OBJECT] ) {       // 删除已遗失物件或函式指标的事件
                        map_delete(events, id);
                        continue;
                } if( event[EVENT_CUR_TIME] < event[EVENT_MAX_TIME] ) {       // 未超过事件循环时间
                        event[EVENT_CUR_TIME] += i;
                } else {       // 已超过事件循环时间
                        evaluate_event(id);
                        event[EVENT_CUR_TIME] = 0;
                        if( !event[EVENT_LOOP] ) map_delete(events, id); // 执行后删除
                }
        }
}

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "排程精灵");
        monitor("排程系统已经启动。");
        // CHANNEL_D->do_channel(this_object(), "sys", "排程系统已经启动。");

        set_heart_beat(1);
}

void start_events()
{
        if( !query_heart_beat() )
                set_heart_beat(1); 
}
