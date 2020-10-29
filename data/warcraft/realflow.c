// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m大鹏[2;37;0m[2;37;0m", ({"dapeng"}));        
        set("gender", "女性");                
        set("long", "上古仙兽[2;37;0m
它是红袖招的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "realflow");
        set("owner_name", "红袖招");
        set_temp("owner", "realflow");
        set_temp("owner_name", "红袖招");
        ::setup();
}
