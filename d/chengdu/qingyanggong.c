#include <ansi.h>
inherit ROOM;

int do_open(string arg);
int do_knock(string arg);
int do_back();

void create()
{
        set("short", "青羊宫");
        set("long", @LONG
青羊宫是天下第一大道观。观中林木婆娑，冠盖亭亭观中道士匆
匆来去，没人得空理你，更没人接待你。你觉得到一种宽松的失落。
旁边有一个木门（door）。
LONG );
        set("exits", ([
                "northeast" : __DIR__"westroad1",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("item_desc", ([
                "door" : "厚厚的木门紧关着，有些年岁了。\n" ,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15250);
	set("coor/y", -1850);
	set("coor/z", 0);
	setup();
}

void init()
{
        object me = this_player();

        if( query("family/family_name", me) == "峨嵋派" )
        {
                tell_object(me, HIG "\n你突然发现峨嵋派弟子留在此处的"
                                "密信。\n" NOR);
                set_temp("want_leave", 1, me);

                remove_call_out("letter");
                call_out("letter", 3, me);
        }
        add_action("do_back",  "back");
        add_action("do_knock", "knock");
        add_action("do_open", "open");
}

void letter(object me)
{
        if (! objectp(me))
                return;

        if( !query_temp("want_leave", me) )
                return;

        tell_object(me, WHT "  ┏------------┓\n"
                            "  ┃观旁树林内有┃\n"
                            "  ┃本派密道能够┃\n"
                            "  ┃直通(" HIY "back" NOR + WHT ")峨┃\n"
                            "  ┃嵋华藏庵大殿┃\n"
                            "  ┗------------┛\n" NOR);
}

int do_back()
{
        object me = this_player();

        if( query_temp("want_leave", me) )
        {
                message("vision", HIC "忽然间只见" + me->name() + HIC
                                  "身形一晃，竟没了踪影。\n" NOR,
                                  environment(me), ({me}));
                me->move("/d/emei/midao5");
                tell_object(me, HIC "\n你钻进了青羊观树林内的密道。\n\n" NOR);
        }
        return 1;
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
                if( query("bunch/bunch_name", me) != "修罗门" && query("shen", me) <= 0 )
                {
                        message_vision(HIB"木门吱呀一声开了，从里面探出个头来，看了$N两眼说道：“是来投靠咱们修罗门的吧！”，
说完一把把$N拉了进去。\n"NOR, me);
                        me->move(__DIR__"xlm_cdfb");
                        return 1;
                }
                if( good_bunch(me) || (query("bunch/bunch_name", me) != "修罗门" && query("shen", me)>0) )
                {
                                command("say 哪里来的邪魔歪道，找打么？\n");
                        return 1;
                }
                message_vision("木门吱呀一声开了，从里面探出个头来，看了$N两眼说道：“既然是本门的兄弟，就进来吧！”，
说完一把把$N拉了进去。\n",me);
                me->move(__DIR__"xlm_cdfb");
                return 1;
        }

        return 1;
}
