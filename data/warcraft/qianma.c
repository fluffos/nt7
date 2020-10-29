// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("自行车[2;37;0m[2;37;0m", ({"alias_m_whistle_zxcc"}));        
        set("gender", "男性");                
        set("long", "自行车[2;37;0m
它是任由漂泊的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qianma");
        set("owner_name", "任由漂泊");
        set_temp("owner", "qianma");
        set_temp("owner_name", "任由漂泊");
        ::setup();
}
