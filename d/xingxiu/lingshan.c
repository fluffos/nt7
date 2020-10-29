// lingshan.c
// Modified by Dumbness, 2003-5-24 0:57

#include <localtime.h>
#include <ansi.h>;
inherit ROOM;

void create()
{
        mixed *local;
        local = localtime(time());

        set("short", "灵山");
        set("long", @LONG
从天池起步，攀上高插云霄、四时积雪的灵山。一到雪线附近，
一股秋菊似的幽香突然袭来，原来朵朵鲜花挺立在这寒风中，给冰雪
世界增添了春色，这就是被叫作 "高山玫瑰" 的雪莲。雪莲单单生长
在这气候严寒、土质贫瘠的冰山雪岭上，每年盛夏开花，一直开到深
秋，不畏冰雪，即使在雪花纷飞中，依然吐苞放瓣，敢於同雪花争艳，
最终与茎同枯而不落。
LONG );
        set("exits", ([
                "down" : "/d/xingxiu/tianchi",
        ]));
        
        if( ( local[LT_MON] >= 4 && local[LT_MON] <= 9 ) && (random(5) == 1) ) 
        {
        
                set("objects", ([
                        DRUG_D("xuelian") : 1,
                ]));
        }

        set("outdoors", "tianshan");
        setup();
}

int valid_leave(object me, string dir)
{
        object *inv;
        int i, flag, j=0;

        inv = all_inventory(me);

        for (i=0; i<sizeof(inv); i++)
                if( query("id", inv[i]) == "xuelian" )
                        j++;

        if( random((int)me->query_skill("dodge")) <= 30
                || ( j > 0 ) )
        {
                me->receive_damage("qi", 100);
                me->receive_wound("qi",  100);
                message_vision(HIR"$N一不小心脚下一滑，... 啊...！\n"NOR, me);
                me->move("/d/xingxiu/tianchi");
                tell_object(me, HIR"你从峰顶梭地一下滑了下来，只觉得浑身无处不疼，还受了几处伤。\n"NOR);
                message("vision",HIR"只见"+query("name", me)+"梭地一下从峰顶上直滑下来，差点儿掉进天池。\n"NOR,environment(me),me);
                if ( j > 0 )
                        for (i=0; i < sizeof(inv); i++) 
                        {
                                if ( !userp(inv[i]) &&
                                        !inv[i]->query_autoload() && 
                                        !query("armor_prop/armor", inv[i]) )
                                {
                                        if( userp(inv[i]) ) continue;
                                        destruct(inv[i]);
                                        flag += 1;
                                }
                        }
                if ( flag ) tell_object(me, "你身上的东西都扑通扑通掉进了天池。\n");
        }
        return ::valid_leave(me, dir);
}

