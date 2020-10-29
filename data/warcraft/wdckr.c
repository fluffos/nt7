// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m天柱[2;37;0m[2;37;0m", ({"tianzhu"}));        
        set("gender", "男性");                
        set("long", "$HIW$天柱[2;37;0m
它是楚飞的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "wdckr");
        set("owner_name", "楚飞");
        set_temp("owner", "wdckr");
        set_temp("owner_name", "楚飞");
        ::setup();
}
