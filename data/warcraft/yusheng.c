// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;34m捷安特[1;31m山地车[2;37;0m[2;37;0m", ({"bike"}));        
        set("gender", "男性");                
        set("long", "kick[2;37;0m
它是梁羽生的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yusheng");
        set("owner_name", "梁羽生");
        set_temp("owner", "yusheng");
        set_temp("owner_name", "梁羽生");
        ::setup();
}
