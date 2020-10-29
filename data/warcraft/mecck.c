// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m九天玲珑凰[2;37;0m[2;37;0m", ({"mecckpet"}));        
        set("gender", "女性");                
        set("long", "九天玲珑凰[2;37;0m
它是阿兰德龙的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mecck");
        set("owner_name", "阿兰德龙");
        set_temp("owner", "mecck");
        set_temp("owner_name", "阿兰德龙");
        ::setup();
}
