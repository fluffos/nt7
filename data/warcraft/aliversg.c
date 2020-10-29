// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("隐形轰炸机[2;37;0m[2;37;0m", ({"pesie"}));        
        set("gender", "男性");                
        set("long", "隐形轰炸机[2;37;0m
它是阿尔七的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "aliversg");
        set("owner_name", "阿尔七");
        set_temp("owner", "aliversg");
        set_temp("owner_name", "阿尔七");
        ::setup();
}
