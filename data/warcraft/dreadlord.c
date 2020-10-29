// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("巫妖[2;37;0m[2;37;0m", ({"lich"}));        
        set("gender", "女性");                
        set("long", "巫妖[2;37;0m
它是恐惧魔王的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dreadlord");
        set("owner_name", "恐惧魔王");
        set_temp("owner", "dreadlord");
        set_temp("owner_name", "恐惧魔王");
        ::setup();
}
