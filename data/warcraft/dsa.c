// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("太极鸟[2;37;0m[2;37;0m", ({"dgg"}));        
        set("gender", "男性");                
        set("long", "一只鸟[2;37;0m
它是连枷兽魔的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dsa");
        set("owner_name", "连枷兽魔");
        set_temp("owner", "dsa");
        set_temp("owner_name", "连枷兽魔");
        ::setup();
}
