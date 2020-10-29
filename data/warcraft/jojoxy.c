// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m萌萌[2;37;0m[2;37;0m", ({"meng"}));        
        set("gender", "女性");                
        set("long", "可爱的宠物。[2;37;0m
它是林志玲的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "jojoxy");
        set("owner_name", "林志玲");
        set_temp("owner", "jojoxy");
        set_temp("owner_name", "林志玲");
        ::setup();
}
