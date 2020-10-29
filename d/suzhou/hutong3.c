// Room: /d/suzhou/hutong3.c
// Date: May 31, 98  Java
// Updated by rama
inherit ROOM;
#include <ansi.h>

int do_open(string arg);
int do_knock(string arg);

void create() {
        set("short", "胡同");
        set("long", @LONG
这是一条黑暗、肮脏的小巷，空气中仿佛飘扬着一股罪恶的气息，
几个流氓在游荡，向东南就能回到大街，你还是赶快走吧。旁边有个
木门（door）。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "west"      : __DIR__"hutong2",
                "southeast" : __DIR__"dongdajie2",
        ]));
        set("item_desc", ([
                "door" : "厚厚的木门紧关着，有些年岁了。\n" ,
        ]));

        set("objects", ([
                "/d/city/npc/liumang" : 2,
        ]));
	set("coor/x", 1140);
	set("coor/y", -1040);
	set("coor/z", 0);
	setup();
}
void init()
{
        add_action("do_knock", "knock");
        add_action("do_open","open");
}
int do_open(string arg)
{
        if(arg=="door")
        return notify_fail("你用力拉了拉木门，结果一点动静都没有，看来是被反锁了！\n");
        else return 0;
}

int do_knock(string arg)
{
        object me;
        me = this_player();
        if (!arg||arg=="")
                return notify_fail("你要敲什么？\n");
          if (arg != "door")
                return notify_fail("你要敲什么？\n");
          if( arg=="door" ) {
                message_vision("$N试著敲了敲木门。\n", me);
                if( query("bunch/bunch_name", me) == "修罗门" )
                {
                        message_vision(HIB"木门吱呀一声开了，从里面探出个头来，看了$N两眼说道：“原来是自己兄弟！”，
说完一把把$N拉了进去。\n"NOR, me);
                        me->move("/d/suzhou/xlm_zb");
                        return 1;
                }

                if( query("bunch/bunch_name", me) != "修罗门" && query("shen", me) <= 0 )
                {
                        message_vision(HIB"木门吱呀一声开了，从里面探出个头来，看了$N两眼说道：“是来投靠咱们修罗门的吧！”，
说完一把把$N拉了进去。\n"NOR, me);
                        me->move("/d/suzhou/xlm_zb");
                        return 1;
                }
                if( good_bunch(me) || query("shen", me)>0 )
                {
                          message_vision("木门吱呀一声开了，从里面探出个头来，看了$N两眼说道：“你这种人也敢来此，活的不耐烦了么？”\n门被重重的关上了。\n",me);
                        return 1;
                }
                message_vision("木门吱呀一声开了，从里面探出个头来，看了$N两眼说道：“既然是本门的兄弟，就进来吧！”，
说完一把把$N拉了进去。\n",me);
                me->move("/d/suzhou/xlm_zb");
                return 1;
        }

        return 1;
}