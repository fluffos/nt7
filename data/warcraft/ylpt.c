// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "上古神兽[2;37;0m
它是咖啡的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ylpt");
        set("owner_name", "咖啡");
        set_temp("owner", "ylpt");
        set_temp("owner_name", "咖啡");
        ::setup();
}
