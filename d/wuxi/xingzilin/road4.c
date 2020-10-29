// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "杏林小道");
        set("long", @LONG
这是林中小路，高大的杏树密布。浓雾飘绕五丈外不可见人，周围
杀喊的声音不时传来。西面远望去有一大堆柴禾挡着去路，柴禾缝隙中
隐隐约约露出个黑黝黝的山洞口。
LONG);
        set("no_sleep_room",1);
        set("no_magic", 1);
        set("exits", ([
                        "north"  : __DIR__"dynamic/dxlin1",
                        "west" : __FILE__,
                        "south" : __DIR__"xxlin9",
        ]));
           set("objects", ([ 
                     "/clone/npc/walker"  : 3, 
           ])); 

setup();


}

int valid_leave(object me, string dir)
{
        if (dir == "west" && ! playerp(me)) return 0; //阻挡npc逃进安全区
        
        if (dir == "west")
         {
                if (me->is_fighting())//可能处于被追杀中
                {
                        if (random(2))
                        {
                                tell_object(me,YEL"你急急忙忙地把柴禾扒开一个缝隙，纵身钻了进去......\n"NOR); 
                                me->move(__DIR__"sleeproom");
                                tell_object(me, CYN "你惊魂未定，但发现后面的脚步声似乎停下来了。\n" NOR );
                                return 1;
                        }
                        else 
                        {
                                me->start_busy(2+random(2));
                                return notify_fail(YEL"你吓得亡魂大冒，冲到柴禾堆前疯狂地乱刨......\n"NOR);
                        }
                }
                else
                {
                        tell_object(me,YEL"你不慌不忙地把柴禾扒开一个缝隙，纵身钻了进去......\n"NOR); 
                        me->move(__DIR__"sleeproom");
                        return 1;
                }
         }

        return ::valid_leave(me, dir);
}

