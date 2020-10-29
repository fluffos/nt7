// Room: jiangan.c
// By River 98/12
inherit ROOM;
void create()
{
        set("short", "江岸");
        set("long", @LONG
江岸尽是山石，小路也没一条，七高八低的走出七八里地，见到一株野生
桃树，树上结实累累。又走了十馀里，才见到一条小径。沿着小径行去，终于
见了过江的铁索桥，只见桥边石上刻着“善人渡”三个大字。 
LONG
        );
        set("exits", ([
            "north" : __DIR__"tiesuo",
            "west" : __DIR__"anbian1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "大理");

        set("coor/x",-280);
  set("coor/y",-290);
   set("coor/z",-20);
   setup();
}