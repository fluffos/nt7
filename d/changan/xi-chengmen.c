//Room: xi-chengmen.c

inherit ROOM;

void create ()
{
        set ("short", "长安西城门");
        set("long", @LONG
长安城的西城门。这里的护城河既深又阔，而且城高墙厚，有一
夫当关，万夫莫开之势，城内还驻扎了两营士兵，远看军营延绵，旌
旗似海，颇具慑人之势，仰望城楼，只见城楼高处满布哨兵，剑拔驽
张，士气昂扬。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "west" : "/d/changan/road7",
                "east" : "/d/changan/xian-daokou",
        ]));
        set("objects", ([ //sizeof() == 3
                "/d/changan/npc/wujiang" : 1,
                "/d/changan/npc/guanbing" :2,
               "/clone/npc/walker"  : 1, 
        ]));

        set("outdoors", "changan");
        set("coor/x", -10770);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}