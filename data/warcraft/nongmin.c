// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m好小子[2;37;0m[2;37;0m", ({"hxz"}));        
        set("gender", "女性");                
        set("long", "一只土里土气的朱雀。[2;37;0m
它是农民的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "nongmin");
        set("owner_name", "农民");
        set_temp("owner", "nongmin");
        set_temp("owner_name", "农民");
        ::setup();
}
