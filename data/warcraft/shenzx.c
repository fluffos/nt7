// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m晨曦[2;37;0m[2;37;0m", ({"shen"}));        
        set("gender", "男性");                
        set("long", "是妖为成仙[2;37;0m
它是聂风的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "shenzx");
        set("owner_name", "聂风");
        set_temp("owner", "shenzx");
        set_temp("owner_name", "聂风");
        ::setup();
}
