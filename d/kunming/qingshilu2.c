inherit ROOM;

void create()
{
        set("short",  "青石路" );
        set("long", @LONG
一条青石大道，青石铺成，平坦宽阔，抬头一看，前面的
城门清晰可见。
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "west" : __DIR__"dongmen", 
                "east"  :__DIR__"qingshilu1",
        ]));
	set("coor/x", -16810);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}