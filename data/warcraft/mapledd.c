// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m墨玉麒麟[2;37;0m[2;37;0m", ({"mmp"}));        
        set("gender", "女性");                
        set("long", "墨玉麒麟[2;37;0m
它是风轻云淡的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mapledd");
        set("owner_name", "风轻云淡");
        set_temp("owner", "mapledd");
        set_temp("owner_name", "风轻云淡");
        ::setup();
}
