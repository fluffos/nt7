// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qing"}));        
        set("gender", "男性");                
        set("long", "一条龙[2;37;0m
它是北城云的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bty");
        set("owner_name", "北城云");
        set_temp("owner", "bty");
        set_temp("owner_name", "北城云");
        ::setup();
}
