// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "翠竹园");
        
        set("long", @LONG
『有竹无肉轩』四周就是翠竹园，这里种满了竹，每到风清月白
的夏夜，圆月山庄的历代主人们便会来此，一把竹椅，一壶清茶，听
那海浪般的竹涛声，可惜柳若松很久已经没这个兴致了，倒是会时常
和他的兄弟们砍竹卖钱换酒，年复一年，翠竹园中的竹子也越来越少。
LONG );
        set("outdoors", "wansong");
        set("type","forest");
        set("exits",([
                "south":__DIR__"wuzhuxuan",
        ]) );

        set("coor/x",-610);
        set("coor/y",230);
        set("coor/z",80);
        setup();
} 
 
