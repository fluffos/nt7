// Code of ShenZhou
// shouwu.c 首乌精

#include <ansi.h>

inherit ITEM;

void init();

void create()
{
        set_name( GRN "首乌精" NOR , ({"shouwu jing", "shouwu"}));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "棵");
                set("long", "这是一棵成精的何首乌，至少生长了几百年了，早已成人形，有奇妙的药效。\n");
                set("value", 8000);
                set("no_sell", 1);
                set("medicine", 1);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        set("jing",query("max_jing",  me), me);
        set("eff_jing",query("max_jing",  me), me);
        set("jingli",query("max_jingli",  me), me);
        
        message_vision(HIY "$N吃下一棵首乌精，药效立刻通彻肺腑，直达四肢。不仅精力大振，连伤痛也全都感觉不到了。\n" NOR, me);

        destruct(this_object());
        return 1;
}