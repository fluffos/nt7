// Room: chaopath2.c 朝阳峰小路
//Date: Oct. 2 1997 by Venus
inherit ROOM;

void create()
{
      set("short","朝阳峰小路");
        set("long", @LONG
这里是朝阳峰小路，山势陡峭，两边下临深谷，一不小心都会掉
了下去。东面有一条小路，长草没径，小路顺着山脊一路宛延而下至
华山后山里。此处是华山前辈避世之处，轻易见不得人迹。就连华山
弟子若是不得传招，也不能来此。北面的几栋小屋，便是华山前辈的
居所。
LONG );
      set("outdoors", "huashan");
      set("exits",([ /* sizeof() == 1 */
          "southwest": __DIR__"chaopath1",
          "eastup"   : __DIR__"chaoyang",
          "westup"   : __DIR__"ziqitai",
          "northup"    : __DIR__"hsxiaowu",
      ]));
      set("objects", ([
          __DIR__"npc/shi-daizi" : 1,
      ]));
      setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xunshan", me))set_temp("xunshan/chaoyang", 1, me);
        return;
}

int valid_leave(object me, string dir)
{
        if (dir != "northup"  ||
            ! objectp(present("shi daizi", environment(me))) ||
            (query("family/master_id", me) == "gaolaozhe") || 
            (query("family/master_id", me) == "ailaozhe") )
                return ::valid_leave(me, dir);

        if( query("family/family_name", me) != "华山派" )
        {
                message_vision("施戴子伸手拦住$N，道：抱歉，上面是两位"
                               "长老清修之处，这位" + RANK_D->query_respect(me) +
                               "请止步！\n", me);
                return notify_fail("看来施戴子不会让你过去。\n");
        }

        if( query("combat_exp", me)<100000 )
        {
                message_vision("施戴子伸手拦住$N，道：止步！上面是两位"
                               "长老清修之处，你虽然是本派弟子，但是学"
                               "艺不精，不能拜见！\n", me);
                return notify_fail("看来施戴子不会让你过去。\n");
        }

        return ::valid_leave(me, dir);
}