inherit ROOM;

void create()
{
        set("short", "青石道" );
        set("long", @LONG
接近荆州，路由黄土变成了青石铺路，两旁渐渐可以看见一些农
舍，农田肥沃，稻香四飘。古称荆州为军事要地，地理为其一，肥沃
为其二啊！往西望去，可见荆州的城楼了。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "north": __DIR__"caodi",
                  "east" : __DIR__"guandao2",
                  "west" : __DIR__"jzdongmen",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -7060);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}