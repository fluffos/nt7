#include <ansi.h>
inherit ROOM;

#define FO  "/adm/npc/buddha"
void create()
{
        set("short", HIY "【极乐世界】" NOR);
        set("long", HIW @LONG
这里是西方极乐世界，是佛祖和他的弟子聚居之所在。
到处都是云海，霞光闪闪，金光四溢，说不出的庄严宏伟。
佛祖释迦牟尼端坐在正中央，周围是形态各异的五百罗汉。
佛祖形象十分伟岸，你觉得自己还不及佛祖一个脚趾高。
LONG NOR );
/*        set("exits", ([
                "down" : __DIR__"tianmen",
]));*/
        set("sleep_room", 1);
        set("no_fight", 1);       
        set("no_magic", 1);
        set("no_bid", 1);
        setup();  
        load_object(FO)->move(this_object());
      
}
