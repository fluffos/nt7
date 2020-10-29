//Room: huarui2.c

inherit ROOM;

void create ()
{
        set ("short", "华瑞街");
        set("long", @LONG
华瑞街是长安城南一条东西向的大道，也是长安城的居民区。一
条碎石子铺成的街坊，南边可见一些民居住宅，北面是一家小面馆，
街头有炊烟袅袅飘来青柴的香味。不远处传来家家户户舂米的声音，
还有大户人家榨香油的醇香味。
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/minju2",
                "north" : "/d/changan/mianguan",
                "west" : "/d/changan/huarui1",
                "east" : "/d/changan/huarui3",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10740);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}