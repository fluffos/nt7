#include <ansi.h>
inherit ROOM;

int do_knock(string arg);
int do_open(string arg);

void create()
{
        set("short", "郭庄");
        set("long", @LONG
庄园的大匾上是「郭庄」两个大字。朱红色的大门(gate)紧紧关
闭着，里面静悄悄的一点声音都没有。
LONG );
        set("exits", ([
                "east" : __DIR__"dadao1",
        ]));
        set("objects", ([
                "/clone/quarry/gou2" : 2,
        ]));
        set("item_desc", ([
                "gate" : "朱红的大门紧闭着，敲敲(knock)看吧。\n"
        ]));
        set("no_clean_up", 0);
	set("coor/x", 770);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
        // replace_program(ROOM);
}

void init()
{
        add_action("do_knock", "knock");
        add_action("do_open","open");
}
int do_open(string arg)
{
        if(arg=="gate")
        return notify_fail("你用力推了推门，结果一点动静都没有！看来是从里面反锁了。\n");
        else return 0;
}

int do_knock(string arg)
{
        object me;
        me = this_player();
        if (!arg||arg=="")
                return notify_fail("你要敲什么？\n");
          if (arg != "gate")
                return notify_fail("你要敲什么？\n");
          if( arg=="gate" ) {
                message_vision("$N试著敲了敲门。\n", me);
                if( query("bunch/bunch_name", me) != "小刀会" && query("shen", me) <= 0 )
                {
                        message_vision(HIB"大门吱呀一声开了，从里面探出个头来，看了$N两眼说道：“是来投靠咱们小刀会的吧！”，
说完一把把$N拉了进去。\n"NOR, me);
                        me->move("/d/hangzhou/xdh_hzfb");
                        return 1;
                }
                if( good_bunch(me) || query("shen", me)>0 )
                {
                        message_vision("大门吱呀一声开了，从里面探出个头来，看了$N两眼说道：“你这种人也敢来此，活的不耐烦了么？”\n门被重重的关上了。\n",me);
                        return 1;
                }
                message_vision("大门吱呀一声开了，从里面探出个头来，看了$N两眼说道：“既然是本帮的兄弟，就进来吧！”，
说完一把把$N拉了进去。\n",me);
                me->move("/d/hangzhou/xdh_hzfb");
                return 1;
        }

        return 1;
}