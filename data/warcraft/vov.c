// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m见性[2;37;0m[2;37;0m", ({"jianxing"}));        
        set("gender", "女性");                
        set("long", "$HIY$见性[2;37;0m
它是明心的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "vov");
        set("owner_name", "明心");
        set_temp("owner", "vov");
        set_temp("owner_name", "明心");
        ::setup();
}
