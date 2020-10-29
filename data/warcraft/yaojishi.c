// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m电机[2;37;0m[2;37;0m", ({"xjg"}));        
        set("gender", "男性");                
        set("long", "自动的。[2;37;0m
它是药剂师的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yaojishi");
        set("owner_name", "药剂师");
        set_temp("owner", "yaojishi");
        set_temp("owner_name", "药剂师");
        ::setup();
}
