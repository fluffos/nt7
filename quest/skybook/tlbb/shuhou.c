// shuhou.c
// bbb 1997/06/11
// Modify By River 98/12
// Modify by tangfeng 2004
inherit ROOM;
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
#include <ansi.h>
void create()
{
	set("short", "树丛后");
	set("long", @LONG
这里光秃秃的一大片石壁，爬满藤蔓，但见石壁平整异常，宛然一面铜镜，
只是比湖西的山壁小了许多，再细看那石壁，平整光滑，别无他异。
LONG
	);
        set("exits", ([
		"out" : __DIR__"shulin1",
	]));
        set("outdoors", "大理");
	setup();
}

void init()
{
	  object me;
    me = this_player();
	  if (me->query(QUESTDIR1+"start") 
	     && !me->query(QUESTDIR1+"wuliangover")
	     && me->query_temp(QUESTDIR1+"jianying") 
	     && !me->query_temp(QUESTDIR1+"see_duanyu1"))
	  {
      "/cmds/std/look.c"->look_room(this_player(), this_object());
      tell_object(me,HIY"\n你眼光顺着湖面一路伸展出去，突然之间全身一震，只见对面玉壁上赫然有个人影。你定了定神凝神看去，那人影淡淡的看不清楚。\n"
                          "你一怔之下，便即省悟：“是我自己的影子？”身子左幌，壁上人影跟着左幌，身侧右，此时已无怀疑。你微一凝思，只觉这迷惑了\n"
                          "“无量剑”数十年的“玉壁仙影”之谜，更无丝毫神奇之处：“当年确有人站在这里使剑，人影映上玉壁。本来有一男一女，后来那\n"
                          "男的不知是走了还是死了，只剩下一个女的，她在这幽谷中寂寞孤单，过不了两年也就死了。”一想像佳人失侣，独处幽谷，终于郁\n"
                          "郁而死，不禁黯然。既明白了这个道理，心中先前的狂喜自即无影无踪，百无聊赖之际，便即手舞足蹈，拳打脚踢，心想：“最好左\n"
                          "子穆、双清他们这时便在崖顶，见到玉壁上忽现‘仙影’，认定这是仙人在演示神奇武功，于是将我这套‘武功’用心学了去，拼命\n"
                          "钻研，传之后世。哈哈，哈哈！”越想越有趣，忍不住纵声狂笑。\n"NOR);
    }
    add_action("do_down", "tear");
    add_action("do_down", "si");
}

int do_down(string arg)
{
	object me = this_player();
        if (!arg || arg!="teng") return 0;
        message_vision("$N把石壁上的藤蔓撕得干干净净，走向后面。\n" , me);
        me->move(__DIR__"shibi");
        return 1; 
}
