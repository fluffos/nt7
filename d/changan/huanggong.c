//Room: huanggong.c

inherit ROOM;

void create ()
{
        set ("short", "皇宫大殿");
        set("long", @LONG
皇宫大殿坐落全宫核心，左右是两个偏殿，各有一条约二十丈长
的廊道相连，如两边飞出雁翼。两个副殿，以左翼殿和右翼殿为名。
LONG );
        set("exits", ([
                "south"   : "/d/changan/bridge2",
                "north"   : "/d/changan/bridge1",
                "east"   : "/d/changan/fudian1",
                "west"   : "/d/changan/fudian2",
        ]));
        set("objects", ([
                "/d/changan/npc/shiwei" : 4,
                "/clone/npc/walker"  : 1, 
        ]));

        set("coor/x", -10720);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
}