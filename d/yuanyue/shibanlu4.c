// This program is a part of NITAN MudLIB

inherit ROOM; 
void create()
{
        set("short", "碎石小路"); 
        set("long", @LONG
这条碎石小路往北就是圆月山庄的后院了，南面是富贵如意厅，
路上生满了青苔，一不当心就会跌倒，两侧不知名的野花开得倒也茂
盛，淡淡的散发着一种清新的花香。草窠中偶尔传来一两声蟋蟀的叫
声。一抬头，可以看见几个或是蜈蚣状，或是老鹰状的风筝高高飞舞
在蓝天白云中。
LONG );
        set("type","road");
        set("outdoors", "wansong");
        set("exits",([
                "south":__DIR__"fuguitin",
                "northeast":__DIR__"grass3",
                "northwest":__DIR__"grass1",
        ]) );
        set("objects" , ([
                __DIR__"obj/flower" : 1,
        ]));    
        set("coor/x",-590);
        set("coor/y",230);
        set("coor/z",80);
        setup();
        replace_program(ROOM);
} 
