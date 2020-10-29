// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;33m草泥马[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "草泥马[2;37;0m
它是上上下下的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "talk");
        set("owner_name", "上上下下");
        set_temp("owner", "talk");
        set_temp("owner_name", "上上下下");
        ::setup();
}
