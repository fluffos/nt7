#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"大雄宝殿"NOR);
        set("long",@LONG
这是一座宽广的大殿，正中是三丈来高的南无如来释迦牟尼佛、
南无金刚不坏佛、南无宝光佛三尊宝像，通体镀金，光芒四射。宝座
下香炉中香烟缭绕，点的是那天竺檀香。蒲团前有一无量功德宝盒。
西过去通往地藏殿，东边是药师殿。
LONG);       
        set("exits", ([
            "southdown" : __DIR__"road1",
                "north" : __DIR__"gfd",
                "west" : __DIR__"dizangdian",
                "east" : __DIR__"yaoshidian",
	]));
        set("coor/x",-350);
  set("coor/y",-330);
   set("coor/z",30);
   setup();
}

void init()
{
       add_action("do_ketou", "ketou");
}

int do_ketou()
{
object me=this_player();
int i;
i=me->query_skill("buddhism",1);
       if (me->is_busy()) return notify_fail("你正忙着呢。\n");
       if (i<20) return 0;
if (random(me->query("neili"))<i) {
   me->unconcious();
return 0;
}
       message_vision("$N虔诚地跪下来，在如来佛祖面前磕头。\n", me);
       
    if (me->query("shen") > i) 
    { me->add("shen", -i);     
   me->add("neili",-i/10);}
    if (me->query("shen") <-i ) 
    { me->add("shen", i);     
   me->add("neili",-i/10);}
   me->start_busy(random(2));
       return 1;
} 
