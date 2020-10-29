// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m玉蜂[2;37;0m[2;37;0m", ({"yufeng"}));        
        set("gender", "男性");                
        set("long", "$HIW$玉蜂[2;37;0m
它是楚云飞的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "chukr");
        set("owner_name", "楚云飞");
        set_temp("owner", "chukr");
        set_temp("owner_name", "楚云飞");
        ::setup();
}
