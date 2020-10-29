// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m飞腿[2;37;0m[2;37;0m", ({"maburahosa"}));        
        set("gender", "男性");                
        set("long", "$HIW$飞腿[2;37;0m
它是晨风的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "maburahos");
        set("owner_name", "晨风");
        set_temp("owner", "maburahos");
        set_temp("owner_name", "晨风");
        ::setup();
}
