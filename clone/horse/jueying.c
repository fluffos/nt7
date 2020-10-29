inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIM "绝影无影" NOR, ({ "jueying wuying"}));
        set("long", HIM "绝影据说是大宛名马，熬得痛，身上中了三箭竟然仍能奋蹄"
                        "疾驰，而且速度极快（绝影之名或许就是因为其速度快而得"
                        "的，意为其速度快的连影子都跟不上了），最后被流矢射中"
                        "眼睛才倒了下去。曹操再转乘长子曹昂的马逃跑，而绝影马"
                        "便在这一战中完成了其所有的使命。 \n" NOR);

        set("tili", 3000);
        set("max_tili", 3000);
        set("level", 3);

        setup();
}