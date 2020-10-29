inherit ROOM;

void create()
{
        set("short", "油条铺");
        set("long", @LONG
这家烧饼油条铺是新开张的。铺面不大，正中央摆了一个大炸锅
和一个烤炉。
LONG );
        set("outdoors", "foshan");
        set("exits", ([
                "south" : __DIR__"street4",
        ]));
	set("coor/x", -6560);
	set("coor/y", -9740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}