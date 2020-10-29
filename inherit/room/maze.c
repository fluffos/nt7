// This program is a part of NITAN MudLIB

#include <maze.h>
#include <ansi.h>

inherit ROOM;

void destruct_me();

void create()
{
    set("short", "迷宫");
    set("long", @LONG
这是一间宽敞的石屋，四周巨石垒就的墙壁泛出幽幽的青色光芒，两盏青铜
灯吐出一尺高的火焰，飘忽闪烁，偶然有灯花爆裂的轻响，更令人感到窒息般的
寂静。地上是丈许见方的青石板铺就，房间中央一块白色石板格外醒目，上面雕
刻着细密的图纹，让人不由自主的想上前查看（mazemap）一番。
LONG );
    set("no_clean_up", 1);
    set("no_drop", 1);
    set("no_sleep_room", 1);
    set("born_time", time() );
    
    setup();
}

void init()
{
    object me, room, next_room;
    int xianjing;
    string mazename;
    int damage;
    
    add_action("do_chakan", "mazemap");

    // 添加陷阱程序
    me = this_player();
    room = this_object();
    
    if ( !me ) return;
    
    xianjing=query("maze/xianjing", room);
    if ( !xianjing ) return;
    
    mazename=query("maze/mazename", room);
    if ( !stringp(mazename) ) return;
    
    switch (xianjing)
    {
        case BUSY:
            message_vision(HIR "\n$N脚下一滑，差点摔个嘴啃泥，好不容易稳住身子，才感觉脚踝扭伤了，好痛啊...\n\n" NOR, me);
            me->start_busy(5);
            break;
        case TRIP:
            message_vision(HIR "\n$N一脚踩上了什么东西，身形再也把持不住，猛的向前滑出，只留下一声惊叫久久回荡...\n\n" NOR, me);
            next_room = MAZE_D->trip_maze(mazename, room);
            if ( objectp(next_room) )
            {
                me->move(next_room);
            }
            break;
        case LOSTMAP:
            message_vision(HIR "\n$N只听得脚下一声喀嚓轻响，忽见到房间中央的白色石板闪起一道强光，旋即迅速黯淡下去...\n\n" NOR, me);
            MAZE_D->lostmap_maze(mazename);
            break;
        case CHANGEMAP:
            MAZE_D->init_maze(mazename);            
            message_vision(HIR "\n$N一脚踩到了什么东西，急惶惶的把脚收起，却已经听到阵阵沉闷的声音从地下响起...\n" NOR
                + HIR "只见四周光影晃动，整个房间似乎在快速移动，等一切安静下来，周遭景象似乎有所改变。\n\n" NOR, me);
            break;
        case WOUND:
            message_vision(HIR "\n只听得一声机括脆响，$N下意识的赶紧避让，却为时已晚，一支钢弩不偏不倚正好射中$N。\n" NOR
                + HIR "$N惊怒交加，伤口处痛彻心扉，终于忍不住连声哀叫起来。\n\n" NOR, me);
            damage=query("max_qi", me);
            damage = damage/10 + random(damage/10) + 1;
            me->receive_wound("qi", damage);
            break;
        default:
            break;
    }
    
    // 把这个房间的陷阱去除
    delete("maze/xianjing", room);
    MAZE_D->remove_xianjing(mazename, room);
    
    return;    
}

int clean_up()
{
    if (time() - query("born_time") > MAZE_LIFT_CYCLE)
    {
        destruct_me();
        return 0;
    }
    
    return 1;
}

void destruct_me()
{
    object *obs;
    int i, user_num;

    obs = filter_array(all_inventory(), (: userp($1) || playerp($1) :));
    user_num = sizeof(obs);
    if (user_num)
    {
                message("vision", HIW "\n你突然觉得周围的一切都晃动起来，逐渐化为虚无...\n\n" NOR, this_object());
        for (i = 0; i < user_num; i ++)
        {
            obs[i]->move(ROOM_EXIT_FILE);
            message("vision", "地面忽然打开一个暗道，只见" + obs[i]->name() + "钻了出来。\n", 
                    environment(obs[i]), ({ obs[i] }));
        }
    }

    destruct(this_object());
    return;
}

int do_chakan(string arg)
{
    object me, room;
    string map = "";
    string mazename;
    
    
    me = this_player();
    if (!me) return 0;
    
    room = this_object();
    mazename=query("maze/mazename", room);
    
    if (!stringp(mazename))
    {
        map = "你仔细的查看石板，但是模模糊糊的什么都看不清...\n";
    }
    else
    {
        if (wizardp(me) && !stringp(arg) )
            map = MAZE_D->get_deep_map(mazename, room);
        else
            map = MAZE_D->get_comm_map(mazename, room);
    }

    if (!stringp(map))
    {
        map = "你仔细的查看石板，但是模模糊糊的什么都看不清...\n";
    }

    me->start_more(map);
    
    return 1;
}

int valid_leave(object me, string dir)
{
    if( dir == "out" && userp(me) && query("exits/out", this_object()) )
    {
        MAZE_D->check_maze(query("maze/mazename", this_object()));
    }

    return ::valid_leave(me, dir);
}
