// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m赤兔[2;37;0m[2;37;0m", ({"chitu"}));        
        set("gender", "男性");                
        set("long", "上古魔兽[2;37;0m
它是仙魔的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "max");
        set("owner_name", "仙魔");
        set_temp("owner", "max");
        set_temp("owner_name", "仙魔");
        ::setup();
}
