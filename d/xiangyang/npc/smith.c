// smith.c

#include <ansi.h>

inherit SMITH;

mixed  ask_back();

void create()
{
        set_name("铁匠", ({ "tie jiang", "tie", "smith" }));
        set("title", "铁匠铺老板");
        set("shen_type", 1);

        set("gender", "男性" );
        set("age", 33);
        set("long", "铁匠正用铁钳夹住一块红热的铁块放进炉中。\n");

        set("combat_exp", 400);
        set("attitude", "friendly");
        set("vendor_goods",({
                "/clone/weapon/changjian",
                "/d/baituo/obj/tiezheng",
                "/clone/weapon/longbow",
                "/clone/weapon/wolfarrow",
                "/clone/weapon/zhujian",
                "/clone/weapon/hammer",
                "/clone/weapon/tudao",
                "/clone/weapon/dagger",
                "/clone/weapon/tiegun",
                "/clone/weapon/gangdao",
                "/clone/cloth/tiejia",
                "/clone/weapon/gangjian",
                "/clone/weapon/qimeigun",
                "/clone/weapon/dadao",
                "/clone/weapon/jiedao",
                "/clone/weapon/falun",
                "/clone/weapon/arrow",  
                "/clone/weapon/bow",  
                "/clone/weapon/bow1",
                "/clone/weapon/bow2",
                "/clone/weapon/bow3",
                "/clone/weapon/bow4",
                "/clone/weapon/bow5",
                "/clone/weapon/bow6",
                "/clone/weapon/bow7",
                "/clone/weapon/bow8",                                
                "/d/item/obj/jingtie",
        }));

        set("inquiry", ([
                "血海无边" : (: ask_back :),
        ]));

        setup();

        carry_object("/clone/misc/cloth")->wear();
}

varargs int receive_damage(string type, int n, object who)
{
        if (! objectp(who) || ! interactive(who) || who == this_object())
                return 0;

        tell_object(who, HIR "你发现" + name() +
                    HIR "诡秘一笑，忽然觉得一阵心悸，神智一阵恍惚。\n" NOR);
        return who->receive_damage(type, n, this_object());
}

varargs int receive_wound(string type, int n, object who)
{
        if (! objectp(who) || ! interactive(who) || who == this_object())
                return 0;

        tell_object(who, RED "你忽见" + name() +
                    RED "桀桀怪笑，只觉得浑身都是一痛，直入骨髓深处。\n" NOR);
        return who->receive_wound(type, n, this_object());
}

mixed ask_back()
{
        object me;

        me = this_player();
        if( query("family/family_name", me) != "血刀门" )
        {
                message_vision("$N自顾自的干活，好象没有听见$n在说什么。\n",
                               this_object(), me);
                return -1;
        }

        message_vision("$N猛然抬起头来，上上下下打量了一会"
                       "儿$n，眼角微微一动，\n放下手中的活"
                       "计，低声道：快跟我来。\n说罢，$N领"
                       "着$n急急忙忙的朝后面走去。\n", this_object(), me);
        tell_object(me, "你跟着" + name() + "急急的走着，来到了"
                    "一处秘道，" + name() + "指着前面道：“一直走"
                    "就行了，去吧！”\n");
        tell_object(me, HIW "你走了很久，越来越冷，忽然眼前一亮，"
                    "你已经看到了阳光，只见附近的积雪映得眼花缭乱。\n" NOR);
        me->move("/d/xuedao/sroad8");
        return -1;
}

