inherit ROOM;

void create()
{
        set("short", "刑场");
        set("long", @LONG
这里是京城的刑场，是朝廷处决钦犯的场所。你走到了这里，发
现整个刑场很是空旷，刑场正中有一个高高的石台，石台上由几根圆
木柱搭建成了一个框架，上面垂着一根很粗的麻绳。框架下面是一个
正方形的大木桩，上面还能够看见隐隐血迹。
LONG );
       set("exits", ([
                "west" : "/d/beijing/wang_2",
        ]));
        set("objects", ([
                "/d/beijing/npc/guizishou" : 1,
               "/clone/npc/walker"  : 1, 
        ]));

	set("coor/x", -2760);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}