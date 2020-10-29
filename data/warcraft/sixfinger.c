// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m六[1;32m脉[2;37;0m[2;37;0m[2;37;0m", ({"sixf"}));        
        set("gender", "女性");                
        set("long", "厉害的[2;37;0m
它是段六脉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "sixfinger");
        set("owner_name", "段六脉");
        set_temp("owner", "sixfinger");
        set_temp("owner_name", "段六脉");
        ::setup();
}
