// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit ROOM;

#define BUSY        1     // 让玩家BUSY      
#define TRIP        2     // 让玩家摔到别的房间   
#define LOSTMAP     3     // 让迷宫地图失效       
#define CHANGEMAP   4     // 让迷宫地图刷新       
#define WOUND       5     // 让玩家受伤          

void create()
{
        set("short", "迷宫");
        set("long", @LONG
这是一间宽敞的石屋，四周巨石垒就的墙壁泛出幽幽的青色光芒，两盏青铜
灯吐出一尺高的火焰，飘忽闪烁，偶然有灯花爆裂的轻响，更令人感到窒息般的
寂静。地上是丈许见方的青石板铺就，房间中央一块白色石板格外醒目，上面雕
刻着细密的图纹，让人不由自主的想上前查看（mazemap）一番。
LONG );
        setup();
}

void init()
{
        object me, room, next_room;
        int trap;
        object mazeobj;
        int damage;

        room = this_object();  
        if( !(me = this_player()) ) return;
        if( !userp(me) ) return;
        if( !(trap=query("maze/trap", room)))return ;
        mazeobj=get_object(query("mazeobj", room));
            
        switch( trap ) {
        case BUSY:
                message_vision(HIR "\n$N脚下一滑，差点摔个嘴啃泥，好不容易稳住身"
                        "子，才感觉脚踝扭伤了，好痛啊...\n\n" NOR, me);
                me->start_busy(5);
                break;
        case TRIP:
                message_vision(HIR "\n$N一脚踩上了什么东西，身形再也把持不住，猛"
                        "的向前滑出，只留下一声惊叫久久回荡...\n\n" NOR, me);
                next_room = mazeobj->trip_maze(room);
                if( objectp(next_room) )
                        me->move(next_room);
                break;
        case LOSTMAP:
                message_vision(HIR "\n$N只听得脚下一声喀嚓轻响，忽见到房间中央的"
                        "白色石板闪起一道强光，旋即迅速黯淡下去...\n\n" NOR, me);
                //mazeobj->set_display_map(0);
                break;
        case CHANGEMAP:
                mazeobj->init_maze(room);
                message_vision(HIR "\n$N一脚踩到了什么东西，急惶惶的把脚收起，却"
                        "已经听到阵阵沉闷的声音从地下响起...\n" NOR 
                        HIR "只见四周光影晃动，整个房间似乎在快速移动，等一切安静"
                        "下来，周遭景象似乎有所改变。\n\n" NOR, me);
                break;
        case WOUND:
                message_vision(HIR "\n只听得一声机括脆响，$N下意识的赶紧避让，却"
                        "为时已晚，一支钢弩不偏不倚正好射中$N。\n" NOR 
                        HIR "$N惊怒交加，伤口处痛彻心扉，终于忍不住连声哀叫起来。"
                        "\n\n" NOR, me);
                damage=query("max_qi", me);
                damage = damage/10 + random(damage/10) + 1;
                me->receive_wound("qi", damage);
                break;
        default:
                break;
        }
    
        // 把这个房间的陷阱去除
        delete("maze/trap");
        mazeobj->remove_trap(room);
        return;    
}
