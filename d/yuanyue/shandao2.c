inherit ROOM;

void create()
{
        set("short", "山道"); 
        set("long", @LONG
你走在去圆月山庄的山道上，一抬头，又可看见几个或是蜈蚣状，
或是老鹰状的风筝高高飞舞在蓝天白云中。山风徐徐，白云悠悠，不
觉感觉悠闲自得。往北面探头望去，已可隐约看见圆月山庄的铜漆大
门。
LONG );
        set("outdoors", "wansong");
        set("type","road");
        set("exits",([
                "north":__DIR__"damen",
                "south":__DIR__"shandao1",
        ]) );
        

        set("coor/x",-590);
        set("coor/y",180);
        set("coor/z",60);
        setup();
} 
