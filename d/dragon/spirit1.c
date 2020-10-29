inherit ROOM; 
 
#include <ansi.h>
void create() 
{ 
        set("short", "精灵界");
        set("long",
"[1;32m这里是一个异世界，来到这里，已经远离了你的江湖。这里\n"
"没有恩怨，没有纷争。有的只是动听的音乐，优美的风景。十四根玉石柱\n"
"子参天而立，看不到尽头。玉柱间白云缭绕，透过白云，隐约能看到雕栏\n"
"画栋，听到丝竹笙歌，光彩流动，奇丽不可名状。这里没有昼夜之分，只\n"
"有空气中不时传来缕缕清香，令人感到平静安宁。\n"
);
        set("exits", ([ 
  "north" : __DIR__"spirit2",
]));
        set("no_clean_up", 0);

        set("no_magic", 1);
        setup();
        replace_program(ROOM);
}
