// trap.c 掘地为牢
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>

inherit F_CLEAN_UP;
void digging(object, int);
void create() { seteuid(getuid()); }

mapping default_dirs = ([
        "north":        "北",
        "south":        "南",
        "east":         "东",
        "west":         "西",
        "northup":      "北边",
        "southup":      "南边",
        "eastup":       "东边",
        "westup":       "西边",
        "northdown":    "北边",
        "southdown":    "南边",
        "eastdown":     "东边",
        "westdown":     "西边",
        "northeast":    "东北",
        "northwest":    "西北",
        "southeast":    "东南",
        "southwest":    "西南",
        "up":           "上",
        "down":         "下",
        "out":          "外",
        "enter":        "里",
]);
string *place = ({ "寺", "庙", "店", "楼", "铺", "阁", "祠", "屋", 
"院", "门", "街", "庄", "斋", "桥", "社", "园", "馆", "堂", "室", 
"厅", "房", "寓", "库", "殿", "营", "厩" ,"船","舟","坪"});

int main(object me, string arg)
{
        object roomfrom, roomto, roomtrap, *inv, tool;
        mapping exits;
        string dir, from, to, *dirs;
        int i, depth;

        if( query("shen", me) >= 0 && !wizardp(me) )
                return notify_fail("你出身正派，竟敢打这种歪门邪道的主意？！\n");
        if( query("combat_exp", me) >= 100000 && !wizardp(me) )
                return notify_fail("如此下三烂的把戏，象你这样的高手不屑为之吧？！\n");
        if( me->query_skill("digging", 1) <= 30)
                return notify_fail("你这点本事都没学全，如何会挖掘陷阱？\n");
        if( me->is_fighting() )
                return notify_fail("一边打架一边挖掘？你真是活腻了！\n");
        if( me->is_busy() )
                return notify_fail("你现在正忙着！\n");
                tool= present("shenlong qiao", me);
        if(!tool && !wizardp(me))
      return notify_fail("先得找把趁手的工具吧？\n");
        if( !query("dig_times", tool) )
                return notify_fail("得找把趁手的工具吧?\n");
        if( query("dig_times", tool) == 1 )
        {
                message_vision(GRN "\n$N偷偷摸摸地举起铁锹，一锹挖下去，“啪”地一声木柄断了。。。\n\n" NOR, me);
                tool->unequip();
                tool->reset_action();
                set("name",query("name",  tool)+"的破片", tool);
                tool->move(environment(me));
                set("value", 0, tool);
                set("weapon_prop", 0, tool);
                set("id", "tieqiao", tool);
        }
        inv = all_inventory(environment(me));
        if( sizeof(inv) > 0)
        for(i=0; i<sizeof(inv); i++)
        {
                if( userp(inv[i]) && inv[i] != me )
                        return notify_fail("胆子这么大？现在可有旁人在场，不能挖！\n");
        }
        if( !arg || !query("exits/"+arg, environment(me)) )
                return notify_fail("你往哪个方向设陷阱？\n");
        if( strsrch(arg, "jump") >= 0  
//        ||
//                strsrch(arg, "up") >= 0 ||
//                strsrch(arg, "down") >= 0 ||
//                strsrch(arg,"out") >=0 ||
//                strsrch(arg,"enter") >=0 
         )
                return notify_fail("你不能往这个方向设陷阱！\n");
        if( !query("trap_room", environment(me)) )
                roomfrom = environment(me);
        else return notify_fail("你不能在陷阱之内再设陷阱！\n");
        if( !query("outdoors", roomfrom) )
                return notify_fail("你不能这里挖掘陷阱！\n");
        if( sizeof(query("exits", roomfrom)) >= 4 )
                return notify_fail("这里是通衢大道，你不能此乱挖陷阱！\n");
/*
        if( query("cost", roomfrom) <= 1 )
                return notify_fail("此处土质坚实，似乎难以挖掘陷阱！\n");
*/
        if( !(roomto=find_object(query("exits/"+arg, roomfrom))) )
                roomto=load_object(query("exits/"+arg, roomfrom));
        if( query("trap_room", roomto) )
                return notify_fail("那边已经有了个陷阱！\n");
        if( !query("outdoors", roomto) )
                return notify_fail("你不能在别人房门口乱挖！\n");
        for (i=0; i<sizeof(place); i++)
                if( strsrch(query("short", roomfrom),place[i]) >= 0 || 
                        strsrch(query("short", roomto),place[i]) >= 0 )
                        return notify_fail("这里的路面不适合挖陷阱！\n");

        depth = me->query_skill("digging", 1)*10
                + me->query_str()*2 
                + me->query_int()*2 
                + me->query_kar()*2
                +query("qi", me)/2;

        if( query("qi", me)<depth*query("cost", roomfrom)/10 )
                return notify_fail("你的力气不够了！\n");
        roomtrap = new("/clone/misc/traproom");
        set("depth", depth/3+random(depth*2/3), roomtrap);
        set("owner", me, roomtrap);
        set("limit", me->query_skill("digging",1)/10, roomtrap);
        set("roomfrom", roomfrom, roomtrap);
        set("from", arg, roomtrap);

        if( !undefinedp(default_dirs[arg]) ) dir = default_dirs[arg];
        else dir = arg;
        if(objectp(roomfrom))
                set("exits/"+arg, file_name(roomtrap), roomfrom);
        if(objectp(roomto))
        {
                if( strsrch(arg, "up") >= 0 || strsrch(arg, "down") >= 0 )
                        set("exits/"+arg, file_name(roomto), roomtrap);
                else set("exits/" + arg + "up", file_name(roomto), roomtrap);
                set("roomto", roomto, roomtrap);
                exits=query("exits", roomto);
                dirs = keys(exits);
                for(i=0; i<sizeof(dirs); i++)
                {
                        if( exits[dirs[i]] == file_name(roomfrom) )
                        {
                                set("exits/"+dirs[i], file_name(roomtrap), roomto);
                                set("exits/"+dirs[i]+"up", file_name(roomfrom), roomtrap);
                                set("to", dirs[i], roomtrap);
                                break;
                        }
                }
        }

        if(objectp(roomfrom) && objectp(roomto))
        {
                set("exits/jump"+query("from", roomtrap), file_name(roomto), roomfrom);
                set("exits/jump"+query("to", roomtrap), file_name(roomfrom), roomto);
        }

        message_vision(GRN "\n$N偷偷摸摸地举起铁锹，朝着" + dir + "方猛挖一通。。。\n\n" NOR, me);
        addn("dig_times", -1, tool);
        remove_call_out("digging");
        call_out("digging", depth/100, me, depth);
        me->start_busy(depth/100);

        return 1;
}

void digging(object me, int depth)
{
        if( me->is_busy() )
        {
                call_out("digging", 3, me, depth);
                if(random(5)==1) message_vision(GRN "\n$N起劲地往地下挖着挖着。。。\n" NOR, me);
        }
        else        
        {
                me->improve_skill("digging", depth / 20);
                me->receive_damage("qi",depth*(query("cost", environment(me)))/10,"挖陷阱累死了");
                tell_object(me, "你大汗淋漓地挖好了一个陷阱！\n");
        }
}

int help (object me)
{
        write(@HELP
指令格式 : [trap <方向>]

这个指令让你向某个方向挖掘一个陷阱。

HELP
);
        return 1;
}
