#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "巨木旗机关");
        set("long", @LONG
你眼前骤然一暗，朦胧中，只见左右前后，到处都是铺天盖地的
不知名的巨树，好象松柏，又似冷杉，簇在一起，密实的枝叶象一蓬
蓬巨伞恒伸向天空，遮天蔽日。你似乎迷失了方向，象没头苍蝇般到
处乱闯。
LONG );
        set("exits", ([
                "east" :  __FILE__,
                "west" :  __FILE__,
                "south" : __FILE__,
                "north" : __FILE__,
        ]));
        set("no_clean_up", 0);
        setup();
}
void init()
{
        if (this_player()->query_family() == "明教") return;
        this_player()->receive_damage("qi", 15);
        this_player()->receive_wound("qi",  15);
        message_vision(HIG"突然一阵巨木桩遮天蔽日凌空砸向$N！\n"NOR, this_player());
}

int valid_leave(object me, string dir)
{
        int total_steps ;
        mapping myfam;

        total_steps = 10 ;
        if ( total_steps <= 0 ) total_steps = 1 ;
        myfam = (mapping) query("family", this_player());
        if(myfam && myfam["family_name"] == "明教")
                total_steps = 1 ;
        if ( dir == "west")
                addn_temp("mingjiao/steps",1,me);
        if ( dir == "east")
                addn_temp("mingjiao/steps",-1,me);

        if (query_temp("mingjiao/steps", me) == total_steps)
        {
                me->move(__DIR__"jmqshenmu");
                delete_temp("mingjiao/steps", me);
                tell_object(me, "你走了半天，终于走到神木。真累! \n");
                return 1;
        }

        if (query_temp("mingjiao/steps", me) == - total_steps )
        {
                me->move(__DIR__"jmqshulin6");
                delete_temp("mingjiao/steps", me);
                tell_object(me, "你走了半天，终于走到神木。真累! \n");
                return 1;
        }

        return ::valid_leave(me,dir);
}