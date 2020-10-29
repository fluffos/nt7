//Room: bridge2.c

inherit ROOM;

void create ()
{
        set ("short", "金水桥");
        set("long", @LONG
金水桥是一条直通皇宫的大石桥，宽敞可容四马并驰，建造得鬼
斧神工，气势磅礴，使人生起一夫当关万夫莫敌的感觉。桥下有一条
清澈见底、蜿蜒地川流的小河，河水有时撞在石上，发出淙淙的流水
声，悦耳动听。桥北通向故皇宫，南面是青龙街。
LONG );
        set("exits", 
        ([ //sizeof() == 2
                "south" : "/d/changan/qinglong2",
                "north" : "/d/changan/huanggong",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/yulinjun" : 2,
                "/d/changan/npc/tongling2" : 1,
        ]));

        set("outdoors", "changan");
        set("coor/x", -10720);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}