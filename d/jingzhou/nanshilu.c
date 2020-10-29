inherit ROOM;
void create()
{
        set("short", "碎石路" );
        set("long", @LONG
这是一条由碎石铺成的路，虽然有些颠簸，却很宽阔，再往南去
就是长江了。
LONG );
        set("exits", ([
                  "north" :__DIR__"jznanmen",
                  "south" :__DIR__"nanshilu1",
                "west" : __DIR__"qingshilu1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jingzhou");

        set("coor/x", -7100);
	set("coor/y", -2090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}