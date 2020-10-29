// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哦嘛噢[2;37;0m[2;37;0m", ({"omo"}));        
        set("gender", "男性");                
        set("long", "哦嘛噢[2;37;0m
它是周仓壹的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "btf");
        set("owner_name", "周仓壹");
        set_temp("owner", "btf");
        set_temp("owner_name", "周仓壹");
        ::setup();
}
