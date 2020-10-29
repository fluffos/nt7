#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"光佛宝殿"NOR);
        set("long",@LONG
这座大殿正正方方，殿中光线明亮，原来屋顶有一圆洞为琉璃瓦
所制，由四支大红圆柱托住。殿里供奉着南无燃灯上古佛祖，金身金
袈，华丽之极。一般香客行到这里就得止步了，再往后便是寺中僧侣
清修之地。
LONG
        );
       
         set("exits", ([
                "south" : __DIR__"baodian",
                "northdown" : __DIR__"yz6",
                "west" : __DIR__"men2",
                "east" : __DIR__"men1",
        ]));


	set("objects",([
                __DIR__"npc/ben-yin" : 1,
        ]));

        set("coor/x",-350);
  set("coor/y",-320);
   set("coor/z",30);
   setup();
}
int valid_leave(object me, string dir)
{
     mapping fam;
 fam = (mapping)me->query("family");
	
	if ( fam && fam["family_name"] != "天龙寺" &&
            present("benyin dashi", environment(me)) &&
			 dir == "northdown")
            return notify_fail("本因大师把手一伸，拦住了你的去路，\n"+
           "说道：阿弥陀佛，你不是天龙寺弟子，不得入后寺扰乱清修。\n");
    if (fam)
	if ( present("benyin dashi", environment(me)) &&
			 !me->query("tls") &&
		dir == "northdown")
            return notify_fail("本因大师把手一伸，拦住了你的去路，\n"+
           "说道：阿弥陀佛，你不是天龙寺出家弟子，不得入后寺扰乱清修。\n");                    
        return ::valid_leave(me, dir);
}
