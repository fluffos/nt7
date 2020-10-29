// heal.c
#include <ansi.h>
int exert(object me, object target)
{
    if ( !wizardp(me)) return 0 ;
    write( HIY "你全身放松，坐下来开始运功疗伤。\n" NOR);
    message("vision",
        HIY + me->name() + "吐出一口金灿灿的血，脸色立刻恢复了正常。\n" NOR,
        environment(me), me);
    set("eff_qi",query("max_qi",  me), me);
    set("qi",query("max_qi",  me), me);
    set("eff_jing",query("max_jing",  me), me);
    set("jing",query("max_jing",  me), me);
    set("neili",query("max_neili",  me), me);
    set("jingli",query("max_jingli",  me), me);
    return 1;
}
