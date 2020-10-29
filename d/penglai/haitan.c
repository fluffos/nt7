#include <ansi.h>
inherit ROOM;

#define MEMBER_D          "/adm/daemons/memberd"

void create()
{
        set("short", "海滩");
        set("long", @LONG
这里就是蓬莱仙岛了。北边是一望无际的大海，放眼望去，整
个岛被仙气笼罩，前方不远处是一片竹林，阵阵梵音传出，令人心
旷神怡。
LONG);

        set("exits",([
                "south" :__DIR__"zhulin1",
        ]));
        set("outdoors", "penglai");
        //set("valid_startroom", 1);
        set("no_clean_up", 1);
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛 
        set("no_fight", 1);       

        set("objects", ([
               // __DIR__"npc/milu-shangren" : 1,
        ]));
       
        set("region", "penglai");
        setup();
        "/clone/board/penglai_shibi"->foo(); 
}

void init()
{
        if (base_name(this_player()) == "/d/penglai/npc/qingmianshou")
        {
                destruct(this_player());
                return;
        }
                
        if (0)
        {
                   // 活动结束了，移动回客店
                   if (random(2))
                   {
                           this_player()->move("/d/city/wumiao");
                           set("startroom", "/d/city/wumiao", this_player());
                   }
                   else
                   {
                           this_player()->move("/d/city/kedian");
                           set("startroom", "/d/city/kedian", this_player());
                   }


        }
        set("startroom", base_name(this_object()), this_player());
        this_player()->save();
}

int valid_leave(object me, string dir)
{
        object guarder;

        if (dir == "south")
        {
                if( !MEMBER_D->is_valid_member(query("id", me)) )
                        return notify_fail("只允许有效会员进入蓬莱岛！\n");
        }

        return 1;
}
