// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("自行车[2;37;0m[2;37;0m", ({"alias_m_whistle_zixc"}));        
        set("gender", "男性");                
        set("long", "自行车[2;37;0m
它是赫连圈钱的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "bagbagh");
        set("owner_name", "赫连圈钱");
        set_temp("owner", "bagbagh");
        set_temp("owner_name", "赫连圈钱");
        ::setup();
}
