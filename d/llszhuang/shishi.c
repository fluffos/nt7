#include <ansi.h>
inherit ROOM;
void create()
{
  set("short","石室");
  set("long",
"石室形作八角，共有八门，阵阵阴风吹来，你不由的打了一个寒战。\n"
"往里走上几步看到门口一滩血迹，墙壁上也斑斑点点散满了血水。好象这\n"
"里刚刚经过一场激烈的搏杀。\n"
);
        set("no_magic", "1");
    set("exits", ([
            "1" : __DIR__"stone1",
            "2" : __DIR__"stone2",
            "3" : __DIR__"stone3",
            "4" : __DIR__"stone4",
            "5" : __DIR__"stone5",
            "6" : __DIR__"stone6",
            "7" : __DIR__"stone7",
 //21              "west" : __DIR__"chukou",
            "8" : __DIR__"stone8",
         "out" :"/d/city/guangchang",
            "east": __DIR__"lou0",
   ]));
    setup();
}
