#include <ansi.h>

inherit ITEM;

void init()
{
object me = this_object();
        object who = this_player();
        object where = environment();
        if (!wizardp(this_player())) 
        {
        set("no_get","你手里一松"+query("name", this_object())+"从指间滑落！\n");
        set("no_give","这么珍贵的药，哪能随便给人？\n");
        set("no_drop","这么宝贵的药，扔了多可惜呀！\n");
        set("no_sell","凡人哪里知道"+query("name", this_object())+"的价值？还是自己留着吧。\n");
        if( !query("my_owner", me) && interactive(who) )
        set("my_owner",query("id",  who), me);
   
        if (userp(where))
        {
                if( query("owned", me) )
                {
                        if( query("owned", me) != query("id", where) )
                        {
                                call_out("destruct_me",1,where,me);
                        }
                }
        else
        {
                set("owned",query("id",  where), me);
        }
        }
        call_out("destroy_me",120,where,me);
        }                                                            

}
void destruct_me(object where, object me)
{
        message_vision("千面怪鬼鬼祟祟地拿起$n撒脚就跑,快追!\n",where,me);
        destruct (me);
}

void create()
{
        set_name(YEL"丹药"NOR, ({"dan yao","danyao"}));
        set_weight(20);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
        set("unit", "株");
        set("long", "一颗香气四溢的丹药。\n");
        set("canoe",1); // 身份鉴定,防止假药材
        set("value", 0);
        set("drug_type", "补品");
        }
  
        setup();
}