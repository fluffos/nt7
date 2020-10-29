// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m七彩云霞[2;37;0m[2;37;0m", ({"qicaiyunxia"}));        
        set("gender", "女性");                
        set("long", "彩霞仙子乘坐的七彩云霞，既美丽又迅速。[2;37;0m
它是彩霞的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "caixia");
        set("owner_name", "彩霞");
        set_temp("owner", "caixia");
        set_temp("owner_name", "彩霞");
        ::setup();
}
