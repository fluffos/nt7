///d/emei/obj/pantao.c
//redl 2014
#include <ansi.h>
inherit ITEM;

void create()
{
          set_name(HIR "蟠桃" NOR, ({"pan tao", "pan", "tao"}));
          set_weight(150);
          /*if (clonep())
                    set_default_object(__FILE__);
          else*/ {
                    set("long", HIR "一个火红色的大蟠桃，正散发着扑鼻的清香。\n" NOR);
                    set("value", 3000);
                set("only_do_effect", 1);
                    set("unit", "个");
          }
          setup();
}

int do_effect(object me)
{
        string force;
        int neili_limit,i;

       if( me->is_busy() ||
                me->is_fighting()
                ) {
                write(NOR BUSY_MESSAGE NOR);
                return 1;
        }
                i = 4500+random(500);
                if (query("drug_addneili", me)<400000000) addn("drug_addneili", i, me);
        neili_limit = me->query_neili_limit();

        message_vision(HIR "\n$N" HIR "三两口将手中的蟠桃嚼烂吞下，一张脸顿时胀"
                       "得通红。\n" NOR, me);
        write(NOR " (你的额外内力上限已经达到了"+(string)query("drug_addneili", me)+"点。) \n\n" NOR);               
        me->start_busy(random(2) + 2);

          if( query("max_neili", me)<=neili_limit-i )
               {
                       addn("max_neili", i, me);
                       if( query("max_neili", me)>neili_limit )
                               set("max_neili", neili_limit, me);
                       set("neili",query("max_neili",  me)*2, me);
               }
                        force = me->query_skill_mapped("force");
               if (me->can_improve_skill("force"))
                       me->improve_skill("force", 100000);
               if (stringp(force) && me->can_improve_skill(force))
                       me->improve_skill(force, 100000);
        destruct(this_object());
        return 1;
}
