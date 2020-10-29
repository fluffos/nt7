#include <ansi.h>

inherit MEDICINE;

void create()
{
        set_name(RED"朱雀丹"NOR, ({"zhuque dan", "dan"}));
        set("unit", "颗");

        set("upgrade_stat", ([ "kee" : 20,
                               "sen" : 20 ]));
        set("apply_condition", ([ "drunk" : 20 ]));
        set("env_message", RED"$N取出一颗红色的丸子，一仰头吃了下去，顿时脸色变得红火。");
        set("prv_message", HIR"你觉得腹内好象有火在烧，一股热气顺着血行汇入了奇经百脉。");

        setup();
}
