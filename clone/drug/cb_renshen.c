// Code of ShenZhou
// /d/changbai/renshen.c 人参

inherit ITEM;
#include <ansi.h>
void setup()
{}

int cure_ob(string);

void create()
{
        set_name("人参", ({"ren shen", "shen"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "株");
                set("long", "这是一株沾满山泥的长白山人参。\n");
                set("value", 10000);
                set("medicine", 1);
                set("no_sell", 1);
        }
        setup();
}

int cure_ob(object me)
{
        if ( (int)me->query_condition("bonze_drug" ) > 0 ) {
                addn("eff_jingli", -1, me);
                addn("max_jingli", -1, me);
                message_vision(HIR "$N吃下一株人参，只觉得头重脚轻，火气翻腾，原来服食太多，药效适得其反！\n" NOR, me);
                this_object()->move("/u/aln/workroom");
                call_out("destroy", 31);
                return 1;
        }

        if( !query_temp("cbs/renshen", me)){
                addn_temp("apply/con", 5, me);
                set_temp("cbs/renshen", 1, me);
                me->start_call_out((:call_other,__FILE__,"remove_effect",me:),query("con", me));
        }

        addn("jingli", 150, me);
        addn("neili", 150, me);

        message_vision(HIG"$N吃下一株人参，只觉得浑身一股热气兜底冒了上来 !\n" NOR, me);

        me->apply_condition("bonze_drug", 
                this_player()->query_condition("bonze_drug")+30);

        this_object()->move("/u/aln/workroom");
        call_out("destroy", 31);
        return 1;
}

void remove_effect(object me)
{
        addn_temp("apply/damage", -30, me);
        delete_temp("cbs/renshen", me);
}

void destroy()
{
        destruct(this_object());
}