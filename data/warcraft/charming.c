// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;33m电[1;32m你[1;31m没商量[2;37;0m[2;37;0m[2;37;0m", ({"lightning"}));        
        set("gender", "女性");                
        set("long", "电你没商量[2;37;0m
它是电电的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "charming");
        set("owner_name", "电电");
        set_temp("owner", "charming");
        set_temp("owner_name", "电电");
        ::setup();
}
