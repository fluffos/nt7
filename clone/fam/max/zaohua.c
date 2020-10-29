// zaohua.c 造化紫箐丹

#include <ansi.h>

inherit COMBINED_ITEM;

string query_autoload() { return query_amount() + ""; } 
void autoload(string param) 
{
        int amt;

        if (sscanf(param, "%d", amt) == 1)
                set_amount(amt); 
}

void setup() 
{
        set_amount(1);
        ::setup();
}

void create()
{
        set_name(HIM "造化紫箐丹" NOR, ({ "zaohua dan", "zaohua", "dan" }) );
        set_weight(30);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", HIM "一颗紫中泛黄的精致奇丹，具有着神话般的功效，传\n"
                                "说吃了之后能平增数甲子的功力，乃是练武之人梦寐\n"
                                "以求的神丹妙药。\n" NOR);
                set("base_value", 1000000);
                set("base_weight", 100); 
                set("no_sell", 1);
                set("base_unit", "粒");
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        string mapsk;
        int effect;
        int neili;

        effect = 0;

        if( me->is_busy() ) return notify_fail(BUSY_MESSAGE);
        me->start_busy(2+random(2));

        if( query("skybook/item/zaohua", me) )
        {
                me->improve_jingli(20000);
                me->improve_neili(100000);
                addn("skybook/item/zaohua", 1, me);
                message_vision(HIW "$N" HIW "一仰脖，吞下了一颗造化紫箐丹，只见$P"
                               HIW "浑身一颤，七窍都冒出白烟来。\n" NOR, me);
        } else
        {
                message_vision(HIW "$N" HIW "一仰脖，吞下了一颗造化紫箐丹，只见$P"
                               HIW "浑身一颤，七窍都冒出白烟来。\n" NOR, me);

                addn("drug_addneili", 100000, me);
                addn("drug_addjingli", 20000, me);

                mapsk = me->query_skill_mapped("force");
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);

                mapsk = me->query_skill_mapped("parry");
                if (me->can_improve_skill("parry"))
                        me->improve_skill("parry", 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);

                mapsk = me->query_skill_mapped("dodge");
                if (me->can_improve_skill("dodge"))
                        me->improve_skill("dodge", 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);

                me->improve_neili(100000);
                me->improve_jingli(20000);
        }
        add_amount(-1);
        if( query_amount() < 1 )
                destruct(this_object());
        return 1;
}

