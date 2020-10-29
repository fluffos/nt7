// Code of ShenZhou
// /d/shenlong/obj/bmdan.c 天王保命丹
// by Aln  1/98

#include <ansi.h>

inherit ITEM;
void create()
{
        set_name("天王保命丹", ({"baoming dan", "dan"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 4000);
                set("long", 
"这天王保命丹是由三百年老山人参、白熊胆、雪莲等物炼成的灵丹\n");
                set("medicine", 1);
                set("no_sell", 1);
                set("only_do_effect", 1);  
                set("no_drop", "天王保命丹炼制不易，哪能乱扔！\n");
        }

        setup();
}

int do_effect(object me)
{
        if( query("eff_qi", me)*10>query("max_qi", me)*3
         && query("eff_jing", me)*10>query("max_jing", me)*3){
                write("你现在用不着服天王保命丹。\n");
                return 1;
        }

        if( !me->is_fighting() ) {
                write("现在又不是危急关头，别浪费了！\n");
                return 1;
        }

        message_vision("$N吃下一颗" + name() + "。\n", me);

        set("eff_qi",query("max_qi",  me), me);
        set("eff_jing",query("max_jing",  me), me);

        message_vision(YEL "$N只觉伤势全愈了。\n\n" NOR, me);
        destruct(this_object());
        return 1;
}