// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("自行车[2;37;0m[2;37;0m", ({"alias_m_whistle_zixc"}));        
        set("gender", "男性");                
        set("long", "自行车[2;37;0m
它是虎头怪的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qmdmc");
        set("owner_name", "虎头怪");
        set_temp("owner", "qmdmc");
        set_temp("owner_name", "虎头怪");
        ::setup();
}
