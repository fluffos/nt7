// dian.c 点石成金
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIC "点石成金" NOR; }

void remove_effect(object me, int amount);

int perform(object me, string skill)
{
        int i;

        if (time() - me->query("special2/dian") < 86400)
                return notify_fail("点石成金一天只能施展一次！\n");

        message_vision(HIY "$N" HIY "施展出点石成金只术，凌空虚点几下，刹那间金光闪闪，\n"
                       "无数黄金从天而下 ……！\n" NOR, me);
 
        i = 1600 + random(801);

        tell_object(me, HIG "你施展点石成金之术获得了 " + chinese_number(i) + " 黄金，已存入银库。\n" NOR);
 
        me->add("stocks/balance", i);

        me->set("special2/dian", time());

        log_file("static/special2", sprintf("%s(%s) 施展点石成金 at %s\n", 
                                    me->name(),
                                    me->query("id"),
                                    ctime(time())));
        me->save();

        return 1;
}
