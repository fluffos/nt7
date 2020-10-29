// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("丹顶鹤[2;37;0m[2;37;0m", ({"hun"}));        
        set("gender", "男性");                
        set("long", "鸟[2;37;0m
它是药丸魂的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yaohun");
        set("owner_name", "药丸魂");
        set_temp("owner", "yaohun");
        set_temp("owner_name", "药丸魂");
        ::setup();
}
