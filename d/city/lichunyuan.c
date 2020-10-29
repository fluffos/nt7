// Room: /city/lichunyuan.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "丽春院");
        set("long", @LONG
你一走进来，一眼就看到大厅的墙上挂着一幅幅春宫图(tu)，一
下子就明白了这是什么地方。厅内到处张灯结彩，香气扑鼻。几名打
扮得妖里妖气的女人分站两旁对你发出媚笑。主人韦春芳上上下下、
前前后后招呼着客人。从楼上传来了阵阵打情骂俏的声音。
LONG );
	set("objects", ([
                CLASS_D("gaibang") + "/kongkong" : 1,
                "/d/city/npc/wei" : 1,
                "/d/city/npc/mao18" : 1, 
	]));

	set("item_desc", ([
		"cannotsawtu" :
"                                      Ο        Ο          Ο             
                                    ┌│        │          │
      ┌—Ο┌—  —┬——Ο        │┤      ┌┘          └┐
    —┘Ο—┘    ————Ο  Ο——┘│  Ο—┼┴—  Ο——┴┼


   Ο       Ο    ΟΟΟ                 Ο                  ○
   │       │    │├┼       ┌—Ο  ┌┼                  │
   ├ Ο┬┐┤    ├└┼┐   —┘Ο——┘┤          ○┬—┐┤
   │   ┘└│    │  │                 └            │  ││
	\n"]));
	set("exits", ([
		"west"  : "/d/city/nandajie2",
		"up"    : "/d/city/lichunyuan2",
	]));

    set("no_fight", 1);
	set("coor/x", 10);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
    "/adm/npc/wei"->come_here(); 
}