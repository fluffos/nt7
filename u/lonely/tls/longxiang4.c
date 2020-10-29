#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "西练武场-龙象台");
        set("long",@LONG
龙象台是一个宽大的平台，是寺中僧侣练习武艺的地方，台边
摆有木桩、梅花桩、沙袋、沙盆等练功设施和各种僧家武器。几个
年轻的僧人正在一旁相互切磋。西边一扇门通往塔林，门口站着位
禅师。
LONG);
        set("outdoors","dali");
        set("exits", ([
                "east" : __DIR__"longxiang1",
                "west" : __DIR__"shanlu-1",
	             	]));
set("objects",([
		__DIR__"npc/liao-xing" : 1,
			]));

        set("coor/x",-410);
  set("coor/y",-320);
   set("coor/z",30);
   setup();
}


int valid_leave(object me, string dir)
{
       string name, new_name;
        name = me->query("name");
        new_name = name[0..0];

    if (me->query("family/family_name") != "天龙寺" &&
            present("liaoxing chanshi", environment(me)) &&
	    dir =="west")
            return notify_fail("了行禅师大师把手一伸，拦住了你的去路，\n"+
           "说道：阿弥陀佛，施主不是天龙弟子，不得到处乱闯。\n");


        if (new_name != "本" && present("liaoxing chanshi", environment(me)) && dir =="west")
            return notify_fail("了行禅师把手一伸，拦住了你的去路，\n"+
           "说道：阿弥陀佛，你的辈分不够，不要去塔林扰乱清净。\n");

        return ::valid_leave(me, dir);
}
