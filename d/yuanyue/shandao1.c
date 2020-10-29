// This program is a part of NITAN MudLIB

inherit ROOM;
void create()
{
        set("short", "山道"); 
        set("long", @LONG
到了此处，山势渐渐平坦些许，已可大致看到不远的圆月山庄，
那是一栋坐落在山腰上的房子，房子很大，建筑得很堂皇。表示房主
一定很有钱。但房子距离小镇也太远了些，也太偏僻了些，附近简直
可说是荒无人烟。
LONG );
        set("outdoors", "wansong");
        set("type","road");
        set("exits",([
                "south": "/d/wudang/sanbuguan",
                "north":__DIR__"shandao2",
        ]) );

        set("coor/x",-590);
        set("coor/y",190);
        set("coor/z",70);
        setup();
        
} 
