// poison_dust.c

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{

        set_name(WHT"软骨散"NOR, ({ "ruangu san", "san" }) );
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一包白色的药粉。\n" );
                set("unit", "包");
                set("base_value", 700);
                set("base_unit", "包");
                set("base_weight", 30);
                set("yaowang", 1);
                set("no_sell", 1);
                set("no_give", 1);
                set("no_get", 1);
                set("value", 0);
        }
        set_amount(1);
}

void init()
{
        object me, ob;
        int obj;

        me = this_player();
        ob = this_object();
        obj = (int)me->query_skill("poison");

        if( query_temp("liandan", me) == 1
                 && query("value", ob) == 0 )
        {
                if(obj<100) {
                        set("value", (random(2000)+2000), ob);}
                if(obj>=100 && obj<150) {
                        set("value", (random(4000)+4000), ob);}
                if(obj>=150 && obj<200) {
                        set("value", (random(8000)+7000), ob);}
                if(obj>=200 && obj<250) {
                        set("value", (random(15000)+15000), ob);}
                if(obj>=250) {
                        set("value", (random(20000)+30000), ob);
                        }
        }
        add_action("do_pour", "pour");
}

int do_pour(string arg)
{
        string me, what;
        object ob;
        function f;

        if( !arg
        ||      sscanf(arg, "%s in %s", me, what)!=2
        ||      !id(me) )
                return notify_fail("命令格式: pour <药> in <物品>。\n");

        ob = present(what, this_player());
        if( !ob )
                return notify_fail("你身上没有" + what + "这样东西。\n");
        if( !query("liquid/remaining", ob) )
                return notify_fail(ob->name() + "里什么也没有，先装些酒水才能溶化药粉\n");
        f = (: call_other, __FILE__, "drink_drug" :);
        set("liquid/drink_func", bind(f,ob), ob);
        addn("liquid/slumber_effect", 100, ob);
        message_vision("$N将一些" + name() + "倒进" + ob->name() 
                + "摇晃了几下。\n", this_player());
        add_amount(-1);
        return 1;
}

int drink_drug(object ob)
{
        this_player()->apply_condition("slumber_drug",
                (int)this_player()->query_condition("slumber_drug") 
                +query("liquid/slumber_effect", ob));
        return 0;
}