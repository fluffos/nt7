// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[41;1m[1;37m南帝北丐[2;37;0m[2;37;0m", ({"gaigai"}));        
        set("gender", "男性");                
        set("long", "南帝北丐[2;37;0m
它是乞丐的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "qigai");
        set("owner_name", "乞丐");
        set_temp("owner", "qigai");
        set_temp("owner_name", "乞丐");
        ::setup();
}
