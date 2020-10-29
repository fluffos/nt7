// Room: /d/gumu/obj/bishou.c匕首
// Last Modifyed by Lonely on Jan. 14 2002

#include <ansi.h>
inherit ITEM;
void create()
{
        set_name( "匕首" , ({ "bi shou", "blade", "bishou" }) );
        set_weight(100);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "把");
                set("long", "这是一把边缘锋利的匕首，好象可以斩(zhan)东西。\n");
                set("value", 0);
                set("material", "iron");
        }
        setup();
}

void init()
{
        add_action("mark_success", ({"zhan", "斩"}));
}

int mark_success(string arg)
{
        object target, ob,name1, me = this_player();

        name1=query("id", me);
        if(!arg) return notify_fail("你要斩什么？\n");  
        target = present(arg, environment(me));  
        if(!target)
                return notify_fail("找不到这个东西。\n");
        if(!target->is_corpse())
                return notify_fail("看清楚点，那不是尸体。\n");
        if( query("no_head", target) )
                return notify_fail("那具尸体已经没有首级了。\n");
        if(!target->is_character())
                return notify_fail("那具尸体已经腐烂了。\n");
        message_vision(HIR"$N扬起匕首 ，对准$n的脖子处猛地斩了下去！\n"NOR, me, target);
        ob=new("/d/gumu/obj/head");
        ob->set_name(query("victim_name", target)+"的首级",({"head"}));
        set("long", "这是一颗"+query("victim_name", target)+"的首级。\n", ob);
        if( query("victim_user", target) )
        set("victim_user", 1, ob);
        if( query("kill_by", target) )
        set("kill_by",query("kill_by",  target), ob);
        delete("kill_by", target);
        message_vision(HIR"$N将$n斩了下来，提在手中。\n"NOR, me, ob);
        ob->move(me);
        set("name", "无头尸体", target);
        set("no_head", 1, target);
        set("long", "一具无头尸体，腐臭四溢，情状可怖。\n", target);
        return 1;
}