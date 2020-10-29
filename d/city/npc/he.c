// he.c

#include <ansi.h>

inherit NPC;

mixed ask_back();

void create()
{
        set_name("何员外", ({ "he yuanwai", "he" }));
        set("shen_type", -1);

        set("gender", "男性" );
        set("age", 53);
        set("long", "何员外是扬州城里的首富，和当地的官绅都有很深的交情。据说他还和桃花岛有些关系。\n");
        set("combat_exp", 400);
        set("attitude", "friendly");
        set("inquiry", ([
                "桃花盛开" : (: ask_back :),
        ]));
        setup();

        carry_object(__DIR__"obj/choucloth")->wear();
}

/*
void init()
{
        object ob;
        mapping myfam;
        ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}
*/

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        say("何员外奇怪地对你说道：“你这人怎么随随便便地就跑到我的园子里来？”\n");
}

mixed ask_back()
{
        object me;

        me = this_player();
        if( query("family/family_name", me) != "桃花岛" )
        {
                message_vision("$N自顾自的干活，好象没有听见$n在说什么。\n",
                               this_object(), me);
                return -1;
        }

        message_sort("$N猛然抬起头来，上上下下打量了一会"
                     "儿$n，眼角微微一动，立刻放下手中的"
                     "活计，从内室领出一只白雕，说道：你"
                     "乘坐这只白雕回桃花岛吧。\n",
                     this_object(), me);

        tell_object(me, HIW "你坐上白雕飞了很久，越过大海，忽然眼前一亮，"
                    "你已经来到了桃花岛。\n" NOR);
        me->move("/d/taohua/jingshe");
        return -1;
}