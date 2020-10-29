// Room: anbian1.c
// By River 98/12
inherit ROOM;
void create()
{
        set("short", "澜沧江畔");
        set("long", @LONG
你一眼望出去，之见前面怒涛汹涌，水流湍急，竟是一条大江。江岸山石
壁立，嶙峋巍峨，看这情势，已是到了澜沧江畔。江面有十来丈高，但要走到
江岸，却也着实不易。 
LONG
        );
        set("exits", ([
            "west" : __DIR__"shanlu8",
            "east" : __DIR__"jiangan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "大理");

        set("coor/x",-290);
  set("coor/y",-290);
   set("coor/z",-20);
   setup();
}