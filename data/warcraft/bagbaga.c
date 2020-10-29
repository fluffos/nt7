// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("自行车[2;37;0m[2;37;0m", ({"alias_m_whistle_zixc"}));        
        set("gender", "男性");                
        set("long", "自行车[2;37;0m
它是赫连小鬼的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "bagbaga");
        set("owner_name", "赫连小鬼");
        set_temp("owner", "bagbaga");
        set_temp("owner_name", "赫连小鬼");
        ::setup();
}
