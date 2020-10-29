inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(NOR + RED "赤兔马" NOR, ({ "chitu ma"}));
        set("long", NOR + RED "浑身上下，火炭般赤，无半根杂毛；从头至尾，长一丈；从蹄至项，高"
                              "八尺；嘶喊咆哮，有腾空入海之状。\n"
                              "建安二十六年，关羽走麦城，兵败遭擒，拒降，为孙权所害。其坐骑赤\n"
                              "兔马为孙权赐予马忠。赤兔马绝食数日，不久即亡。\n" NOR);

        set("tili", 5000);
        set("max_tili", 5000);
        set("level", 4);

        set("can_go_any", 1);

        setup();
}