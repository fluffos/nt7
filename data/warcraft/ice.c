// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m冰灵[2;37;0m[2;37;0m", ({"ices"}));        
        set("gender", "女性");                
        set("long", "冰灵[2;37;0m
它是冰心的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ice");
        set("owner_name", "冰心");
        set_temp("owner", "ice");
        set_temp("owner_name", "冰心");
        ::setup();
}
