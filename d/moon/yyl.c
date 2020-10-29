
inherit ROOM;
void create()
{
	set("short", "月影楼");
	set("long", @LONG
此处群墙下面是白石台阶，雕成朵朵莲花模样，
屋子里是大理石砌成纹理，显得富丽而又不落俗套。
LONG    );
	set("exits", ([ 
  "up" : __DIR__"yyl1",
  "northdown" : __DIR__"froom1",
  "southdown" : __DIR__"qfg",
]));
        set("objects",([
                        __DIR__"npc/guards3" : 1,
       	]) );
	set("coor/x",-30);
	set("coor/y",1140);
        set("coor/z",70);
	setup();
}
int valid_leave(object me, string dir)
{
        if (  (dir == "up")
 &&((string)me->query("class") != "bandit") 
//  && ((string)me->query("family/family_name") != "圆月山庄")
           && objectp(present("guards", environment(me))) )
        return notify_fail("守卫挡住你道；非本庄第子不得擅闯月影楼！。\n");
        return ::valid_leave(me, dir);
}
